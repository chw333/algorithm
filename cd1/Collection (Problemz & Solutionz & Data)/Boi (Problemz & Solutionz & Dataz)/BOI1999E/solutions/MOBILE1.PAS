{ BOI'99 Penktoji Baltijos ali— informatikos olimpiada }
{ Ryga, Latvija }
{ Ÿetas u‘davinys SVERTAS }

{ Sprendim… pareng‚ Jurgis Paukonis, VTGTM lic‚jus, 10 kl. }

{ IDJA: Surikiuojame pakabas pagal gyl (gylis rodo per kiek kit—
  pakabu pritvirtinta ta pakaba). Tada nuo apatiniame lygyje esan‡i—
  pakaba— visas i eil‚s bandome sud‚ti taip, kad jos b–t— pusiausvyros
  b–senoje. Rekursikai ibandome visus variantus.

  Kadangi pradedame nuo giliausiai esan‡i— pakab—, tai vis— nagrin‚jamame
  lygyje esan‡i— pakab— ant kuri— kas nors kabo, mas‚s jau bus ‘inomos.

  Algoritmas veikia gana greitai, nes negalima naudoti t— pa‡i— pasvar—
  du kartus, o ant vienos pakabos kaba ne daugiau 7 svori— (i kuri— keli
  gali b–ti ‘inomi i ankstesni— ‘ingsni—).
}



program svertas;
type pakaba = record
                n, m, mm, gl, k : integer;
                { n - kiek ant pakabos yra prikabinim—,
                  (m ir mm iraoma ir naudojama tik rekursiskai bandant suka-
                   binti svars‡ius)
                  m - visos pakabos mas‚,
                  mm - vis— prikabinam— masi— ir atstum— sandaug— suma
                            (baigus kabinti turi b–ti 0),
                  gl - pakabos gylis,
                  k - kelinta i pakaba buvo prie surikiuojant pagal gyl
                       (reikalinga, kad nustatytume ryius tarp pakab— po su -
                        rikiavimo) }
                pr : array [1 .. 7] of record
                                        l, p, m : integer
                                      end
                    { prikabinimai.
                        l - atstumas,
                        p - nuoroda  kit… pakab…, jei 0, tai kaba svarstis
                        m - prikabinimo mas‚ (raoma tik rekursikai bandant
                             sukabinti svars‡ius) }
              end;
     buvo_naudoti = array [1 .. 17] of boolean;


  var np, n : integer;
        { np - kiek yra pakab—,
          n - kiek prikabinim— svars‡iams, t.y. kiek galime naudoti svars‡i— }
      p : array [1 .. 17] of pakaba;
           { visos pakabos }
      sudetas : boolean; { ar jau rastas atsakymas }
      ch : char;
      f : text;
      a : pakaba;
      ck, c : integer;
      m : array [1 .. 17] of integer;
      bv : buvo_naudoti;

  procedure skaitom (gl : integer);
      { proced–ra, rekursikai nuskaitanti pradinius duomenis,
         gl - kokiame gylyje dabar skaitome }
    var ch : char;
        s : string[3];
        c, k : integer;
          { k - kelinta ‡ia pakaba }
  begin
    k := np;
    p[k].n := 0; p[k].k := k; p[k].gl := gl;
    read (f, ch);
    while ch <> ')' do   { kol nepasibaig‚ itos pakabos apraymas }
      begin
        s := '';
        inc (p[k].n);
        while ch in ['0'..'9','-'] do begin s := s + ch; read (f, ch) end;
          { suformuojame s - skai‡i— parodant, kokiu atstumu yra
            prikabinimas }
        val (s, p[k].pr[p[k].n].l, c);
        if ch = '(' then begin { '(' reikia, kad ‡ia prikabinta kita pakaba }
                           inc (np);
                           p[k].pr[p[k].n].p := np;
                           skaitom (gl+1); { skaitom i… pakab… }
                           read (f, ch)
                         end
                    else begin p[k].pr[p[k].n].p := 0; inc (n); end;
        if ch = ',' then read (f, ch);
      end;
  end;

  procedure rasom (k : integer);
     { proced–ra, rekursikai atspausdinanti rezultatus }
    var c : integer;
  begin
    write (f, '(');
    for c := 1 to p[k].n do
      begin
        if p[k].pr[c].p = 0 then write (f, p[k].pr[c].m)
                           else rasom (p[k].pr[c].p);
        if c < p[k].n then write (f, ',');
      end;
    write (f, ')');
  end;


  procedure dedam_svarscius (kp, kpr : integer; bv : buvo_naudoti);
     { bandome sukabinti svars‡ius taip kad svertas butu pusiausvyras
       kp - kelint… pakab… bandome sutvarkyti,
       kpr - kelint… pakabos prikabinim… tvarkome,
       bv - kokie svars‡iai jau buvo kabinti }
    var c : integer;
  begin
    if not sudetas then  { bandome deti tik tada, jei dar neturime atsakymo }
      if kp = np + 1 then sudetas := true { jei bandome deti tolimesnŠ pakab…,
       nei paskutin‚, reikia, jau visos sukabintos, t.y. gavom atsakym… }
      else if kpr = p[kp].n+1 then
           begin  { jei visi prikabinimai sutvarkyti, imame tolimesnŠ pakab… }
             if p[kp].mm = 0 then dedam_svarscius (kp+1, 1, bv);
           end
           else begin
                  if kpr = 1 then begin p[kp].mm := 0; p[kp].m := 0; end;
                            { i prad‘i— pakabos mas‚ ir
                              atstum— ir masi— sandaug— suma lygi 0 }
                  if p[kp].pr[kpr].p > 0 then
                    begin
                     { jei ant io prikabinimo kaba kita pakaba,
                      tai tik pridedame jos masŠ ir
                      atstumo bei mas‚s sandaug… }
                      p[kp].m := p[kp].m + p[p[kp].pr[kpr].p].m;
                      p[kp].mm := p[kp].mm +
                                  p[p[kp].pr[kpr].p].m*p[kp].pr[kpr].l;
                      dedam_svarscius (kp, kpr+1, bv);
                      p[kp].m := p[kp].m - p[p[kp].pr[kpr].p].m;
                      p[kp].mm := p[kp].mm -
                                  p[p[kp].pr[kpr].p].m*p[kp].pr[kpr].l;
                    end
                  else for c := 1 to n do
                         { jei kaba svarstis tai bandome d‚ti visus i eil‚s
                           dar ned‚tus }
                           if (not sudetas) and (not bv[c]) then
                             begin
                               p[kp].pr[kpr].m := c;
                               p[kp].m := p[kp].m + c;
                               p[kp].mm := p[kp].mm + c*p[kp].pr[kpr].l;
                               bv[c] := true;
                               dedam_svarscius (kp, kpr+1, bv);
                               bv[c] := false;
                               p[kp].m := p[kp].m - c;
                               p[kp].mm := p[kp].mm - c*p[kp].pr[kpr].l;
                             end;
                end;
  end;


begin
  assign (f, 'mobile.in'); reset (f);
  read (f, ch);
  np := 1; n := 0;
  skaitom (1);  { perskaitome pradinius duomenis }
  close (f);

  c := 1;
  while c < np do { surikiuojame pakabas pagal gyl ma‘‚jimo tvarka }
   if p[c].gl >= p[c+1].gl then inc (c)
       else begin
              a := p[c]; p[c] := p[c+1]; p[c+1] := a;
              if c = 1 then inc (c)
                       else dec (c)
            end;

  for c := 1 to np do
    m[p[c].k] := c;
  for ck := 1 to np do   { pakei‡iame nuorodas  kitas pakabas, nes po suri -
                           kiavimo pasikeit‚ j— numeriai }
    for c := 1 to p[ck].n do
      if p[ck].pr[c].p > 0 then p[ck].pr[c].p := m[p[ck].pr[c].p];

  fillchar (bv, sizeof(bv), false);
  sudetas := false;
  dedam_svarscius (1, 1, bv);  { bandome sukabinti svars‡ius }

  assign (f, 'mobile.out'); rewrite (f);
  rasom (m[1]);               { spausdiname rezultat… }
  close (f);
end.