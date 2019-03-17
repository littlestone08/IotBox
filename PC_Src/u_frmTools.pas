unit u_frmTools;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, u_DMDatabase,
  Data.DB, Vcl.Grids, Vcl.DBGrids, DBGridEhGrouping, ToolCtrlsEh,
  DBGridEhToolCtrls, DynVarsEh, EhLibVCL, GridsEh, DBAxisGridsEh, DBGridEh, uFrmUsrCloudDllDemo,
  PlumUtils, uCommonDef;

type
  TfrmTools = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    TreeView1: TTreeView;
    Button2: TButton;
    Memo1: TMemo;
    DBGridEh1: TDBGridEh;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    CheckBox5: TCheckBox;
    CheckBox6: TCheckBox;
    CheckBox7: TCheckBox;
    CheckBox8: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
  private
    { Private declarations }
    FConnected: Boolean;
    Procedure _Log(const Info: String);
    Procedure ParserDevInfo(DevId: PWideChar;  pData: PByte; DataLen: Integer);
  public
    { Public declarations }
      Procedure Usr_Dev_StatusPush_CBF(MessageID: LongInt; DevId, JsonStr: PWideChar);
      Procedure Usr_RcvRawFromDev_CBF(MessageID: LongInt; DevId: PWideChar; pData: PByte;  DataLen: Integer);
  end;

var
  frmTools: TfrmTools;

implementation
uses
  Fmx.Types, StrUtils;

{$R *.dfm}

procedure TfrmTools.Button1Click(Sender: TObject);
begin
  if Not FConnected then
  begin
    FrmUsrCloudDllDemo.btnInitClick(Nil);

    FrmUsrCloudDllDemo.LabeledEdit_UserName.Text:= 'dcdz_test01';
    FrmUsrCloudDllDemo.LabeledEdit_password.Text:= 'test01';
    FrmUsrCloudDllDemo.btnConnClick(Nil);
    WaitMS(1000);
    FrmUsrCloudDllDemo.LabeledEdit_SubUserRaw.Text:= 'dcdz_test01';
    FrmUsrCloudDllDemo.btnSubscribeUserRawClick(Nil);

    FConnected:= True;
  end;
end;

procedure TfrmTools.Usr_Dev_StatusPush_CBF(MessageID: LongInt; DevId,
  JsonStr: PWideChar);
begin
  Log.d('MessageID: %d, DeviceID: %s, JsonStr: %s', [MessageID, DevID, JsonStr]);
end;

procedure TfrmTools.Usr_RcvRawFromDev_CBF(MessageID: LongInt; DevId: PWideChar;
  pData: PByte; DataLen: Integer);
var
  Str: AnsiString;

begin
  SetLength(Str, DataLen);
  System.Move(pData^, Str[1], DataLen);
  if StartsText('$GPRMC', Str) then
  begin
    _Log('GPS：' + Str);
  end
  else if StartsText('www.usr.cn', Str) then
  begin
    _Log('设备心跳包：' + Str);
  end
  else
  begin
    _Log('二进制数据流: ' + PlumUtils.Buf2Hex(Str));
    ParserDevInfo(DevId, pData, DataLen);
  end;

  //_Log('原始数据流: ' + Str);


end;

procedure TfrmTools.Button2Click(Sender: TObject);
begin
  FrmUsrCloudDllDemo.Show;
end;

procedure TfrmTools.CheckBox1Click(Sender: TObject);
begin
  if sender is TCheckBox then
  begin
    dmDatabase.MemTableEh1.FieldByName(TCheckBox(Sender).Caption).Visible:= TCheckBox(Sender).Checked;
  end;
end;

procedure TfrmTools.FormCreate(Sender: TObject);
begin
  DBGridEh1.DataSource.DataSet.Open;
//  With self.DBGridEh1.DataGrouping do
//  begin
//
//    Active:= True;
//    GroupPanelVisible:= True;
//    With GroupLevels.Add do
//    begin
//      Column:= self.DBGridEh1.FindFieldColumn('ID');
//    end;
//  end;
//  self.DBGridEh1.DataSource.DataSet.FieldByName('ToolBox').DisplayLabel:= '工具箱';
//select  a.id    as ToolBoxID,
//        a.Name  as ToolBox,
//        a.Status as Status,
//        b.id    as ToolID,
//        b.Name  as ToolName,
//        b.PC,
//        b.RSSI,
//        b.EPC,b.InBox
//  With DBGridEh1.DataSource.DataSet do
//  begin
//    With FieldByName('ToolBox') do
//    begin
//      DisplayLabel:= '工具箱';
//      DisplayWidth:= 10;
//    end;
//    With FieldByName('ToolBoxIden') do
//    begin
//      DisplayLabel:= '工具箱编码';
//      DisplayWidth:= 10;
//    end;
//    With FieldByName('Status') do
//    begin
//      DisplayLabel:= '状态';
//      DisplayWidth:= 10;
//    end;
//
//    With FieldByName('IsOnline') do
//    begin
//      DisplayLabel:= '联网';
//      DisplayWidth:= 10;
//    end;
//
//    With FieldByName('LastTimeStamp') do
//    begin
//      DisplayLabel:= '上次通信时间';
//      DisplayWidth:= 10;
//    end;
//
//    With FieldByName('ToolIden') do
//    begin
//      DisplayLabel:= '工具编码';
//      DisplayWidth:= 10;
//    end;
//
//    With FieldByName('ToolName') do
//    begin
//      DisplayLabel:= '工具';
//      DisplayWidth:= 10;
//    end;
//
//    With FieldByName('InBox') do
//    begin
//      DisplayLabel:= '未使用';
//      DisplayWidth:= 10;
//    end;
//
//
//
//    With FieldByName('PC') do
//    begin
////      DisplayLabel:= '未使用';
//      DisplayWidth:= 10;
//    end;
//    FieldByName('ToolBoxID').Visible:= False;
//    FieldByName('ToolID').Visible:= False;
//  end;
end;

procedure TfrmTools.FormDestroy(Sender: TObject);
begin
  if FConnected then
  begin
    FrmUsrCloudDllDemo.btnUnSubscribeUserRawClick(Nil);
    FrmUsrCloudDllDemo.btnUnSubscribeUserRawClick(Nil);
    FrmUsrCloudDllDemo.btnDisConnClick(Nil);
    FrmUsrCloudDllDemo.btnReleaseClick(Nil);
    FConnected:= False;
  end;
end;


procedure TfrmTools.ParserDevInfo(DevId: PWideChar; pData: PByte;
  DataLen: Integer);
var
  type_code, Cmd_Code: Byte;
  param_len: Integer;
  i: Integer;
  check_sum: Byte;
  pParam: PByte;
var
  BoxStatus: Byte;
  ToolCount: Byte;
  RSSI: Byte;
  PC: SmallInt;
  ToolInfoPtr: PToolInfoRec;
begin
  if DataLen >= 7 then
  begin
    if (pData[0] = $BB) and  (pData[DataLen - 1] = $7E) then
    begin
      check_sum:= pData[1];
      for i := 2 to DataLen - 3 do
      begin
        check_sum:= check_sum + pData[i];
        Log.d('0x%2x', [pData[i]]);
      end;
      if (check_sum = pData[DataLen - 2]) or True then //校验有问题
      begin
        type_code:= pData[1];
        cmd_code:= pData[2];
        param_len:= pData[3] shl 8 or pData[4];
        pParam:= @pData[5];
        //----------------------------
        if (type_code = $01) and (Cmd_Code = $00) then
        begin
          BoxStatus:= pParam[0];
          ToolCount:= pParam[1];
          ToolInfoPtr:= @pParam[2];
          dmDatabase.db_PushBoxToolList(DevId, Boxstatus, ToolInfoPtr, ToolCount);
          for i := 0 to ToolCount - 1 do
          begin
            _Log(Format('第 %d 个: %s', [i + 1,ToolInfoPtr.EPC_String]));
            Inc(ToolInfoPtr);
          end;
        end
        else
        begin
          _Log(Format('不能解析的命令: 0x%2x,  0x%2x', [type_code, cmd_code]));
        end;
      end
      else
      begin
        _Log(Format('无法解析, 校验和错误: 0x%2x <> 0x%2x', [check_sum, pData[DataLen - 2]]));
      end;
    end
    else
    begin
      _Log(Format('无法解析, 帧头尾错误: 0x%2x, 0x%2x', [pData[0], pData[DataLen - 1]]));
    end;
  end
  else
  begin
    _Log(Format('无法解析, 数据长度错误: %d', [DataLen]));
  end;
end;

procedure TfrmTools._Log(const Info: String);
begin
  self.Memo1.Lines.Add(Format('%s: %s', [FormatDateTime('YYYY-MM-DD HH:NN:SS', NOw), Info]))
end;

end.
