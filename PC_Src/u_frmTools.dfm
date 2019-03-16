object frmTools: TfrmTools
  Left = 0
  Top = 0
  Caption = #24037#20855#31665
  ClientHeight = 635
  ClientWidth = 1098
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    1098
    635)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 7
    Width = 65
    Height = 13
    Caption = #24037#20855#31665#29366#24577
  end
  object Button1: TButton
    Left = 263
    Top = 1
    Width = 75
    Height = 25
    Caption = #36830#25509
    TabOrder = 0
    OnClick = Button1Click
  end
  object TreeView1: TTreeView
    Left = 8
    Top = 32
    Width = 273
    Height = 233
    Indent = 19
    TabOrder = 1
    Items.NodeData = {
      0301000000240000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      00010000000103E55D7751B17B220000000000000000000000FFFFFFFFFFFFFF
      FF0000000000000000000000000102BE8B0759}
  end
  object Button2: TButton
    Left = 344
    Top = 1
    Width = 75
    Height = 25
    Caption = #35843#35797#31383#21475
    TabOrder = 2
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 285
    Width = 1082
    Height = 342
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object DBGridEh1: TDBGridEh
    Left = 304
    Top = 32
    Width = 777
    Height = 233
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmDatabase.DataSource1
    DynProps = <>
    TabOrder = 4
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
end
