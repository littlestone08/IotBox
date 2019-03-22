object frmTools: TfrmTools
  Left = 0
  Top = 0
  Caption = #24037#20855#31665
  ClientHeight = 635
  ClientWidth = 926
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter3: TSplitter
    Left = 0
    Top = 276
    Width = 926
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitWidth = 359
  end
  object Memo1: TMemo
    Left = 0
    Top = 279
    Width = 926
    Height = 356
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 926
    Height = 247
    Align = alTop
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 417
      Top = 1
      Height = 245
      ExplicitLeft = 552
      ExplicitTop = 104
      ExplicitHeight = 100
    end
    object lvBoxes: TListView
      Left = 1
      Top = 1
      Width = 416
      Height = 245
      Align = alLeft
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
          Width = 200
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
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
    end
    object Panel2: TPanel
      Left = 420
      Top = 1
      Width = 505
      Height = 245
      Align = alClient
      TabOrder = 1
      object Splitter2: TSplitter
        Left = 1
        Top = 82
        Width = 503
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitWidth = 162
      end
      object DBGrid1: TDBGrid
        Left = 1
        Top = 1
        Width = 503
        Height = 81
        Align = alTop
        DataSource = dmDatabase.dsBoxes
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -13
        TitleFont.Name = #23435#20307
        TitleFont.Style = []
      end
      object DBGrid2: TDBGrid
        Left = 1
        Top = 85
        Width = 503
        Height = 159
        Align = alClient
        DataSource = dmDatabase.dsTools
        TabOrder = 1
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -13
        TitleFont.Name = #23435#20307
        TitleFont.Style = []
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 926
    Height = 29
    Caption = 'ToolBar1'
    TabOrder = 2
    object Button1: TButton
      Left = 0
      Top = 0
      Width = 75
      Height = 22
      Caption = #36830#25509#26381#21153#22120
      TabOrder = 0
      OnClick = Button1Click
    end
    object btnDiscon: TButton
      Left = 75
      Top = 0
      Width = 75
      Height = 22
      Caption = #26029#24320#36830#25509
      TabOrder = 4
      OnClick = btnDisconClick
    end
    object Button2: TButton
      Left = 150
      Top = 0
      Width = 75
      Height = 22
      Caption = #35843#35797#31383#21475
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 225
      Top = 0
      Width = 88
      Height = 22
      Caption = #25163#24037#20462#25913#20445#23384
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 313
      Top = 0
      Width = 75
      Height = 22
      Caption = 'Button4'
      TabOrder = 3
      OnClick = Button4Click
    end
  end
  object Timer1: TTimer
    Interval = 15000
    OnTimer = Timer1Timer
    Left = 168
    Top = 141
  end
end
