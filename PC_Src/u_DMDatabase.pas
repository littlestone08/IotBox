unit u_DMDatabase;

interface

uses
  System.SysUtils, System.Classes, FireDAC.Stan.Intf, FireDAC.Stan.Option,
  FireDAC.Stan.Error, FireDAC.UI.Intf, FireDAC.Phys.Intf, FireDAC.Stan.Def,
  FireDAC.Stan.Pool, FireDAC.Stan.Async, FireDAC.Phys, FireDAC.VCLUI.Wait,
  Data.DB, FireDAC.Comp.Client, FireDAC.Stan.Param, FireDAC.DatS,
  FireDAC.DApt.Intf, FireDAC.DApt, FireDAC.Comp.DataSet, FireDAC.Stan.ExprFuncs,
  FireDAC.Phys.SQLiteDef, FireDAC.Phys.SQLite,
  Variants, uCommonDef, FMX.Types;

type

{
select NULL PID, ID, Name, NULL RSSI, NULL PC, NULL EPC, NULL InBox from tbToolBox
union
select BID PID, ID, Name, RSSI, PC, EPC, InBox from tbTools
}

{
select  a.id    as ToolBoxID,
	      a.Iden  as ToolBoxIden,
        a.Name  as ToolBox,
        a.Status as Status,
        a.IsOnline as IsOnline,
        a.LastTimeStamp as LastTimeStamp,
        b.id    as ToolID,
	      b.Iden  as ToolIden,
        b.Name  as ToolName,
        b.PC,
        b.RSSI,
        b.EPC,
        b.InBox,
        b.BID
from tbToolBox a
    left join tbTools b  on b.bid = a.id

}
  TLeavePageRec = Record
    Caption: String;
    HrefID: Integer;
    HtmlID: Integer;
    HrefLink: String;
    ToolURL: String;
    HtmlText: String;
  End;

  TLeavePages = TArray<TLeavePageRec>;

  TdmDatabase = class(TDataModule)
    FDConnection1: TFDConnection;
    DataSource1: TDataSource;
    FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink;
    fdqModify: TFDQuery;
    FDMemTable1: TFDMemTable;
    fdaBoxes: TFDTableAdapter;
    fdaTools: TFDTableAdapter;
    fdcBoxes: TFDCommand;
    fdcTools: TFDCommand;
    fdmBoxes: TFDMemTable;
    fdmTools: TFDMemTable;
    dsBoxes: TDataSource;
    dsTools: TDataSource;
  private
    { Private declarations }
    Procedure RefreshUI;
    function Add_Update_Box(DevIden: String; BoxStatus: byte): Integer;
    function Add_UPdate_Tool(BoxID: Integer; PC, EPC: String;
      RSSI: ShortInt): Integer;
  public
    { Public declarations }
    Constructor Create(AOwner: TComponent); Override;
    Procedure db_QueryLeafPages(var Value: TLeavePages);
    Procedure db_UpdateHtmlID(const HrefID, HtmlID: Integer);

  public
    Procedure db_PushBoxToolList(const DevIden: String; const boxStatus: Byte; ToolListPtr: PToolInfoRec; ToolCount: Integer);
  end;

var
  dmDatabase: TdmDatabase;

implementation
uses
  u_frmTools;
{%CLASSGROUP 'Vcl.Controls.TControl'}

{$R *.dfm}
const
  CONST_DBFILENAME = 'ToolDB';




  //��ʷ״̬��α���

  //��������
  CONST_FIELDNAME_ID      = 'ID';
  CONST_FIELDNAME_IDEN          = 'IDEN';
  CONST_FIELDNAME_NAME          = 'Name';
  CONST_FIELDNAME_LASTTIMESTAMP = 'LastTimeStamp';
  //�������
  CONST_TB_TOOLBOX = 'tbToolBox';

  CONST_FIELDNAME_STATUS        = 'Status';
  CONST_FIELDNAME_BATTERY       = 'Battery';
  CONST_FIELDNAME_CHARGING      = 'Charging';
  //CONST_FIELDNAME_ISONLINE      = 'IsOnline';


  //��������
  CONST_TB_TOOLS   = 'tbTools';
  CONST_FIELDNAME_TID      = 'TID';
  CONST_FIELDNAME_PC       = 'PC';
  CONST_FIELDNAME_RSSI       = 'RSSI';
  CONST_FIELDNAME_EPC       = 'EPC';
  //CONST_FIELDNAME_INBOX     = 'InBox';
  CONST_FIELDNAME_DAT       = 'Memo';
  CONST_FIELDNAME_BOXID     = 'BID';




constructor TdmDatabase.Create(AOwner: TComponent);
const
  dbPath = '.\'  + CONST_DBFILENAME;
//var
//  dbPath: String;
//begin
//   dbPath:= AppPath + '\WeightInfo.sdb';
var
  Tables: TStringList;
var
  ASQL: String;
  Conn: TFDConnection;
begin
  inherited;
  Conn:= TFDConnection.Create(Self);
  Tables:= TStringList.Create;

  try
      with Conn do
      begin
        Connected:= False;
        Params.Add('DriverID=SQLite');
        Params.Add('Database=' + dbPath);
//        Params.Add('Database=D:\WORK\Io_Box\IotBox_Uv4\PC_Src\Win32\Debug\ToolDB');

    //      Params.Add('Database=:memory:'); //��ʡ������, FireDAC ��Դ����ʾ, if Database = '' then Database := ':memory:';
        //Params.Add('SQLiteAdvanced=page_size=4096'); //��ָ���ڴ�ҳ��С, ����Ĭ��ֵ
        Connected := True;
      end;

      Conn.GetTableNames('', '', '', Tables);
      if Tables.IndexOf(CONST_TB_TOOLBOX) < 0 then
      begin
        ASQL:= 'CREATE TABLE ' + CONST_TB_TOOLBOX + ' ('    +
                              CONST_FIELDNAME_ID +' integer PRIMARY KEY,'     +
                              CONST_FIELDNAME_IDEN + ' Text(24), '       +
                              CONST_FIELDNAME_LASTTIMESTAMP+ ' DateTime, ' +     //����ͨ��ʱ�䣬���������Ƿ�����

                              CONST_FIELDNAME_NAME    + ' string(20), '       +

                              CONST_FIELDNAME_STATUS  + ' TINYINT, '      +     //0:unkown, 1: ffline 2:opend 3 closed
                              CONST_FIELDNAME_BATTERY + ' TINYINT, '      +     //0~100 �ٷֱ�
                              CONST_FIELDNAME_CHARGING+ ' BOOLEAN '       +     //�Ƿ��ڳ��

                              ')';
        Conn.ExecSQL(ASQL);
      end;
      if Tables.IndexOf(CONST_TB_TOOLS) < 0 then
      begin
        ASQL:= 'CREATE TABLE ' + CONST_TB_TOOLS + ' ('    +
                              CONST_FIELDNAME_ID +' integer PRIMARY KEY,'     +
                              CONST_FIELDNAME_IDEN + ' string(24), '       +
                              CONST_FIELDNAME_LASTTIMESTAMP+ ' DateTime, ' +     //����ͨ��ʱ�䣬���������Ƿ�����

                              CONST_FIELDNAME_NAME    + ' string(24), '       +

                              CONST_FIELDNAME_TID     + ' Text, '       +
                              CONST_FIELDNAME_RSSI    + ' TinyInt, '       +
                              CONST_FIELDNAME_PC      + ' String(4), '       +
                              CONST_FIELDNAME_EPC     + ' String(24), '       +
                              CONST_FIELDNAME_DAT     + ' Text, '             +
                              CONST_FIELDNAME_BOXID  + ' integer null, ' +
                              'FOREIGN KEY (' + CONST_FIELDNAME_BOXID + ') REFERENCES ' +
                                  Format('%s(%s)', [CONST_TB_TOOLBOX, CONST_FIELDNAME_ID]) +
                              ')';
        Conn.ExecSQL(ASQL);

      end;
    finally
      Tables.Free;
      Conn.Free;
    end;


  {�鿴��}
  //MemTableEh1.Active:= True;
  //MemTableEh1.Fields.FieldDefs.Add('LastTimeStamp', ftDateTime);
//  MemTableEh1.FieldByName(CONST_FIELDNAME_ID).Visible:= False;
//  MemTableEh1.FieldByName(CONST_FIELDNAME_PID).Visible:= False;
end;




procedure TdmDatabase.db_PushBoxToolList(const DevIden: String; const boxStatus: Byte; ToolListPtr:
  PToolInfoRec; ToolCount: Integer);
var
  i: Integer;
  SQLCmd: String;
  BoxID: Integer;
  Changed: Boolean;
begin
  BoxID:= Add_Update_Box(DevIden, BoxStatus);
  for i := 0 to ToolCount - 1 do
  begin
    Add_UPdate_Tool(BoxID, ToolListPtr.PC_String, ToolListPtr.EPC_String, ToolListPtr.RSSI);
    inc(ToolListPtr);
  end;

  RefreshUI();
end;

procedure TdmDatabase.db_QueryLeafPages(var Value: TLeavePages);
const
  SQLSQL =
        'select * from %s where id not in                 ' +
        '(                                                ' +
        '     select id  from %s where id in              ' +
        '         (select id from %s where  pid = -1)     ' +
        '            union                                ' +
        '     select id  from %s where pid in             ' +
        '         (select id from %s where  pid = -1)     ' +
        ')                                                ';

var
  L_Query: TFDQuery;
  L_Count: Integer;
begin
//  L_Query:= TFDQuery.Create(Nil);
//  try
//    L_Query.Connection:= FDConnection1;
//    L_Query.SQL.Text:= Format(SQLSQL, [CONST_TABLENAME_HREF,
//                                  CONST_TABLENAME_HREF,
//                                  CONST_TABLENAME_HREF,
//                                  CONST_TABLENAME_HREF,
//                                  CONST_TABLENAME_HREF
//      ]);
//    L_Query.Active:= True;
//    L_Query.Offline;
//    L_Query.DisableControls;
//    SetLength(Value, 0);
//    L_Query.First;
//    while Not L_Query.Eof do
//    begin
//      L_Count:= Length(Value);
//      SetLength(Value, L_Count + 1);
//      Value[L_Count].Caption:= L_Query[CONST_FIELDNAME_CAPTION];
//      Value[L_Count].HrefID:= L_Query[CONST_FIELDNAME_ID];
//      Value[L_Count].HrefLink:= L_Query[CONST_FIELDNAME_HREF];
//      if VarIsNull(L_Query[CONST_FIELDNAME_TOOLURL]) then
//        Value[L_Count].ToolURL:= ''
//      else
//        Value[L_Count].ToolURL:= L_Query[CONST_FIELDNAME_TOOLURL];
//
//      L_Query.Next;
//    end;
//    L_Query.EnableControls;
//  finally
//    L_Query.Free;
//  end;
end;

procedure TdmDatabase.db_UpdateHtmlID(const HrefID, HtmlID: Integer);
var
  ASQL : String;
begin
  ASQL:= 'Update tbHref set HtmlID = ' + IntToStr(HtmlID) +
            ' where ID = ' + IntToStr(HrefID);
  FDConnection1.ExecSQL(ASQL);
end;



procedure TdmDatabase.RefreshUI;
begin
  frmTools.ReDrawTools();
end;


  Function TdmDatabase.Add_Update_Box(DevIden: String; BoxStatus: byte): Integer;
  begin
    fdqModify.SQL.Text:= 'select * from tbToolBox';
    fdqModify.Open();
    if Not fdqModify.Locate('iden', DevIden) then
    begin
      fdqModify.Append;
      fdqModify.FieldByName('iden').AsString:= DevIden;
      fdqModify.FieldByName('name').AsString:= DevIden;
      fdqModify.FieldByName('Status').Value:= BoxStatus;
    end;
    if Not (fdqModify.State in [dsEdit, dsInsert]) then
    begin
      fdqModify.Edit;
    end;

    fdqModify.FieldByName('LastTimeStamp').Value:= Now();
    fdqModify.Post;
    fdqModify.Close;
    fdqModify.Open('select id from tbToolBox where iden = ' + '''' + DevIden+ '''');
    Result:= fdqModify.FieldByName('id').Value;
    fdqModify.Close;
  end;

  Function TdmDatabase.Add_UPdate_Tool(BoxID: Integer; PC: String; EPC: String; RSSI: ShortInt): Integer;
  const
    InsToolSQL = 'Insert into ' + CONST_TB_TOOLS +
      ' (%s, %s, %s, %s, %s, %s) Values (%d, "%s", "%s", %d, "%s", "%s" )';
  var
    CmdSQL: String;
  begin
    fdqModify.SQL.Text:= 'select * from tbTools where BID = ' + IntToStr(BoxID);
    fdqModify.Open();

    if Not fdqModify.Locate('iden', EPC) then
    begin
      fdqModify.Append;
      fdqModify.FieldByName('bid').Value:= BoxID;
      fdqModify.FieldByName('iden').AsString:= EPC;
      fdqModify.FieldByName('name').AsString:= EPC;
      fdqModify.FieldByName('rssi').Value:= RSSI;
      fdqModify.FieldByName('pc').Value:= PC;
      fdqModify.FieldByName('epc').Value:= EPC;
    end;
    if Not (fdqModify.State in [dsEdit, dsInsert]) then
    begin
      fdqModify.Edit;
    end;
    fdqModify.FieldByName('LastTimeStamp').Value:= Now();
    fdqModify.Post;
    fdqModify.Close;
    fdqModify.Open('select id from tbTools where iden = '+ '''' + EPC + '''');
    Result:= fdqModify.FieldByName('id').Value;
    fdqModify.Close;
  end;
end.
