object frmTools: TfrmTools
  Left = 0
  Top = 0
  Caption = #24037#20855#31665
  ClientHeight = 635
  ClientWidth = 1208
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
    1208
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
    Caption = #36830#25509#26381#21153#22120
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 344
    Top = 1
    Width = 75
    Height = 25
    Caption = #35843#35797#31383#21475
    TabOrder = 1
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 285
    Width = 1192
    Height = 342
    Anchors = [akLeft, akRight, akBottom]
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 2
  end
  object DBGrid1: TDBGrid
    Left = 352
    Top = 32
    Width = 848
    Height = 81
    Anchors = [akLeft, akTop, akRight]
    DataSource = dmDatabase.dsBoxes
    TabOrder = 3
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = #23435#20307
    TitleFont.Style = []
  end
  object DBGrid2: TDBGrid
    Left = 352
    Top = 119
    Width = 848
    Height = 146
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmDatabase.dsTools
    TabOrder = 4
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = #23435#20307
    TitleFont.Style = []
  end
  object Button3: TButton
    Left = 497
    Top = 1
    Width = 88
    Height = 25
    Caption = #25163#24037#20462#25913#20445#23384
    TabOrder = 5
    OnClick = Button3Click
  end
  object lvBoxes: TListView
    Left = 7
    Top = 32
    Width = 339
    Height = 233
    Anchors = [akLeft, akTop, akBottom]
    Columns = <
      item
        Caption = #21517#31216
        Width = 100
      end
      item
        Caption = #29366#24577
        Width = 100
      end
      item
        Caption = #20869#37096#32534#30721
        Width = 120
      end>
    Groups = <
      item
        Header = #31665'#1'
        Footer = '00022845000000000004'
        GroupID = 3
        State = [lgsNormal]
        HeaderAlign = taLeftJustify
        FooterAlign = taRightJustify
        Subtitle = #22312#32447'('#25171#24320')'
        TitleImage = -1
      end>
    Items.ItemData = {
      055E0000000200000000000000FFFFFFFFFFFFFFFF0100000003000000000000
      00047F674B623500F75303C0684B6D305298FD6B1700000000FFFFFFFFFFFFFF
      FF01000000030000000000000003BA871D4E0052042A67C0684B6D305210F56B
      17FFFFFFFF}
    GroupView = True
    ReadOnly = True
    TabOrder = 6
    ViewStyle = vsReport
  end
  object Button4: TButton
    Left = 600
    Top = 1
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 7
    OnClick = Button4Click
  end
end
