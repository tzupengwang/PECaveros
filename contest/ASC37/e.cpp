#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 250010;

int n;
char str[ MAXN ];
int ans[ MAXN ] , f[ MAXN ]; 
int lst[ MAXN ];

int main2()
{
    scanf( "%s" , str );
    f[ 0 ] = -1;
    n = strlen( str );
    for( int i = 1 ; i < n ; i ++ ){
        int tmp = f[ i - 1 ];
        while( tmp >= 0 && str[ tmp + 1 ] != str[ i ] )
            tmp = f[ tmp ];
        f[ i ] = tmp + ( str[ tmp + 1 ] == str[ i ] );
        //printf( "  f %d %d\n" , i , f[ i ] );
    }
    for( int i = 1 ; i <= n ; i++ ) lst[ i ] = -1;
    ans[ 0 ] = 1;
    lst[ 1 ] = 0;
    for( int i = 1 ; i < n ; i++ )
    {
        if( f[ i ] < 0 )
        {
            ans[ i ] = i+1;
            lst[ i+1 ] = i;
            continue ;
        }
        int pl = ans[ f[ i ] ];
        int pp = lst[ pl ];
        assert( pp >= 0 );
        if( i - pp <= pl )
        {
            ans[ i ] = pl;
            lst[ pl ] = i;
        }
        else
        {
            ans[ i ] = i+1;
            lst[ i+1 ] = i;
        }
    }
    for( int i = 0 ; i < n ; i++ )
        printf( "%d%c" , ans[ i ] , " \n"[ i == n-1 ] );
    return 0;
}

int main()
{
#ifdef ONLINE_JUDGE
    freopen("cover.in" , "r" , stdin );
    freopen("cover.out" , "w" , stdout );
#endif
    main2();
}
