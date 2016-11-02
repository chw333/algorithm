{ BOI'99  Penktoji Baltijos ÷aliù informatikos olimpiada }
{ Ryga, Latvija }
{ Uıdavinys Eilußiù jungimas }

{ Sprendimİ parengó Justas Kranauskas, VTGTM liójus, 12 kl. }

{Idója:
    naudoju paie÷kos õ plotõ algoritmİ, t.y. kiekvienİ pirmo rinkinio
eilutñ palyginu su kiekviena eilute i÷ antrojo rinkinio, jeigu viena i÷ jù
yra kitos pradıia, õtraukiu jas õ eilñ. Pvz.:
    'ABC' i÷ pirmo rinkinio ir 'AB' i÷ antrojo - antroji yra pirmosios
pradıia, todól jas õtraukiu õ eilñ. Eilóje i÷saugau likusiİ galûne ('C'),
i÷ kurio rinkinio eilutós ÷i galûnó (pirmo), bendros sudarytos eilutós
ilgõ (2) bei kokios eilutós yra sudarytoje eilutóje i÷ pirmo ir antro
rinkinio. Tikrindamas, kad nesusidarytù ciklas, pvz.:
ABC+BC+BC+BC+BC...
AB+CB+CB+CB+CB...
õ eilñ neõtraukiu naujù pana÷iù, bet ilgesniù dariniù, t.y. turinßiù tİ
paßiİ galûnñ, pvz. eilóje bus tokia informacija:

galûnó:  ilgis:  ...

(AB)C      2     ...
(AB)

tada õ eilñ nebeõtraukiu tokio darinio:

galûnó:   ilgis:

(ABC+B)C    4
(AB+CB)

Kai palyginu abu rinkinius, tada bandau pridóti kiekvienİ eilutñ i÷
rinkinio (priklausomai nuo to, kuriam i÷ jù priklauso likusi galûnó) prie
kiekvieno eilós elemento. Taip auginu bendrİ eilutñ, kol galù gale nebelieka
jokios galûnós arba eilóje nebelieka nei÷nagrinótù elementù.
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
      q : fino;                       {eiló}
      l : sarasas;                    {pagalbinis sİra÷as}
  procedure naujas_atsakymas (inf : info; var ats : atsak);
  {patikrina, ar naujas atsakymas geresnis (sudaryta trumpesnó eilutó)
  uı anksßiau gautİ}
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
  {sİra÷İ papildo nauju elementu}
    var tmp : sarasas;
  begin
    new (tmp);
    tmp^.t := l;
    tmp^.is := b;
    l := tmp;
  end;
  function tinka (inf : info; var inf2 : info; ii : byte;
                  var baigta : boolean; pirm : boolean) : boolean;
  {patikrina, ar prie sudarytos eilutós galima prijungti tikrinamİ}
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
      {eilußiù galûnós sutampa - rastas naujas atsakymas}
        begin
          baigta := true;
          inf2.s := '';
          inc (inf2.ilg, ls);
          ok := true;
        end
      else if linfs > ls
        then if pos (s, inf2.s) = 1
          then
          {tikrinama eilutó trumpesnó uı sudarytos eilutós galûnñ}
            begin
              delete (inf2.s, 1, ls);
              inc (inf2.ilg, ls);
              ok := true;
            end
          else
        else if pos (inf2.s, s) = 1
          then
          {tikrinama eilutó ilgesnó uı sudarytos eilutós galûnñ}
            begin
              delete (s, 1, linfs);
              inf2.s := s;
              inc (inf2.ilg, linfs);
              inf2.pirm := pirm;
              ok := true;
            end;
    if ok
    {jeigu galima pridóti tikrinamİ eilutñ, reikia papildyti eilußiù sİra÷İ
    (reikós spausdinant atsakymİ)}
      then if pirm
        then pridek (inf2.la, ii)
        else pridek (inf2.lb, ii);
    tinka := ok;
  end;
  procedure itrauk_eilen (inf : info);
  {õtraukia naujİ galûnñ ir kitİ su ja susijusiİ informacijİ õ eilñ}
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
          writeln ('Perpildyta eiló!');
          halt;
        end;
    inc (galva);
    q[galva] := inf;
  end;
  procedure spausdink (l : sarasas; b : boolean);
  {spausdina eilutes i÷ sİra÷o sİlygoje reikalaujamu formatu}
  begin
    if l^.t <> nil
      then spausdink (l^.t, b);
    if b
      then write (f, rinka[l^.is], '+')
      else write (f, rinkb[l^.is], '+')
  end;
  procedure paieska_i_ploti;
  {tikrina visus galimus eilußiù variantus paie÷kos õ plotõ algoritmu}
    var i, ii : integer;
        inf, inf2 : info;
        baigta : boolean;
  begin
    galva := 0;
    ats.la := nil;
    ats.lb := nil;
    ats.ilg := maxint;
    for i := 1 to a do
    {õ eilñ õtraukiamos galûnós, gaunamos i÷ rinkiniù A ir B eilußiù, kuriù
    pradıios atitinkamai sutampa}
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
              {gali bûti, kad skirtinguose rinkiniuose yra vienodos eilutós,
              i÷kart gauname vienİ atsakymİ}
              else naujas_atsakymas (inf2, ats);
      end;
    uodega := 0;
    while galva <> uodega do
    {tikrinami visi eilós elementai}
      begin
        inc (uodega);
        inf := q[uodega];
        if inf.pirm
          then
          {prie galûnós likusios nuo pirmojo rinkinio eilußiù bandoma
          prijungti visas eilutes i÷ antrojo rinkinio}
            for i := 1 to b do
              if tinka (inf, inf2, i, baigta, false)
                then if not baigta
                  then itrauk_eilen (inf2)
                  else naujas_atsakymas (inf2, ats)
                else
          else
          {prie galûnós likusios nuo antrojo rinkinio eilußiù bandoma
          prijungti visas eilutes i÷ pirmojo rinkinio}
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