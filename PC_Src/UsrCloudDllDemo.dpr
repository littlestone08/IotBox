program UsrCloudDllDemo;

uses
  Vcl.Forms,
  uFrmUsrCloudDllDemo in 'uFrmUsrCloudDllDemo.pas' {FrmUsrCloudDllDemo},
  uUsrCloud in 'uUsrCloud.pas',
  u_DMDatabase in 'u_DMDatabase.pas' {dmDatabase: TDataModule},
  u_frmTools in 'u_frmTools.pas' {frmTools},
  PlumUtils in 'D:\WORK170908\PlumComm\PlumUtils.pas',
  uCommonDef in 'uCommonDef.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TdmDatabase, dmDatabase);
  Application.CreateForm(TfrmTools, frmTools);
  Application.CreateForm(TFrmUsrCloudDllDemo, FrmUsrCloudDllDemo);
  Application.Run;
end.
