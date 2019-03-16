object dmDatabase: TdmDatabase
  OldCreateOrder = False
  Height = 414
  Width = 567
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=D:\WORK\Io_Box\IotBox_Uv4\PC_Src\Win32\Debug\ToolDB'
      'DriverID=SQLite')
    Connected = True
    Left = 88
    Top = 64
  end
  object FDQuery1: TFDQuery
    Connection = FDConnection1
    SQL.Strings = (
      'select  a.id    as ToolBoxID,'
      #9'      a.Iden  as ToolBoxIden,'
      '        a.Name  as ToolBox,'
      '        a.Status as Status,'
      '        a.IsOnline as IsOnline,'
      '        a.LastTimeStamp as LastTimeStamp,'
      '        b.id    as ToolID,'
      #9'      b.Iden  as ToolIden,'
      '        b.Name  as ToolName,'
      '        b.PC,'
      '        b.RSSI,'
      '        b.EPC,'
      '        b.InBox,'
      '        b.BID'
      'from tbToolBox a'
      '    left join tbTools b  on b.bid = a.id')
    Left = 176
    Top = 64
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 248
    Top = 64
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 88
    Top = 8
  end
  object MemTableEh1: TMemTableEh
    FieldDefs = <
      item
        Name = 'ToolBoxID'
        DataType = ftInteger
        Precision = 15
      end
      item
        Name = 'ToolBoxIden'
        DataType = ftWideString
        Size = 20
      end
      item
        Name = 'ToolBox'
        DataType = ftWideString
        Size = 20
      end
      item
        Name = 'Status'
        DataType = ftShortint
        Precision = 15
      end
      item
        Name = 'IsOnline'
        DataType = ftBoolean
      end
      item
        Name = 'LastTimeStamp'
        DataType = ftDateTime
      end
      item
        Name = 'ToolID'
        DataType = ftInteger
        Precision = 15
      end
      item
        Name = 'ToolIden'
        DataType = ftWideString
        Size = 20
      end
      item
        Name = 'ToolName'
        DataType = ftWideString
        Size = 20
      end
      item
        Name = 'PC'
        DataType = ftWideString
        Size = 2
      end
      item
        Name = 'RSSI'
        DataType = ftShortint
        Precision = 15
      end
      item
        Name = 'EPC'
        DataType = ftWideString
        Size = 12
      end
      item
        Name = 'InBox'
        DataType = ftBoolean
      end>
    IndexDefs = <>
    Params = <>
    DataDriver = DataSetDriverEh1
    StoreDefs = True
    TreeList.Active = True
    TreeList.KeyFieldName = 'BID'
    TreeList.RefParentFieldName = 'ToolBoxID'
    Left = 88
    Top = 136
  end
  object DataSetDriverEh1: TDataSetDriverEh
    ProviderDataSet = FDQuery1
    Left = 176
    Top = 136
  end
  object FDQuery4: TFDQuery
    Connection = FDConnection1
    Left = 456
    Top = 72
  end
end
