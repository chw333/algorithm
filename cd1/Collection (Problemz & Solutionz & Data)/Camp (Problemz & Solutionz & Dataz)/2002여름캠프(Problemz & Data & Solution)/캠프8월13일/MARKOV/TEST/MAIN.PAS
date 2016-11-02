unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls;

type
  TForm1 = class(TForm)
    UpDown1: TUpDown;
    Label1: TLabel;
    Label2: TLabel;
    edtStandard: TEdit;
    Label3: TLabel;
    edtTest: TEdit;
    Button1: TButton;
    lblResult: TLabel;
    edtPoint: TEdit;
    procedure UpDown1ChangingEx(Sender: TObject; var AllowChange: Boolean;
      NewValue: Smallint; Direction: TUpDownDirection);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.UpDown1ChangingEx(Sender: TObject;
  var AllowChange: Boolean; NewValue: Smallint;
  Direction: TUpDownDirection);
begin
  edtStandard.Text := 'markov.ou' + IntToStr(NewValue);
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  F1, F2: TextFile;
  S1, S2: string;
  i, j, k, Line: Integer;
  Same: Boolean;
  t: string;
begin
  lblResult.Caption := '比较结果：';
  AssignFile(F1, edtStandard.Text);
  AssignFile(F2, edtTest.Text);
  Reset(F1); Reset(F2);
  Same := True;
  Line := 0;
  while Same and not Eof(F1) and not Eof(F2) do
  begin
    Inc(Line);
    ReadLn(F1, S1); ReadLn(F2, S2);
    if S1 <> S2 then
    begin
      for k := Length(S1) downto 1 do
        if S1[k] <> ' ' then Break;
      Delete(S1, k + 1, Length(S1) - k);
      for k := Length(S2) downto 1 do
        if S2[k] <> ' ' then Break;
      Delete(S2, k + 1, Length(S2) - k);
      if Length(S1) <> Length(S2) then
      begin
        Same := False;
        Break;
      end;
      j := 1;
      for i := 1 to Length(S1) do
        if S1[i] = ' ' then
        begin
          t := Copy(S1, j, i - j);
          if Pos(t, S2) = 0 then
          begin
            Same := False;
            Break;
          end;
          j := i + 1;
        end;
    end;
  end;
  if Eof(F1) <> Eof(F2) then Same := False;
  if Same then lblResult.Caption := '比较结果：' + '相同'
  else lblResult.Caption := '比较结果：' + '第' + IntToStr(Line) + '行不同';
  CloseFile(F1); CloseFile(F2);
end;

end.
