{ IDJA: Jei neb–t— sukeitimo, tai b–t— papras‡iausias dinaminio
  programavimo u‘davinys. Dabar t… klasikinŠ sprendimo id‚j…
  reikia žiek tiek modifikuoti.

  P.s. Atkreipkite d‚mes, kad n‚ra akivaizdu kaip sutalpinti
  vis… eilutŠ  atmint. SprŠsdami darome papras‡iau. ­simename
  tik naujai perskaityt… ir buvusi… eilutŠ.

  1. Perskaitome pirm…j… eilutŠ. J… simename lentel‚je eil_nek.

     Jei žioje eilut‚je b–t— atliekamas sukeitimas, tai visus
     jos elementus b–t— galima pakeisti maksmalia reikžme. T… ir padarome.
     Rezultat… simename lentel‚je eil_suk.

  2. Perskaitome tolesnŠ eilutŠ eil. Galimi trys variantai.

      a) Sukeitimas iki žiol nebuvo darytas ir nebus daromas
         žioje eilut‚je.

         Tuomet remdamiesi eilut‚mis eil bei eil_nek atnaujiname
         eilutŠ eil_nek, t.y. randame ilgiausius kelius nuo viržutin‚s
         eilut‚s iki perskaitytosios eilut‚s kiekvieno elemento

     b) Sukeitimas jau buvo padarytas ankstesn‚je eilut‚je.

         Tuomet remdamiesi eilut‚mis eil bei eil_suk atnaujiname
         eilutŠ eil_suk, t.y. randame ilgiausius kelius nuo viržutin‚s
         eilut‚s iki perskaitytosios eilut‚s kiekvieno elemento.

     c) Sukeitimas daromas žioje eilut‚je.

        Randame did‘iausi… eil element…. Tuomet remdamiesi eilute
        eil_nek atnaujiname eilutŠ eil_suk.


     Eilut‚ eil_nek atnaujinama tik atliekant ‘ingsn a).
     Tuo tarpu atlikdami b) ir c) ‘ingsnius gausime dvi eilut‚s
     eil_suk versijas. Ÿias dvi eilutes "sujungiame" pasirinkdami
     didesniuosiu elementus:
        eil_suk_atnaujinta[i] := max(eil_suk_a[i], eil_suk_b[i]);
        i kinta nuo 1 iki eilut‚s ilgio.

3. Antr…j ‘ingsn kartojame kol per‘i–rime visas eilutes.

4. Ižrenkame did‘iausi… eilu‡i— eil_nek ir eil_suk element…. Tai ir bus
   iežkomas kelias.
}
program korio_uzdavinys;

  const PR = 'hon.in';
        RZ = 'hon.out';
        MAX_N = 99;
  type eilute = array [1..2*MAX_N-1] of integer;

  procedure skaityti (var f: text; ilg: integer; var eil: eilute);
    { iž pradini— duomen— bylos perskaito nurodyto ilgio eilutŠ }
    var i: integer;
  begin
    for i := 1 to ilg do
      read (f, eil[i]);
  end; { skaityti }

  function didz (ilg: integer; eil: eilute): integer;
    { ižrenkamas did‘iausias eilut‚s elementas }
    var max, i: integer;
  begin
    max := eil[1];
    for i := 2 to ilg do
      if eil[i] > max
         then max := eil[i];
     didz := max;
  end; { did‘ }

  function max_2 (a, b: integer): integer;
  begin
    if a < b
       then max_2 := b
       else max_2 := a;
  end; { max_2 }

  function pagrindine (var f: text): integer;
    var n, { korio kražtin‚s ilgis }
        i, j, ilg, max, max2, max1, kair, des: integer;
        nau_nek, nau_dab, nau_suk, eil_suk, eil_nek, eil: eilute;
  begin
    readln (f, n); { korio kražtin‚s ilgis }
    { perskaitoma pirmoji eilut‚ }
    ilg := n; { pirmosios eilut‚s ilgis }
    skaityti (f, ilg, eil);
    { randamas jos did‘iausias elementas }
    max := didz (ilg, eil);
    eil_nek := eil;
    for i := 1 to n do
      eil_suk[i] := max;
    { skaitome po vien… korio eilutŠ ir iežkome did‘iausio kelio }
    for i := 2 to 2*n-1 do
      begin
        { perskai‡iuojame eilut‚s ilg }
        if i <= n then ilg := ilg + 1
                 else ilg := ilg - 1;
        { skaitome tolesnŠ eilutŠ }
        skaityti (f, ilg, eil);
        { jei sukeitimas dar nebuvo atliktas arba atliktas žioje eilut‚je }
        max := didz (ilg, eil);
        for j := 1 to ilg do
          begin
            { kairioji žaka }
            if (j = 1) and (i <= n) then kair := -1
             else if i <= n then kair := eil_nek[j-1]
                            else kair := eil_nek[j];
            { dežinioji žaka }
            if (j = ilg) and (i <= n) then des := -1
             else if i <= n then des := eil_nek[j]
                            else des := eil_nek[j+1];
            nau_nek[j] := max_2(kair, des) + eil[j];
            nau_dab[j] := max_2(kair, des) + max;
          end;
        { jei sukeitimas atliktas ankstesn‚se eilut‚se }
        for j := 1 to ilg do
          begin
            { kairioji žaka }
            if (j = 1) and (i <= n) then kair := -1
             else if i <= n then kair := eil_suk[j-1]
                            else kair := eil_suk[j];
            { dežinioji žaka }
            if (j = ilg) and (i <= n) then des := -1
             else if i <= n then des := eil_suk[j]
                            else des := eil_suk[j+1];
            nau_suk[j] := max_2(kair, des) + eil[j];
          end;
        { atnaujinamos reikžm‚s }
        eil_nek := nau_nek;
        for j := 1 to ilg do
          eil_suk[j] := max_2(nau_dab[j], nau_suk[j])
      end;
    { ižrenkame did‘iausi… reikžmŠ }
    max1 := didz (ilg, eil_suk);
    max2 := didz (ilg, eil_nek);
    pagrindine := max_2(max1, max2);
  end; { pagrindin‚ }

  procedure atidaryti_byla (var f: text);
  begin
    assign (f, PR);
    reset (f);
  end; { atidaryti_byl… }

  procedure uzdaryti_byla (var f: text);
  begin
    close (f);
  end; { u‘daryti_byl… }

  procedure spausdinti (rez: integer);
    var f: text;
  begin
    assign (f, RZ);
    rewrite (f);
    writeln (f, rez);
    close (f);
  end; { spausdinti }

  var f: text;
      rez: integer;
begin
  atidaryti_byla (f);
  rez := pagrindine (f);
  uzdaryti_byla(f);
  spausdinti (rez);
end.