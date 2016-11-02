program reiskiniai_su_dalyba;
   const PR = 'DIV.IN';
         RZ = 'DIV.OUT';
         MAX_N = 10000;
   type skaiciai = array [1..MAX_N] of longint;

  function bdd (a, b: longint): longint;
  begin
    if b = 0 then bdd := a
             else bdd := bdd (b, a mod b)
  end; { bdd }

  function tikrinti (var f: text; n: longint): boolean;
    { ar galima gauti nauj… reižkin, kad jo reikžm‚ b–t— sveikasis skai‡ius }
    var i, sk, vard: longint;
  begin
    readln (f, sk);
    readln (f, vard);
    n := n - 2;
    vard := vard div bdd(sk, vard);
    while (vard > 1) and (n > 0) do
      begin
        readln (f, sk);
        vard := vard div bdd(sk, vard);
        n := n - 1;
      end;
    { perskaitome likusius narius }
    for i := 1 to n do
      readln (f, n);
    tikrinti := vard = 1;
  end; { tikrinti }

  var f, g: text;
      d, i, n: longint;
      galima: boolean;
begin
  assign (f, PR);
  assign (g, RZ);
  reset (f);
  rewrite (g);
  readln (f, d);
  for i := 1 to d do
    begin
      readln (f, n);
      galima := tikrinti (f, n);
      if galima
         then writeln (g, 'YES')
         else writeln (g, 'NO');
    end;
  close (f);
  close (g);
end.