unit u_DMDatabase;

interface

uses
  System.SysUtils, System.Classes, FireDAC.Stan.Intf, FireDAC.Stan.Option,
  FireDAC.Stan.Error, FireDAC.UI.Intf, FireDAC.Phys.Intf, FireDAC.Stan.Def,
  FireDAC.Stan.Pool, FireDAC.Stan.Async, FireDAC.Phys, FireDAC.VCLUI.Wait,
  Data.DB, FireDAC.Comp.Client, FireDAC.Stan.Param, FireDAC.DatS,
  FireDAC.DApt.Intf, FireDAC.DApt, FireDAC.Comp.DataSet, FireDAC.Stan.ExprFuncs,
  FireDAC.Phys.SQLiteDef, FireDAC.Phys.SQLite,
  MemTableEh, Variants, CnDebug, MemTableDataEh, DataDriverEh, uCommonDef, FMX.Types;

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
    FDQuery1: TFDQuery;
    DataSource1: TDataSource;
    FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink;
    DataSetDriverEh1: TDataSetDriverEh;
    FDQuery4: TFDQuery;
    MemTableEh1: TMemTableEh;
  private
    { Private declarations }
  public
    { Public declarations }
    Constructor Create(AOwner: TComponent); Override;
    Function AddHrefItem(const APID: Integer; const ACaption: String; AHref: String; AHtmlID: Integer = -1): Integer;
    Procedure db_QueryLeafPages(var Value: TLeavePages);
    Function db_AddHtmlTool(const HtmlSource: String): Integer;
    Procedure db_UpdateHtmlID(const HrefID, HtmlID: Integer);
    Procedure db_UpdateToolURL(const ID: Integer; const URL: String);
    Procedure db_PushBoxToolList(const DevIden: String; const boxStatus: Byte; ToolListPtr: PToolInfoRec; ToolCount: Integer);
  end;

var
  dmDatabase: TdmDatabase;

implementation

{%CLASSGROUP 'Vcl.Controls.TControl'}

{$R *.dfm}
const
  CONST_DBFILENAME = 'ToolDB';




  //历史状态如何保存

  //公共属性
  CONST_FIELDNAME_ID      = 'ID';
  CONST_FIELDNAME_IDEN          = 'IDEN';
  CONST_FIELDNAME_NAME          = 'Name';
  //工具箱表
  CONST_TB_TOOLBOX = 'tbToolBox';

  CONST_FIELDNAME_STATUS        = 'Status';
  CONST_FIELDNAME_BATTERY       = 'Battery';
  CONST_FIELDNAME_CHARGING      = 'Charging';
  CONST_FIELDNAME_ISONLINE      = 'IsOnline';
  CONST_FIELDNAME_LASTTIMESTAMP = 'LastTimeStamp';

  //工具属性
  CONST_TB_TOOLS   = 'tbTools';
  CONST_FIELDNAME_TID      = 'TID';
  CONST_FIELDNAME_PC       = 'PC';
  CONST_FIELDNAME_RSSI       = 'RSSI';
  CONST_FIELDNAME_EPC       = 'EPC';
  CONST_FIELDNAME_INBOX     = 'InBox';
  CONST_FIELDNAME_DAT       = 'Memo';
  CONST_FIELDNAME_BOXID     = 'BID';

  //-------------------------------------
  CONST_FIELDNAME_PID     = 'PID';
  CONST_FIELDNAME_CAPTION = 'Caption';
  CONST_FIELDNAME_HREF    = 'Hreflink';
  CONST_FIELDNAME_TOOLURL = 'ToolURL';
  CONST_FIELDNAME_HTMLID  = 'HTMLID';
  CONST_FIELDNAME_HTML    = 'HTML';
  CONST_FIELDNAME_HTML2   = 'HTML2';

  CONST_WEB_ROOT = 'https://www.mwstore.com';

function TdmDatabase.AddHrefItem(const APID: Integer; const ACaption: String;
  AHref: String; AHtmlID: Integer): Integer;
//const
//  AFmtSQL = 'Insert into ' + CONST_TABLENAME_HREF +
//    ' (%s, %s, %s, %s) Values (%s, %s, %s, %s )';
var
  ASQL: String;

begin
//  ASQL:= Format(AFmtSQL, [CONST_FIELDNAME_PID, CONST_FIELDNAME_CAPTION, CONST_FIELDNAME_HREF, CONST_FIELDNAME_HTMLID,
//    APID, ACaption, AHref, L_HtmlID
//    ]);
//  FDConnection1.ExecSQL(ASQL);
  FDQuery1.DisableControls;
  try
    FDQuery1.Append;
    FDQuery1[CONST_FIELDNAME_PID]:= APID;
    FDQuery1[CONST_FIELDNAME_CAPTION]:= ACaption;
    FDQuery1[CONST_FIELDNAME_HREF]:= AHref;
    if AHtmlID >= 0 then
      FDQuery1[CONST_FIELDNAME_HTMLID]:= AHtmlID;
    FDQuery1.Post;
    FDQuery1.Refresh;
    Result:= FDQuery1[CONST_FIELDNAME_ID];
  finally
    FDQuery1.EnableControls;
  end;
end;

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

    //      Params.Add('Database=:memory:'); //可省略这行, FireDAC 的源码显示, if Database = '' then Database := ':memory:';
        //Params.Add('SQLiteAdvanced=page_size=4096'); //可指定内存页大小, 这是默认值
        Connected := True;
      end;

      Conn.GetTableNames('', '', '', Tables);
      if Tables.IndexOf(CONST_TB_TOOLBOX) < 0 then
      begin
        ASQL:= 'CREATE TABLE ' + CONST_TB_TOOLBOX + ' ('    +
                              CONST_FIELDNAME_ID +' integer PRIMARY KEY,'     +
                              CONST_FIELDNAME_IDEN + ' string(24), '       +
                              CONST_FIELDNAME_NAME    + ' string(20), '       +
                              CONST_FIELDNAME_STATUS  + ' TINYINT, '      +     //0:unkown, 1: ffline 2:opend 3 closed
                              CONST_FIELDNAME_BATTERY + ' TINYINT, '      +     //0~100 百分比
                              CONST_FIELDNAME_CHARGING+ ' BOOLEAN, '       +     //是否在充电
                              CONST_FIELDNAME_ISONLINE+ ' BOOLEAN, '       +     //是否在线
                              CONST_FIELDNAME_LASTTIMESTAMP+ ' DateTime' +     //最后的通信时间，用来计算是否在线
                              ')';
        Conn.ExecSQL(ASQL);
      end;
      if Tables.IndexOf(CONST_TB_TOOLS) < 0 then
      begin
        ASQL:= 'CREATE TABLE ' + CONST_TB_TOOLS + ' ('    +
                              CONST_FIELDNAME_ID +' integer PRIMARY KEY,'     +
                              CONST_FIELDNAME_IDEN + ' string(24), '       +
                              CONST_FIELDNAME_NAME    + ' string(24), '       +
                              CONST_FIELDNAME_TID     + ' Text, '       +
                              CONST_FIELDNAME_RSSI    + ' TinyInt, '       +
                              CONST_FIELDNAME_PC      + ' String(4), '       +
                              CONST_FIELDNAME_EPC     + ' String(24), '       +
                              CONST_FIELDNAME_INBOX   + ' BOOLEAN, '       +     //是否在盒子中
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


  {查看表}
  MemTableEh1.Active:= True;
  //MemTableEh1.Fields.FieldDefs.Add('LastTimeStamp', ftDateTime);
//  MemTableEh1.FieldByName(CONST_FIELDNAME_ID).Visible:= False;
//  MemTableEh1.FieldByName(CONST_FIELDNAME_PID).Visible:= False;
end;

function TdmDatabase.db_AddHtmlTool(const HtmlSource: String): Integer;
const
  AFmtSQL = 'select * from  %s';
var
  L_Query: TFDQuery;
  L_Count: Integer;
begin
  L_Query:= TFDQuery.Create(Nil);
  try
    L_Query.Connection:= FDConnection1;
    L_Query.SQL.Text:= Format(AFmtSQL, [
                                  CONST_TB_TOOLBOX,
                                  CONST_FIELDNAME_ID]);
    L_Query.Active:= True;
    L_Query.DisableControls;
    L_Query.Append;
    L_Query[CONST_FIELDNAME_HTML]:= HtmlSource;
    L_Query.Post;
    L_Query.Refresh;
    Result:= L_Query[CONST_FIELDNAME_ID];
  finally
    L_Query.Free;
  end;
end;



procedure TdmDatabase.db_PushBoxToolList(const DevIden: String; const boxStatus: Byte; ToolListPtr:
  PToolInfoRec; ToolCount: Integer);
  Function GetBoxID(AIden: string; var ID: Integer): Boolean;
  begin
    Result:= False;
    FDQuery4.Open('Select ID From tbToolBox where Iden = ' + AIden);
    if FDQuery4.RecordCount = 1 then
    begin
      ID:= FDQuery4.FieldValues['ID'];
      Result:= True;
    end;
  end;
const
  ANowBoxFmtSQL = 'Insert into ' + CONST_TB_TOOLBOX +
    ' (%s, %s, %s, %s, %s) Values (%s, %s, %d, 1, Now() )';
  InsToolSQL = 'Insert into ' + CONST_TB_TOOLS +
    ' (%s, %s, %s, %s, %s, %s) Values (%d, "%s", "%s", %d, "%s", "%s" )';
var
  i: Integer;
  SQLCmd: String;
  BoxID: Integer;
  PC_Byte: TBytes;
begin

  if Not GetBoxID(DevIden, BoxID) then
  begin
    SQLCmd:= Format(ANowBoxFmtSQL, [
      CONST_FIELDNAME_IDEN,
      CONST_FIELDNAME_NAME,
      CONST_FIELDNAME_STATUS,
      CONST_FIELDNAME_ISONLINE,
      CONST_FIELDNAME_LASTTIMESTAMP,
      DevIden, DevIden, BoxStatus
      //, 1
      //, FormatDateTime('YYYY-MM-DD HH:NN:SS', NOw)
    ]);
    //Log.d(SQLCmd);
    FDQuery4.ExecSQL(SQLCmd);
    Assert(GetBoxID(DevIden, BoxID) = True, '');
  end;

  for i := 0 to ToolCount - 1 do
  begin
    SetLength(PC_Byte, 2);
    Move(ToolListPtr.PC, PC_Byte[0], 2);
    SQLCmd:= Format(InsToolSQL, [
      CONST_FIELDNAME_BOXID  ,
      CONST_FIELDNAME_IDEN,
      CONST_FIELDNAME_NAME,
      CONST_FIELDNAME_RSSI,
      CONST_FIELDNAME_PC,
      CONST_FIELDNAME_EPC,

      BoxID, ToolListPtr.Iden_String(), ToolListPtr.Iden_String(),
      ToolListPtr.RSSI,ToolListPtr.PC_String(),ToolListPtr.EPC_String()
    ]);
    Log.d(SQLCmd);
    FDQuery4.ExecSQL(SQLCmd);
    inc(ToolListPtr);
  end;



  MemTableEh1.DisableControls;
  try
    MemTableEh1.Refresh;
  finally
    MemTableEh1.EnableControls;
  end;

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

procedure TdmDatabase.db_UpdateToolURL(const ID: Integer; const URL: String);
var
  ASQL : String;
begin
  ASQL:= 'Update tbHref set ToolURL = :URL where ID = :ID';
  FDConnection1.ExecSQL(ASQL, [CONST_WEB_ROOT + URL, ID]);
end;

end.
