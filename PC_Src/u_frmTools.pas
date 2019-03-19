unit u_frmTools;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, u_DMDatabase,
  Data.DB, Vcl.Grids, Vcl.DBGrids,  uFrmUsrCloudDllDemo,
  PlumUtils, uCommonDef, Vcl.ExtCtrls, Vcl.ToolWin;

type
  TfrmTools = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Memo1: TMemo;
    DBGrid1: TDBGrid;
    DBGrid2: TDBGrid;
    Button3: TButton;
    lvBoxes: TListView;
    Button4: TButton;
    Panel1: TPanel;
    Splitter1: TSplitter;
    Panel2: TPanel;
    Splitter2: TSplitter;
    ToolBar1: TToolBar;
    Splitter3: TSplitter;
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    FConnected: Boolean;
    Procedure _Log(const Info: String);
    Procedure ParserDevInfo(DevId: PWideChar;  pData: PByte; DataLen: Integer);
  public
    { Public declarations }
      Procedure Usr_Dev_StatusPush_CBF(MessageID: LongInt; DevId, JsonStr: PWideChar);
      Procedure Usr_RcvRawFromDev_CBF(MessageID: LongInt; DevId: PWideChar; pData: PByte;  DataLen: Integer);
      Procedure ReDrawTools();
  end;

var
  frmTools: TfrmTools;

implementation
uses
  Fmx.Types, StrUtils, DateUtils;

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
    dmDatabase.db_PushBoxComm(DevID);
    self.ReDrawTools();
  end
  else if StartsText('www.usr.cn', Str) then
  begin
    _Log('设备心跳包：' + Str);
    dmDatabase.db_PushBoxComm(DevID);
    self.ReDrawTools();
  end
  else
  begin
    _Log('二进制数据流: ' + PlumUtils.Buf2Hex(Str));
    ParserDevInfo(DevId, pData, DataLen);
  end;
end;

procedure TfrmTools.Button2Click(Sender: TObject);
begin
  FrmUsrCloudDllDemo.Show;
end;

procedure TfrmTools.Button3Click(Sender: TObject);
begin
  self.lvBoxes.ShowColumnHeaders:= False;
  self.lvBoxes.ShowColumnHeaders:= True;
  self.lvBoxes.Clear;

  With dmDatabase.fdmBoxes do
    if (State in [dsEdit, dsInsert]) then
      Post;

  With dmDatabase.fdmTools do
    if (State in [dsEdit, dsInsert]) then
      Post;
end;



procedure TfrmTools.Button4Click(Sender: TObject);
begin
  LockWindowUpdate(self.lvBoxes.Handle);
  try
    self.ReDrawTools();
  finally
    LockWindowUpdate(0);
  end;
end;

procedure TfrmTools.FormCreate(Sender: TObject);
begin
  self.lvBoxes.Clear;
  DBGrid1.DataSource.DataSet.Open;
  DBGrid2.DataSource.DataSet.Open;
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


procedure TfrmTools.FormShow(Sender: TObject);
begin
   self.ReDrawTools();
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
          self.ReDrawTools();
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

procedure TfrmTools.ReDrawTools;
  Function BoxTimeout(TimeThen: TDateTime): Boolean;
  begin
    Result:= SecondsBetween(Now, TimeThen) > 60;
  end;

  Function UpdateBox(const BoxID: Integer; const IDEN: String; const BoxName: String; StateStr: String): TListGroup;
  var
    i: Integer;
  begin
    Result:= Nil;
    for i := 0 to self.lvBoxes.Groups.Count - 1 do
    begin
      if lvBoxes.Groups.Items[i].GroupID =  BoxID then
      begin
        Result:= lvBoxes.Groups.Items[i];
        Break;
      end;
    end;

    if Result = Nil then
      Result:= lvBoxes.Groups.Add;

    With Result do
    begin
      GroupID:= BoxID;
      Header:= BoxName;
      Footer:= IDEN;
      Subtitle:= StateStr;
    end;
  end;

  Procedure UpdateTools(const ABoxID: Integer; const IDEN: String;
    const ToolName: String; StateStr: String);
  var
    i: Integer;
    ATool: TListItem;
  begin
    ATool:= Nil;
    for i := 0 to lvBoxes.Items.Count - 1 do
    begin
      if lvBoxes.Items[i].SubItems[1] = IDEN then
      begin
        ATool:= lvBoxes.Items[i];
        Break;
      end;
    end;
    if ATool = Nil then
    begin
      ATool:= lvBoxes.Items.Add;
      ATool.GroupID:= ABoxID;
      ATool.SubItems.Add('');
      ATool.SubItems.Add('');
    end;

    With ATool do
    begin
      ATool.Caption:= ToolName;
      ATool.SubItems[0]:= StateStr;
      ATool.SubItems[1]:= IDEN;
    end;
  end;
  function BoxState(StateCode: Byte; LastCommTime: TDateTime): String;
  begin
    if BoxTimeout(LastCommTime) then
    begin
      Result:= '离线'
    end
    else
      Result:= '在线';

    if Result = '在线' then
    case StateCode of
      0: Result:= Result + '(未知)';
      1: Result:= Result + '(打开)';
      2: Result:= Result + '(关闭)';
    else
      Result:= Result + '(未知:'+ IntToStr(StateCode) +')';
    end;
  end;
  function ToolState(BoxCommTime, BoxScanTime: TDateTime; ToolScanTime: TDateTime): String;
  begin
    if BoxTimeout(BoxCommTime) then
    begin
      Result:= '未知';
    end
    else
    begin
    //'╳√'
      if SecondSpan(ToolScanTime, BoxScanTime) > 2 then
      begin
        Result:= '╳'
      end
      else
        Result:= '√';
    end;
  end;
var
  //BoxScanTime: TDateTime;
  VBoxScanTime: Variant;
  BoxCommTime: TDateTime;
begin
  With dmDatabase do
  begin
    fdmBoxes.DisableControls;
    fdmTools.DisableControls;
    try
      fdmBoxes.First;
      while not fdmBoxes.Eof do
      begin
        BoxCommTime:= fdmBoxes.FieldValues['LastCommTime'];
        VBoxScanTime:= fdmBoxes.FieldValues['LastScanTime'];
        UpdateBox(fdmBoxes.FieldValues['id'],
                  fdmBoxes.FieldValues['iden'],
                  fdmBoxes.FieldValues['Name'],
                  BoxState(fdmBoxes.FieldValues['Status'], BoxCommTime)
        );
        //更新对应工具箱中的工具信息
        fdmTools.First;
        while not fdmTools.Eof do
        begin
          UpdateTools(
                      fdmTools.FieldValues['bid'],
                      fdmTools.FieldValues['iden'],
                      fdmTools.FieldValues['Name'],
                      ToolState(BoxCommTime, VBoxScanTime,
                            fdmTools.FieldValues['LastScanTime'])
          );
          fdmTools.Next;
        end;


        fdmBoxes.Next;
      end;

    finally
      fdmBoxes.EnableControls;
      fdmTools.EnableControls;
    end;
  end;

  Log.d(inttoStr(self.lvBoxes.Groups.Count));
end;

procedure TfrmTools.Timer1Timer(Sender: TObject);
begin
  self.ReDrawTools();
end;

procedure TfrmTools._Log(const Info: String);
begin
  self.Memo1.Lines.Add(Format('%s: %s', [FormatDateTime('YYYY-MM-DD HH:NN:SS', NOw), Info]))
end;

end.
