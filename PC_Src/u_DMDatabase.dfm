object dmDatabase: TdmDatabase
  OldCreateOrder = False
  Height = 414
  Width = 567
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=D:\WORK\Io_Box\IotBox_Uv4\PC_Src\Win32\Debug\ToolDB'
      'DriverID=SQLite')
    Left = 88
    Top = 64
  end
  object DataSource1: TDataSource
    Left = 248
    Top = 72
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 88
    Top = 8
  end
  object fdqModify: TFDQuery
    Connection = FDConnection1
    SQL.Strings = (
      'select IDEN from tbToolBox'
      'union'
      'select IDEN from tbTools')
    Left = 456
    Top = 72
  end
  object FDMemTable1: TFDMemTable
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    Left = 336
    Top = 72
  end
  object fdaBoxes: TFDTableAdapter
    UpdateTableName = 'tbToolBox'
    DatSTableName = 'fdmBoxes'
    SelectCommand = fdcBoxes
    Left = 120
    Top = 152
  end
  object fdaTools: TFDTableAdapter
    DatSTableName = 'fdmTools'
    SelectCommand = fdcTools
    Left = 120
    Top = 224
  end
  object fdcBoxes: TFDCommand
    Connection = FDConnection1
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    CommandText.Strings = (
      ''
      'select * from tbToolBox')
    Left = 64
    Top = 152
  end
  object fdcTools: TFDCommand
    Connection = FDConnection1
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    CommandText.Strings = (
      ''
      'select * from tbTools')
    Left = 64
    Top = 224
  end
  object fdmBoxes: TFDMemTable
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    Adapter = fdaBoxes
    Left = 184
    Top = 152
  end
  object fdmTools: TFDMemTable
    MasterSource = dsBoxes
    MasterFields = 'ID'
    DetailFields = 'BID'
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    Adapter = fdaTools
    Left = 184
    Top = 224
  end
  object dsBoxes: TDataSource
    DataSet = fdmBoxes
    Left = 240
    Top = 152
  end
  object dsTools: TDataSource
    DataSet = fdmTools
    Left = 240
    Top = 224
  end
end
