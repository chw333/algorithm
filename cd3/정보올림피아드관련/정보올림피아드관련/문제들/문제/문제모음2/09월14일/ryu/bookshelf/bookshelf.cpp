#include <fstream.h>
#include <stdlib.h>

ifstream in ( "bookshelf04.in"  );
ofstream out( "bookshelf04.out" );

#define Max_Knapsack 1024
#define Max_Item     1024

int Knapsack[Max_Knapsack], Item[Max_Item];
int K_size, K_n, I_n;
int Total_k, Total_i, Total_i_acc[Max_Item];

int Result;

void input()
{
    int i, tmp, tmp2;
    
    in >> K_size;
    for ( i = 0; i < Max_Knapsack; i ++ ) Knapsack[i] = K_size;
    in >> I_n;
    for ( i = 0; i < I_n; i ++ ) in >> Item[i];
    for ( i = 1; i < I_n; i ++ ) Total_i += Item[i];
    
    K_n = I_n;
}

void output()
{
    out << Result;
}

int recur( int item, int start_k )
{
    int i, j, sw, tmp, ret, t1 = 0, t2 = 0;
  
    if ( Total_i > Total_k ) return -1;

    if ( item == 1 ) {
        for ( i = 0; i < K_n; i ++ ) {
            if ( Knapsack[i] <= Item[1] + Item[0] ) return 0;
            else if ( Knapsack[i] <= Item[1] ) t1 = 1;
            else if ( Knapsack[i] <= Item[0] ) t2 = 1;
            if ( t1 == 1 && t2 == 1 ) return 0;
        }
    }
    
    if ( item == 0 ) {
        for ( i = 0; i < K_n; i ++ ) {
            if( Knapsack[i] >= Item[item] ) return 0;
        }
        return -1;
    }
    

    for ( i = start_k; i < K_n; i ++ ) {
    
        /* remove same sized knapsack */    
        sw = 0;
        for ( j = 0; j < i; j ++ ) {
            if ( Knapsack[i] == Knapsack[j] ) { sw = 1; break; }                
        }
        if ( sw ) continue;
        
        if ( Item[item] < Knapsack[i] ) {
        
            if ( Knapsack[i] < Item[0] + Item[item] ) tmp = Knapsack[i];
            else tmp = Item[item];
            
            Knapsack[i] -= tmp; Total_k -= tmp; Total_i -= Item[item];
            
            /* consider same sized item */    
            if ( Item[item] == Item[item-1] ) {
                ret = recur ( item-1, i );
            } else {
                ret = recur ( item-1, 0 );
            }
                        
            Knapsack[i] += tmp; Total_k += tmp; Total_i += Item[item];
            
            if ( ret == 0 ) return 0;            
            
        } else if ( Knapsack[i] == Item[item] ) {
            Knapsack[i] -= Item[item];
            Total_k -= Item[item];
            Total_i -= Item[item];
            if ( Item[item-1] == Item[item] ) {
               ret = recur ( item-1, i );
            } else {
               ret = recur ( item-1, 0 );
            }
            Knapsack[i] += Item[item];
            Total_k += Item[item];
            Total_i += Item[item];
            return ret;
        }                
    }
    return ( -1 );
}

void resizer ( int item )
{
    int i;
    Total_i = 0;
    for ( i = 0; i < item; i ++ ) Total_i += Item[i];
}

int s_f ( const void *a, const void *b )
{
    int A = *(int *) a, B = *(int *) b;
    if ( A > B ) return 1;
    else if ( A == B ) return 0;
    return -1;
}

void process()
{
    int i, ret, min, max, mid;
    qsort ( Item, I_n, sizeof(Item[0]), s_f );
    min = (Total_i / K_size) + ((Total_i%K_size)?1:0);
    max = K_n;
    mid = ( min + max ) / 2;    
    while ( mid != min && mid != max ) {        
        K_n = mid;
        Total_k = K_n * K_size;        
        ret = recur ( i, 0 );
        if ( ret == 0 ) max = mid;
        else min = mid;
        mid = ( min + max ) / 2;           
    }
    K_n = min;
    Total_k = K_n * K_size;        
    if ( recur ( I_n-1, 0 ) == 0 ) Result = K_n;    
    K_n = max;
    Total_k = K_n * K_size;        
    if ( recur ( I_n-1, 0 ) == 0 ) Result = K_n;        
}

void main()
{
    input();
    process();
    output();
}
