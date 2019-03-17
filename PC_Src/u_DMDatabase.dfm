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
      
        'select 0 PID, ID, IDEN, Name, NULL RSSI, NULL PC, NULL EPC, 0 In' +
        'Box, ID BoxID from tbToolBox'
      'union'
      
        'select BID PID, ID, IDEN, Name, RSSI, PC, EPC, InBox, NULL BOXID' +
        ' from tbTools')
    Left = 176
    Top = 64
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 168
    Top = 136
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 88
    Top = 8
  end
  object DataSetDriverEh1: TDataSetDriverEh
    ProviderDataSet = FDQuery1
    Left = 264
    Top = 64
  end
  object FDQuery4: TFDQuery
    Connection = FDConnection1
    SQL.Strings = (
      'select IDEN from tbToolBox'
      'union'
      'select IDEN from tbTools')
    Left = 456
    Top = 72
  end
  object MemTableEh1: TMemTableEh
    Params = <>
    DataDriver = DataSetDriverEh1
    Left = 80
    Top = 136
  end
end
