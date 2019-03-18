unit uCommonDef;

interface
uses
  Classes, SysUtils;
type
  PToolInfoRec = ^TToolInfoRec;
  TToolInfoRec = packed Record
    RSSI: Byte;
    PC: SmallInt;
    EPC: Array[0..11] of Byte;
    function PC_String: AnsiString;
    function EPC_String: AnsiString;
  End;
implementation

{ TToolInfoRec }

function TToolInfoRec.EPC_String: AnsiString;
begin
  SetLength(Result, 24);
  BinToHex(Pointer(@EPC), PAnsiChar(@Result[1]), 12);
end;



function TToolInfoRec.PC_String: AnsiString;
begin
  SetLength(Result, 4);
  BinToHex(Pointer(@PC), PAnsiChar(@Result[1]), 2);
end;

end.
