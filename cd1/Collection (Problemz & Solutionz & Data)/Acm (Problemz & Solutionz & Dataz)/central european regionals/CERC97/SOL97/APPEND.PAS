program append;   { (c) Ilja Martisovits  }

  const  max   =  1000;  { horny odhad pre   p }

         dlz_buf = max+3;

  var  buffer:array[0..(dlz_buf-1)] of integer;

       f,g:text;
       p,r:integer;
       znak:char;

       pocet_znakov:integer;  {  pocet znakov decodovaneho zatial textu }
       zac,poc:integer;  { urcuje polohu zoznamu cisel v bufri buffer }
       counter:integer;  { pocet zatial vyhovujucich oddelovnikov }
       pivot:integer;

       a,b:integer;  { pre binarne vyhladavanie }
       a0:integer;

       index:integer;

  procedure haltni(ret:string);
  begin
    writeln(ret);
    writeln(g,'Error: ',ret);
    close(g);
    close(f);
    halt;
  end;

  begin   { hlavny program }

    assign(f,'append.in');
    assign(g,'append.out');
    reset(f);
    rewrite(g);

    while (not eoln(f)) do
      begin  { cyklus pre bloky }

        { inicializacia zoznamu }

        buffer[0]:=0;
        zac:=0;
        poc:=1;
        pocet_znakov:=0;
        counter:=1;

        
        repeat
          read(f,p); { citanie riadku }
          read(f,znak);
          if (znak <> ' ') then haltni('Oddelovnik nie je medzera !!');
          if (p=0) then begin
                          read(f,znak);
                          r:=1;
                        end
                   else begin
                          read(f,r);
                          if (r>p) then haltni('r je vacsie ako p !!');
                          if (r<1) then haltni('r je mensie ako 1 !!');
                        end;
          readln(f);


          { vyhodenie tych, ktori uz presli overenim }

          while (buffer[(zac mod dlz_buf)] <= pocet_znakov - max) do
            begin
              zac:=(zac+1) mod dlz_buf;
              poc:=poc-1;
            end;


          pivot:=pocet_znakov - p;
          if (pivot < 0) then haltni('Vstupna sekvencia parov sa neda korektne dekodovat !!!');

          a:=0;
          b:=poc;
                          { binarne vyhladanie }
          while (a<b) do
            begin
              a0:=trunc((a+b)/2);
              index:=(zac+a0) mod dlz_buf;
              if (buffer[index] > pivot) then b:=a0
                                         else a:=a0+1;
            end;

          {vyhodenie}
          counter:=counter - (poc - a);
          poc:=a;

          pocet_znakov:=pocet_znakov + r;

          { zaradi noveho kandidata }

          buffer[((zac+poc) mod dlz_buf)]:=pocet_znakov;
          poc:=poc+1;
          counter:=counter+1;

        until eoln(f);

        readln(f);

        counter:=counter-2;
        if (counter < 0) then counter:=0;

        writeln(g,counter);

      end;

    close(g);
    close(f);

  end.