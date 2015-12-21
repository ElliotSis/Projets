program chiffrementParBloc;

uses sysutils;

function decToBin(n : Integer) : String;
var Result : String;
  i : Integer;
begin
  Result := '';
  for i := 0 to 3 do
    if n and (1 shl i) <> 0 then Result := '1' + Result
                                  else Result := '0' + Result;
  decToBin := Result;
end;

Function BinToDec (Bin : String) : Word;
Var
  i, L : Integer;
  Result : Word;
Begin
  Result := 0;
  L := Length(Bin);
  for i := 1 to L do
    if Bin[i] = '1' then Result := Result + (1 shl (L - i));
  BinToDec := Result;
End;

procedure crypte(var a : Integer; var b : Integer; t, k : Integer);
var tmp : Integer;
begin
	if t = 0 then
	begin
		tmp := k xor b;
		a := a xor tmp;
	end
	else
	begin
		tmp := b;
		b := (k xor b) xor a;
		a := tmp;
		crypte(a,b, t-1, k)
	end;
end;

var a, b : Integer;
	bin : String;
	donnees, lol : Text;
begin
	assign(donnees, 'donnees.txt');
	assign(lol, 'lol.txt');
	append(lol);
	reset(donnees);
	while not(eof(donnees)) do
	begin	
		readln(donnees, bin);
		a := BinToDec(copy(bin, 1, 4));
		b := BinToDec(copy(bin, 5, 9)); 
		crypte(a, b, 3, 10);
		writeln(lol, decToBin(a) + decToBin(b));
	end;
	close(donnees)
end.
