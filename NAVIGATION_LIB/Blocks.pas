

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

unit Blocks;


interface

uses {$IFDEF FPC} DynLibs, {$ELSE} Windows, {$ENDIF}
 Classes, DataTypes, SysUtils, abstract_im_interface, RunObjts, uExtMath;


type

  Navigation = class(TRunObject)
  public
    function       InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;override;
    function       RunFunc(var at,h : RealType;Action:Integer):NativeInt;override;
    function       GetParamID(const ParamName:string;var DataType:TDataType;var IsConst: boolean):NativeInt;override;
  end;


Type TDllIn = record
    alpha : Double;
    phi   : Double;
    d     : Double;
end;
Type PDllIn = ^TDllIn;

Type TDllOut = record
    x   : Double;
    y   : Double;
    z   : Double;
end;
Type PDllOut = ^TDllOut;

var
  hcalcHandler: {$IFDEF FPC}TLibHandle{$ELSE}THandle{$ENDIF};
  CALC: function(n : integer; i : PDllIn; o : PDllOut): integer; cdecl;
  
implementation

function    Navigation.GetParamID;
begin
  Result:=inherited GetParamId(ParamName,DataType,IsConst);
  if Result = -1 then begin
  end
end;

function Navigation.InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;
  var i: integer;
begin
  Result:=0;
  case Action of
    i_GetCount:     begin
                      cY[0] := 3;
                      if CU.Count < 3 then begin
                        ErrorEvent('Ошибка кол-во точек < 3', msError, VisualObject);
                        Result:=r_Fail;
                        exit;
                      end;
                      
                      for i:= 0 to cU.count - 1 do 
                        begin
                          if cU[i] <> 3 then begin
                            ErrorEvent('Ошибка: размерность входа != 3', msError, VisualObject);
                            Result:=r_Fail;
                            exit;
                          end;
                        end;
                        

                    end;
  else
    Result:=inherited InfoFunc(Action,aParameter);
  end
end;

function   Navigation.RunFunc;
   var 
    j : integer;
    i : array of TDllIn;
    o : TDllOut;
    r : integer;
begin
 Result:=0;
 case Action of
   f_InitState:
              begin
                        Y[0].arr^[0] := 0;
                        Y[0].arr^[1] := 0;
                        Y[0].arr^[2] := 0;
              end;
   f_UpdateOuts,
   f_GoodStep:
              begin
                if hcalcHandler = 0 then
                  begin
                    ErrorEvent('Ошибка. Не подгружена внешняя библиотека', msError, VisualObject);
                    Result:=r_Fail;
                    exit;
                  end;

                SetLength(i, cU.count);
                for j := 0 to cU.count - 1 do 
                  begin
                     i[j].alpha := Double(U[j].arr^[0]);
                     i[j].phi := Double(U[j].arr^[1]);
                     i[j].d := Double(U[j].arr^[2]);
                  end;
                r := CALC(cU.count, PDllIn(i), @o);
                Y[0].arr^[0] := o.x;
                Y[0].arr^[1] := o.y;
                Y[0].arr^[2] := o.z;
                if r = -1 then
                  begin
                    ErrorEvent('Ошибка расчетов', msError, VisualObject);
                    Result:=r_Fail;
                    exit;
                  end;
              end;
 end
end;

initialization
  hcalcHandler := LoadLibrary('solextr.dll');
  CALC:=GetProcAddress(hcalcHandler,'calc');
finalization
  if hcalcHandler <> 0 then FreeLibrary(hcalcHandler);
end.
