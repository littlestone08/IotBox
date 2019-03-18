object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 311
  ClientWidth = 643
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lv1: TListView
    Left = 0
    Top = 0
    Width = 643
    Height = 311
    Align = alClient
    Columns = <
      item
        Caption = 'col1'
      end
      item
        Caption = 'col2'
      end>
    Groups = <
      item
        Header = 'HEADER'
        Footer = 'FOOTER'
        GroupID = 3
        State = [lgsNormal]
        HeaderAlign = taLeftJustify
        FooterAlign = taRightJustify
        Subtitle = 'SUBTITLE'
        TitleImage = -1
      end>
    Items.ItemData = {
      05800000000300000000000000FFFFFFFFFFFFFFFF0100000003000000000000
      00056900740065006D0031000463006F006C00320078B1592F00000000FFFFFF
      FFFFFFFFFF010000000300000000000000056900740065006D0032000463006F
      006C0032004862592F00000000FFFFFFFFFFFFFFFF00000000FFFFFFFF000000
      0000FFFFFFFF}
    TabOrder = 0
    ViewStyle = vsReport
    OnCustomDrawSubItem = lv1CustomDrawSubItem
  end
end
