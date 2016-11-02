{ BOI'99 Penktoji Baltijos ali— informatikos olimpiada }
{ Ryga, Latvija }
{ Penktas u‘davinys NAUJA FUNKCIJA }

{ Sprendim… pareng‚ Jurgis Paukonis, VTGTM lic‚jus, 10 kl. }

{ IDJA: GavŠ nauj… duomen— eilutŠ, j… 'suspaud‘iame'  skai‡ius nuo 1
  iki 4: ma‘iausi… skai‡i— paver‡iame 1 (jei ma‘iausi— yra keli, tai
  visus paver‡iame 1), antrus pagal didum… paver‡iame 2 ir taip toliau
  (skai‡i— nuo 1 iki 4 u‘tenka. Net jei visi pradiniai duomenys b–t— visi
  skirtingi, tai gautume 1, 2, 3, 4).

  Turime masyv… i keturi— element—, kuriame saugome vis— jau buvusi—
  duomen— rinkini—, paverst—  skai‡ius nuo 1 iki 4, atsakymus.

  Taigi, gavŠ nauj… eilutŠ j… paver‡iame  skai‡ius nuo 1 iki 4; jei toks
  atsakymas jau yra, tuomet parenkame atitinkam… duomen ir j atspausdiname,
  jei ne, ikvie‡iame sen… funkcij…, ir gaut… atsakym… iraome  masyv….

  Tokiu atveju funkcija FUN bus kvie‡iama < 256 kart— ir su maksimaliais
  duomenimis nevirys laiko limito.  }

program newfun;

uses funit;
type mas = array [1 .. 4] of integer;

procedure conv (a : mas; var ca : mas);
{ funkcija, suspaud‘ianti duomenis  skai‡ius nuo 1 iki 4 }
  var c, min, liko, n : integer;
begin
  liko := 4; n := 1;
  while liko > 0 do
  begin
    min := 0;
    for c := 1 to 4 do  { randame ma‘iausi… i dar nepaverst— skai‡i— }
      if (a[c] > 0) and ((min = 0) or (a[c] < min)) then min := a[c];
    for c := 1 to 4 do  { visus skai‡ius lygius ma‘iausiam paver‡iame
                           n, kuris prad‘ioje lygus 1, o kiekvien… kart…,
                          pavertus vienodus skai‡ius, padidinamas }
      if a[c] = min then begin
                           ca[c] := n;
                           dec (liko);
                           a[c] := 0
                         end;
    inc (n)
  end;
end;

  var a, ca : mas;
      ma, fa : byte;
      m : array [1 .. 4, 1 .. 4, 1 .. 4, 1 .. 4] of byte;
      n, c : integer;
      f1, f2 : text;

begin
  assign (f1, 'newfun.in'); reset (f1);
  assign (f2, 'newfun.out'); rewrite (f2);
  readln (f1, n);
  fillchar (m, sizeof(m), 0);      { prad‘ioje ne‘inome nei vieno atsakymo }
  for c := 1 to n do
  begin
    readln (f1, a[1], a[2], a[3], a[4]);
    conv (a, ca);                { paver‡iame nuskaityt… eilutŠ }
    ma := m[ca[1],ca[2],ca[3],ca[4]];
    if ma = 0 then { jei tokio atsakymo dar n‚ra, su‘inome j ir raome  m }
     begin
       fa := fun(ca[1],ca[2],ca[3],ca[4]);
       m[ca[1],ca[2],ca[3],ca[4]] := fa;
       ma := fa
     end;
    if ma = ca[1] then writeln (f2, a[1])   { atver‡iame rezultat… atgal }
       else if ma = ca[2] then writeln (f2, a[2])
       else if ma = ca[3] then writeln (f2, a[3])
            else writeln (f2, a[4])
  end;
  close (f1); close (f2);
end.