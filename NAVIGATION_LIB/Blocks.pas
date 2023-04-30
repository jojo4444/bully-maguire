
{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

unit Blocks;

interface

uses {$IFDEF FPC} DynLibs, {$ELSE} Windows, {$ENDIF}
 Classes, DataTypes, SysUtils, abstract_im_interface, RunObjts, uExtMath;


type

  TPharosNavigation = class(TRunObject)
  public
    function       InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;override;
    function       RunFunc(var at,h : RealType;Action:Integer):NativeInt;override;
    function       GetParamID(const ParamName:string;var DataType:TDataType;var IsConst: boolean):NativeInt;override;
  end;
type

  TAstronomicalNavigation = class(TRunObject)
  public
    function       InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;override;
    function       RunFunc(var at,h : RealType;Action:Integer):NativeInt;override;
    function       GetParamID(const ParamName:string;var DataType:TDataType;var IsConst: boolean):NativeInt;override;
  end;


Type TDllPolarСircle = record
    lat : Double;
    lon   : Double;
    d     : Double;
end;
Type PDllPolarСircle = ^TDllPolarСircle;

Type TDllPoint = record
    x   : Double;
    y   : Double;
    z   : Double;
end;
Type PDllPoint = ^TDllPoint;

Type TDllCelestialSpherePoint = record
    phi   : Double;
    delta : Double;
    t     : Double;
end;
Type PDllCelestialSpherePoint = ^TDllCelestialSpherePoint;

var
  hcalcHandler: {$IFDEF FPC}TLibHandle{$ELSE}THandle{$ENDIF};
  PHAROS_CALC: function(n : integer; i : PDllPolarСircle; o : PDllPoint): integer; cdecl;
  ASTRONOMICAL_CALC: function(n : integer; i : PDllCelestialSpherePoint; o : PDllPoint): integer; cdecl;


implementation

function    TPharosNavigation.GetParamID;
begin
  Result:=inherited GetParamId(ParamName,DataType,IsConst);
  if Result = -1 then begin
  end
end;

function TPharosNavigation.InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;
  var i: integer;
begin
  Result:=0;
  case Action of
    i_GetCount:     begin
                      cY[0] := 3;
                      for i:= 0 to cY.count - 1 do
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

function   TPharosNavigation.RunFunc;
   var 
    j : integer;
    i : array of TDllPolarСircle;
    o : TDllPoint;
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
                     i[j].lat := Double(U[j].arr^[0]);
                     i[j].lon := Double(U[j].arr^[1]);
                     i[j].d := Double(U[j].arr^[2]);
                  end;
                r := PHAROS_CALC(cU.count, PDllPolarСircle(i), @o);
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

function TAstronomicalNavigation.GetParamID;
begin
  Result:=inherited GetParamId(ParamName,DataType,IsConst);
  if Result = -1 then begin
  end
end;

function TAstronomicalNavigation.InfoFunc(Action: integer;aParameter: NativeInt):NativeInt;
  var i: integer;
begin
  Result:=0;
  case Action of
    i_GetCount:     begin
                      cY[0] := 3;
                      if cY.count < 1 then begin
                            ErrorEvent('Ошибка: кол-во выходов < 1', msError, VisualObject);
                            Result:=r_Fail;
                            exit;
                      end;
                      if cU.count < 4 then begin
                            ErrorEvent('Ошибка: кол-во входов < 4', msError, VisualObject);
                            Result:=r_Fail;
                            exit;
                      end;
                      if cU[0] <> 1 then begin
                            ErrorEvent('Ошибка: размерность первого входа входа != 1', msError, VisualObject);
                            Result:=r_Fail;
                            exit;
                      end;

                      for i:= 1 to cY.count - 1 do
                        begin
                          if cU[i] <> 2 then begin
                            ErrorEvent('Ошибка: размерность входа != 2', msError, VisualObject);
                            Result:=r_Fail;
                            exit;
                          end;
                        end;


                    end;
  else
    Result:=inherited InfoFunc(Action,aParameter);
  end
end;

function   TAstronomicalNavigation.RunFunc;
   var
    j : integer;
    i : array of TDllCelestialSpherePoint;
    o : TDllPoint;
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
                for j := 1 to cU.count - 1 do
                  begin
                     i[j].phi := Double(U[0].arr^[0]);
                     i[j].delta := Double(U[j].arr^[1]);
                     i[j].t := Double(U[j].arr^[2]);
                  end;
                r := ASTRONOMICAL_CALC(cU.count, PDllCelestialSpherePoint(i), @o);
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
  PHAROS_CALC:=GetProcAddress(hcalcHandler,'pharosCalc');
  ASTRONOMICAL_CALC:= GetProcAddress(hcalcHandler,'astronomicCalc');
finalization
  if hcalcHandler <> 0 then FreeLibrary(hcalcHandler);
end.
