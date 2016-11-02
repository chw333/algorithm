#include <fstream.h>

// debugging 
#include <iomanip.h>
#include <conio.h>

ifstream in  ( "oddfraction10.in" );
ofstream out ( "oddfraction10.out" );

double Tmp;
int A, B;

void input()
{
    in >> A >> B;
    Tmp = (double)A / B;
}

void process()
{
    int d = 2, sw = 0;
    double p = (double)1/d;
    double hab = 0.0;
    cout << Tmp << endl;
    do {
        while ( Tmp < hab + p && d > 0 ) {
            d ++;
            p = (double)1/d;
        }
        if ( d <= 0 ) break;
        if ( sw == 0 ) sw = 1;
        else cout << endl;
        hab += p;
        cout << d << " " << hab;
        d ++;
        p = (double)1/d;
    } while ( Tmp > hab && d > 0 );   
    cout << endl << d;
}

void main()
{
	input();
	process();
	getch();
}
