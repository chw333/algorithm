{I+,Q+,R+,S+}
{$M 65520,0,655360}
program mikroshemos;
  { srauto u‘davinys, kai ne tik briaunos, bet ir vir–ni— bakai }
  { turi pralaidumus }
  { Sprendimas, kai papras‡iausiai ribojamas bako turinys }

  { ieko maksimalaus srauto i pirmosios  m-…j… vir–nŠ }
  { m - vir–ni— skai‡ius grafe }
  { randa ne tik srauto kiek, bet ir pa‡ius srautus }

  const MAX_N = 15;  { maksimali n reikm‚ }
        MAX_M = MAX_N*MAX_N*2 + 2; { maksimalus vir–ni— skai‡ius }
        ELEM_SK = 255; { element— skai‡ius aib‚je }
        PR = 'ELE.IN';
        RZ = 'ELE.OUT';
  type  aibe = array [1..2] of set of 0..255;
        lentele1 = array [1..MAX_M] of integer; { vir. auk‡iai, bakai }
        lentele2 = array [1..MAX_M] of aibe;    { srautai, pralaidumai }

  procedure inicializuoti_aibe (var aib: aibe);
    { gr…‘ina tu‡i… aibŠ }
  begin
    aib[1] := []; aib[2] := [];
  end; { valyti_aibŠ }

  function tuscia_aibe (aib: aibe): boolean;
    { patikrina ar aib‚ tu‡ia }
  begin
    tuscia_aibe := (aib[1] = []) and (aib[2] = []);
  end; { tu‡ia_aib‚ }

  procedure i_aibe (elem: integer; var aib: aibe);
    {  aibŠ traukia nauj… element… }
  begin
    if elem < 255
       then aib[1] := aib[1] + [elem]
       else aib[2] := aib[2] + [elem mod 255]
  end; { _aibŠ }

  procedure is_aibes (elem: integer; var aib: aibe);
    { i aib‚s paalina nurodyt… element… }
  begin
    if elem < 255
       then aib[1] := aib[1] - [elem]
       else aib[2] := aib[2] - [elem mod 255]
  end; { _aibŠ }

  function aibeje (elem: integer; aib: aibe): boolean;
    { ar aib‚je yra nurodytas elementas }
  begin
    if elem < 255
       then aibeje := elem in aib[1]
       else aibeje := (elem mod 255) in aib[2];
  end; { aib‚je }

  procedure ivesti (var pral: lentele2;           { briaun— pralaidumai }
                    var m, n,       { vir–ni— skai‡ius, tinkelio dydis }
                    prad, gal: integer;    { pradin‚s, galin‚s vir–n‚s }
                    var krastas,                   { kratin‚s vir–n‚s }
                    isejimai: aibe);                { vir–ni— skai‡ius }
                                          { pradin‚ bei galin‚ vir–n‚s }
  { veda pradinius duomenis }
    var md, kiekis, i, j, nn, u, v, c: integer;
        f: text;
        delta: array [1..4] of integer;
  begin
    assign (f, PR);
    reset (f);
    readln (f, n);
    inicializuoti_aibe (isejimai);  { perskaitŠ pradinius duomenis }
    for i := 1 to n do        { sudarome i‚jim— aibŠ }
      for j := 1 to n do
        begin
          read (f, c);
          if c = 1 then i_aibe ((i-1)*n + j, isejimai);
        end;
    close(f);
    nn := n*n;
    m := 2*nn + 2;
    prad := 2*nn + 1; gal := 2*nn + 2;
    { sudarome graf… }
    { inicializuojame briaun— pralaidum— masyv… }
    for u := 1 to m do
      inicializuoti_aibe (pral[u]);
    { surandame kratini— mazg— virutiniame tinklelyje aibŠ }
    inicializuoti_aibe (krastas);
    for u := 1 to nn do
      if (u <= n) or (u mod n = 1) or (u mod n = 0) or (u >= (n-1)*n)
         then i_aibe (u, krastas);
    { pradinŠ vir–nŠ sujungiame su i‚jimais }
     for u := 1 to nn do
         if aibeje (u, isejimai)
            then i_aibe(u, pral[prad]);
     { sujungiame abu tinkelius }
     for u := 1 to nn do
       i_aibe (u+nn, pral[u]);
    { sujungiame vir–nes tinklelyje }
     delta[1] := -1; delta[2] := 1;  { vir–ni—, gretim— u numeriai }
     delta[3] := -n; delta[4] := n;
    for u := 1 to nn do
       for i := 1 to 4 do
          begin
            { nuvesime briaun… i u  v }
            v := u + delta[i];
            if (1 <= v) and (v <= nn) and not (aibeje (v, isejimai)) and
               {  mazg… briauna ateiti negali }
               not (aibeje((u mod nn), krastas))
               { briauna neieina i krato }
               then i_aibe (v, pral[u+nn])
          end;
    { sujungiame kratus su i‚jimu }
    for u := 1 to nn do
      if aibeje (u, krastas)
         then i_aibe (gal, pral[u+nn]);
  end; { vesti }

  procedure max_srautas (m, prad, gal: integer;     { vir–ni— skai‡ius }
                                             { pradin‚, galin‚ vir–n‚s }
                         pral: lentele2;          { briaun— pralaidumai }
                         var sr_teig: lentele2);           { rastasis srautas }
  { randa maksimal— sraut… grafe }
    var e, { eil‚ }
        h, bakas: lentele1;  { vir–ni— auk‡iai ir bakasildymai }
        sr_neig: lentele2;
        u, galva, uodega: integer;
        virs: aibe;

    procedure inicializuoti (var h, bakas: lentele1; { auktis ir bakas }
                             var sr_neig, sr_teig: lentele2 { srautas });
    { inicializuoja (priskiria nulius) h, s, bakas }
      var u, v: integer;
    begin
      for u := 1 to MAX_M do
        begin
          h[u] := 0;
          bakas[u] := 0;
        end;
     for u := 1 to MAX_M do
         begin
           inicializuoti_aibe (sr_neig[u]);
           inicializuoti_aibe (sr_teig[u]);
         end;
    end; { inicializuoti }

    procedure itraukti_i_eile (u: integer;  var virs: aibe;
                               var e:lentele1; var uodega: integer);
    { traukia  eil‚s pabaig… vir–nŠ u }
    begin
      i_aibe (u, virs);
      e[uodega] := u;
      if uodega = MAX_M
         then uodega := 1
         else uodega := uodega + 1;
    end; { traukti__eilŠ }

    procedure pasalinti_is_eiles (var galva: integer; var virs: aibe);
    begin
      is_aibes (u, virs);
      if galva = MAX_M
         then galva := 1
         else galva := galva + 1
    end; { paalinti_i_eil‚s }

    procedure pakelti (u: integer; { keliama vir–n‚ }
                       var h: lentele1 { vir–ni— auk‡iai });
    { padidinamas u auktis }
    { vartojami global–s kintamieji m, s, pral }
      var mini, v, ind, pralaid, vv, srautas: integer;
          galima: boolean;
    begin
      galima := true; { ar galima pakelti vir–nŠ }
      mini := 0;      { ‘emiausia vir–n‚  kuri… galima leisti sraut… }
      for v := 1 to m do
        begin
           { leisime sraut… i u  v }
           { koks pralaidumas i u  v }
           if v < 255 then begin ind := 1; vv := v end
                      else begin ind := 2; vv := v mod 255 end;
           if vv in pral[u, ind] then pralaid := 1
                                 else pralaid := 0;
           { kiek srauto nukreipta i u  v }
           if vv in sr_teig[u, ind] then srautas := 1
              else if vv in sr_neig[u, ind] then srautas := -1
              else srautas := 0;
           { dabar tikrai leisime sraut… }
           if pralaid - srautas > 0
              then if (h[u] <= h[v])
                      then begin
                             if mini = 0 { jei dar n‚ viena nerasta }
                                then mini := v
                                else if h[v] < h[mini]
                                        then mini := v;
                           end
                      else galima := false;
        end;
      if galima
         then h[u] := h[mini] + 1
    end; { pakelti }

    function min (x, y: integer): integer;
    begin
      if x < y
         then min := x
         else min := y
    end; { min }

    procedure paleisti (u: integer;
                        var sr_neig, sr_teig: lentele2; { srautai }
                        var bakas: lentele1);
    { paleid‘ia vir–n‚s u bake esant sraut… }
    { vartojami global–s kintamieji m, h, pral, e, uodega }
      var v, kiekis, vv, ind, pralaid, srautas: integer;
    begin
      for v := 1 to m do
        begin
          { apskai‡iuosime pralaidum… bei praleist… sraut… }
          if v < 255
             then begin ind := 1; vv := v end
             else begin ind := 2; vv := v mod 255 end;
          if vv in pral[u, ind] then pralaid := 1
                                else pralaid := 0;
          if vv in sr_teig[u, ind] then srautas := 1
             else if vv in sr_neig[u, ind] then srautas := -1
             else srautas := 0;
          if (h[v] + 1 = h[u]) and (pralaid - srautas > 0)
           { jei v ‘emesn‚ ir  j… dar galima paleisti sraut… }
           then begin
                  kiekis := min (bakas[u], pralaid - srautas);
                  bakas[u] := bakas[u] - kiekis;
                  if kiekis = 1
                     then begin
                            if aibeje (v, sr_neig[u])
                               { jei s[u, v] = -1 }
                               then begin { s[u, v] = -s[v, u] = 0 }
                                      is_aibes (v, sr_neig[u]);
                                      is_aibes (u, sr_teig[v]);
                                     end
                               else begin { jei s[u, v] = 0 }
                                       i_aibe (v, sr_teig[u]);
                                       i_aibe (u, sr_neig[v]);
                                     end;
                          end { if kiekis = 1 }
                  else if kiekis = -1
                      then begin
                            if aibeje (v, sr_teig[u])
                               { jei s[u, v] = 1 }
                               then begin { s[u, v] = -s[v, u] = 0 }
                                      is_aibes (v, sr_teig[u]);
                                      is_aibes (u, sr_neig[v]);
                                     end
                               else begin { jei s[u, v] = 0 }
                                       i_aibe (v, sr_neig[u]);
                                       i_aibe (u, sr_teig[v]);
                                     end;
                          end;
                  bakas[v] := bakas[v] + kiekis;
                  if (bakas[v] > 0) and (v <> prad)
                  then if (v <> gal) and (not (aibeje(v, virs)))
                       then itraukti_i_eile (v, virs, e, uodega);
                end;
        end;
    end; { paleisti }

  begin
    inicializuoti (h, bakas, sr_neig, sr_teig);
    galva := 1; uodega := 1; { eil‚ tu‡ia }
    inicializuoti_aibe (virs); { eil‚je esan‡ios vir–n‚s }
    h[prad] := m; { pradin‚s vir–n‚s auktis }
    { paleid‘iame sraut… i pradin‚s vir–n‚s }
    for u := 1 to m do
      if aibeje (u, pral[prad])
         then begin
                i_aibe (u, sr_teig[prad]);
                i_aibe (prad, sr_neig[u]);
                bakas[u] := 1;
                if u <> m { galin‚s vir–n‚s bakas begalinis }
                   then itraukti_i_eile (u, virs, e, uodega);
              end;
    while not tuscia_aibe (virs) do
      { su aibe papras‡iau patikrinti ar ta pati vir–n‚  eilŠ netraukiama }
      { du kartus }
      begin
        u := e[galva];
        pasalinti_is_eiles (galva, virs);
        while bakas[u] > 0 do
          begin
            pakelti (u, h);
            paleisti (u, sr_neig, sr_teig, bakas)
          end;
      end;
  end; { max_srautas }

  procedure skaiciuoti (n,             { tinklelio dydis }
                        prad: integer; { pradin‚ vir–n‚ }
                        const sr_teig: lentele2; { rasti srautai }
                        const krastas, isejimai: aibe;
                        var max_ise: integer);
    { randa rezultat… bei i‚jimus tinklelio krate }
    var u: integer;
  begin
    max_ise := 0;
    for u := 1 to n*n do
        if aibeje (u, sr_teig[prad]) and
        not ((aibeje (u, krastas)) and (aibeje(u, isejimai)))
        { jei eina briauna ne  kratin kontakt… }
           then max_ise := max_ise + 1;
  end; { skai‡iuoti }

  procedure isvesti (m, n, prad, gal: integer;
                     const krastas, isejimai: aibe;
                     const sr_teig: lentele2);
  { spausdina rezultatus }
    var f: text;
        nn, nuo, u, v, max_ise, i: integer;
        kryptis: char;
  begin
    nn := n*n;
    assign (f, RZ);
    rewrite (f);
    { rasime maksimal— i‚jim— skai‡i— bei tuos i‚jimus, kam nereik‚jo }
    { tiesti grandin‚s }
    skaiciuoti (n, prad, sr_teig, krastas, isejimai, max_ise);
    writeln (f, max_ise);
    { atspausdinsime grandines }
    for u := 1 to nn do
       if aibeje(u, sr_teig[prad]) and not (aibeje(u, krastas))
          then   { jei tai i‚jimas ir ne krate }
       begin
         write (f, u, ' '); { atspausdiname i‚jimo numer }
         nuo := u;
         while not aibeje (gal, sr_teig[nuo]) do { kol nepasiek‚me krato }
           begin
             v := 1;
             while not
             aibeje(v, sr_teig[nuo]) do
               v := v + 1;
             { nustatome krypt }
             kryptis := '?';
             if nuo mod nn > v mod nn {  kairŠ arba  vir— }
                then if abs (nuo mod nn - v mod nn) = 1 {  kairŠ }
                        then kryptis := 'W'
                        else kryptis := 'N'
                else if nuo mod nn < v mod nn {  deinŠ arba  apa‡i… }
                        then if abs (nuo mod nn - v mod nn) = 1 {  deinŠ }
                                then kryptis := 'E'
                                else kryptis := 'S';
             if kryptis <> '?'
                then write (f, kryptis);
             nuo := v;
           end; { kol nepasiek‚me krato }
         writeln (f);
       end; { grandini— ivedimas }
    close (f);
  end; { ivesti }

  var pral, s: lentele2; { briaun— pralaidumai bei rasti srautai }
      m, n, prad, gal: integer; { vir–ni— skai‡ius, pradin‚ bei galin‚ vir. }
      isejimai, krastas: aibe;
begin
  ivesti (pral, m, n, prad, gal, krastas, isejimai);
  max_srautas (m, prad, gal, pral, s);
  isvesti (m, n, prad, gal, krastas, isejimai, s);
end.

