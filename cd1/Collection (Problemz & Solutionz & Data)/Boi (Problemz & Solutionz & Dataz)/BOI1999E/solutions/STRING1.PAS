{ BOI'99  Penktoji Baltijos �ali� informatikos olimpiada }
{ Ryga, Latvija }
{ U�davinys Eilu�i� jungimas }

{ Sprendim� pareng� Justas Kranauskas, VTGTM li�jus, 12 kl. }

{Id�ja:
    naudoju paie�kos � plot� algoritm�, t.y. kiekvien� pirmo rinkinio
eilut� palyginu su kiekviena eilute i� antrojo rinkinio, jeigu viena i� j�
yra kitos prad�ia, �traukiu jas � eil�. Pvz.:
    'ABC' i� pirmo rinkinio ir 'AB' i� antrojo - antroji yra pirmosios
prad�ia, tod�l jas �traukiu � eil�. Eil�je i�saugau likusi� gal�ne ('C'),
i� kurio rinkinio eilut�s �i gal�n� (pirmo), bendros sudarytos eilut�s
ilg� (2) bei kokios eilut�s yra sudarytoje eilut�je i� pirmo ir antro
rinkinio. Tikrindamas, kad nesusidaryt� ciklas, pvz.:
ABC+BC+BC+BC+BC...
AB+CB+CB+CB+CB...
� eil� ne�traukiu nauj� pana�i�, bet ilgesni� darini�, t.y. turin�i� t�
pa�i� gal�n�, pvz. eil�je bus tokia informacija:

gal�n�:  ilgis:  ...

(AB)C      2     ...
(AB)

tada � eil� nebe�traukiu tokio darinio:

gal�n�:   ilgis:

(ABC+B)C    4
(AB+CB)

Kai palyginu abu rinkinius, tada bandau prid�ti kiekvien� eilut� i�
rinkinio (priklausomai nuo to, kuriam i� j� priklauso likusi gal�n�) prie
kiekvieno eil�s elemento. Taip auginu bendr� eilut�, kol gal� gale nebelieka
jokios gal�n�s arba eil�je nebelieka nei�nagrin�t� element�.
}
program eilutes;
  const ilg = 50;
        maxn = 100;
        maxq = 500;
  type string_ilg = string[ilg];
       rinkinys = array [1..maxn] of string_ilg;
       sarasas = ^elem;
       elem = record
                is : byte;
                t : sarasas;
              end;
       info = record
                s : string_ilg;
                pirm : boolean;
                ilg : integer;
                la, lb : sarasas;
              end;
       atsak = record
                 la, lb : sarasas;
                 ilg : integer;
               end;
       fino = array [1..maxq] of info; {First In Never Out}
  var f : text;
      rinka, rinkb : rinkinys;
      a, b : byte;
      i, galva, uodega : integer;
      ats : atsak;                    {geriausias atsakymas}
      q : fino;                       {eil�}
      l : sarasas;                    {pagalbinis s�ra�as}
  procedure naujas_atsakymas (inf : info; var ats : atsak);
  {patikrina, ar naujas atsakymas geresnis (sudaryta trumpesn� eilut�)
  u� anks�iau gaut�}
  begin
    if inf.ilg < ats.ilg
      then
        begin
          ats.la := inf.la;
          ats.lb := inf.lb;
          ats.ilg := inf.ilg;
        end;
  end;
  procedure pridek (var l : sarasas; b : byte);
  {s�ra�� papildo nauju elementu}
    var tmp : sarasas;
  begin
    new (tmp);
    tmp^.t := l;
    tmp^.is := b;
    l := tmp;
  end;
  function tinka (inf : info; var inf2 : info; ii : byte;
                  var baigta : boolean; pirm : boolean) : boolean;
  {patikrina, ar prie sudarytos eilut�s galima prijungti tikrinam�}
    var linfs, ls : byte;
        s : string;
        ok : boolean;
  begin
    inf2 := inf;
    if pirm
      then s := rinka[ii]
      else s := rinkb[ii];
    linfs := length (inf2.s);
    ls := length (s);
    ok := false;
    baigta := false;
    if (ls = linfs) and (s = inf2.s)
      then
      {eilu�i� gal�n�s sutampa - rastas naujas atsakymas}
        begin
          baigta := true;
          inf2.s := '';
          inc (inf2.ilg, ls);
          ok := true;
        end
      else if linfs > ls
        then if pos (s, inf2.s) = 1
          then
          {tikrinama eilut� trumpesn� u� sudarytos eilut�s gal�n�}
            begin
              delete (inf2.s, 1, ls);
              inc (inf2.ilg, ls);
              ok := true;
            end
          else
        else if pos (inf2.s, s) = 1
          then
          {tikrinama eilut� ilgesn� u� sudarytos eilut�s gal�n�}
            begin
              delete (s, 1, linfs);
              inf2.s := s;
              inc (inf2.ilg, linfs);
              inf2.pirm := pirm;
              ok := true;
            end;
    if ok
    {jeigu galima prid�ti tikrinam� eilut�, reikia papildyti eilu�i� s�ra��
    (reik�s spausdinant atsakym�)}
      then if pirm
        then pridek (inf2.la, ii)
        else pridek (inf2.lb, ii);
    tinka := ok;
  end;
  procedure itrauk_eilen (inf : info);
  {�traukia nauj� gal�n� ir kit� su ja susijusi� informacij� � eil�}
    var i, ii : integer;
  begin
    for i := 1 to galva do
      if (q[i].s = inf.s) and (q[i].pirm = inf.pirm)
        then if q[i].ilg > inf.ilg
          then
            begin
              dec (galva);
              for ii := i to galva do
                q[ii] := q[ii + 1];
              {fillchar (q[galva + 1], sizeof (q[galva + 1]), 0);}
              break;
            end
          else exit;
    if galva = maxq
      then
        begin
          writeln ('Perpildyta eil�!');
          halt;
        end;
    inc (galva);
    q[galva] := inf;
  end;
  procedure spausdink (l : sarasas; b : boolean);
  {spausdina eilutes i� s�ra�o s�lygoje reikalaujamu formatu}
  begin
    if l^.t <> nil
      then spausdink (l^.t, b);
    if b
      then write (f, rinka[l^.is], '+')
      else write (f, rinkb[l^.is], '+')
  end;
  procedure paieska_i_ploti;
  {tikrina visus galimus eilu�i� variantus paie�kos � plot� algoritmu}
    var i, ii : integer;
        inf, inf2 : info;
        baigta : boolean;
  begin
    galva := 0;
    ats.la := nil;
    ats.lb := nil;
    ats.ilg := maxint;
    for i := 1 to a do
    {� eil� �traukiamos gal�n�s, gaunamos i� rinkini� A ir B eilu�i�, kuri�
    prad�ios atitinkamai sutampa}
      begin
        inf.s := rinka[i];
        inf.pirm := true;
        inf.ilg := 0;
        inf.la := nil;
        inf.lb := nil;
        pridek (inf.la, i);
        baigta := false;
        for ii := 1 to b do
          if tinka (inf, inf2, ii, baigta, false)
            then if not baigta
              then itrauk_eilen (inf2)
              {gali b�ti, kad skirtinguose rinkiniuose yra vienodos eilut�s,
              i�kart gauname vien� atsakym�}
              else naujas_atsakymas (inf2, ats);
      end;
    uodega := 0;
    while galva <> uodega do
    {tikrinami visi eil�s elementai}
      begin
        inc (uodega);
        inf := q[uodega];
        if inf.pirm
          then
          {prie gal�n�s likusios nuo pirmojo rinkinio eilu�i� bandoma
          prijungti visas eilutes i� antrojo rinkinio}
            for i := 1 to b do
              if tinka (inf, inf2, i, baigta, false)
                then if not baigta
                  then itrauk_eilen (inf2)
                  else naujas_atsakymas (inf2, ats)
                else
          else
          {prie gal�n�s likusios nuo antrojo rinkinio eilu�i� bandoma
          prijungti visas eilutes i� pirmojo rinkinio}
            for i := 1 to a do
              if tinka (inf, inf2, i, baigta, true)
                then if not baigta
                  then itrauk_eilen (inf2)
                  else naujas_atsakymas (inf2, ats);
      end;
  end;
begin
  assign (f, 'match.in');
  reset (f);
  readln (f, a);
  for i := 1 to a do
    readln (f, rinka[i]);
  readln (f, b);
  for i := 1 to b do
    readln (f, rinkb[i]);
  close (f);
  paieska_i_ploti;
  assign (f, 'match.out');
  rewrite (f);
  if ats.ilg < maxint
    then
      begin
        writeln (f, ats.ilg);
        spausdink (ats.la^.t, true);
        writeln (f, rinka[ats.la^.is]);
        spausdink (ats.lb^.t, false);
        writeln (f, rinkb[ats.lb^.is]);
      end
    else writeln (f, 0);
  close (f);
end.