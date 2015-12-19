#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210;
typedef pair< int , int > pii;

int n;
int in[ MAXN ][ MAXN ];
int ord[ MAXN ];
vector< pii > sw[ MAXN * MAXN * 10 ];
int ans[ MAXN ];
int anss[ MAXN ];


bool go[ MAXN ][ MAXN ];

int main2()
{
    scanf( "%d" , &n );
    int mx = 0;
    for( int i = 1 ; i < n ; i++ )
        for( int j = 1 ; j <= i ; j++ )
        {
            scanf( "%d" , in[ i ] + j );
            int t = n - i + 2*(j-1);
            mx = max( mx , t );
            sw[ t ].push_back( pii( i , j ) );
        }
    for( int i = 1 ; i <= n ; i++ ) ord[ i ] = i;
    for( int i = 1 ; i <= mx ; i ++  )
    {
        for( pii p : sw[ i ] )
        {
            if( in[ p.first ][ p.second ] )
            {
                go[ ord[ p.first + 1 ] ][ ord[ p.first ] ] = 1;
                swap( ord[ p.first ] , ord[ p.first + 1 ] );
            }
            else
            {
                go[ ord[ p.first ] ][ ord[ p.first + 1 ] ] = 1;
            }
        }
    }

    for( int k = 1 ; k <= n ; k++ )
        for( int i = 1; i <= n ; i++ )
            for( int j = 1 ; j <= n ; j++ )
                go[ i ][ j ] = go[ i ][ j ] || ( go[i][k] && go[k][j] );

    for( int i = 1 ; i <= n ; i++ )
        for( int j = 1 ; j <= n ; j++ )
            if( go[i][j] && go[j][i] )
            {
                puts( "NO" );
                return 0;
            }
    puts( "YES" );
    for( int i = 1 ; i <= n ; i++ ) ans[ i ] = i;
    sort( ans + 1 , ans + 1 + n , [&](int a,int b){return go[a][b];} );
    for( int i = 1 ; i <= n ; i++ )
        anss[ ans[ i ] ] = i;
    for( int i = 1 ; i <= n ; i++ )
        printf( "%d%c" , anss[ i ] , " \n"[ i == n ] );
    return 0;
}

int main()
{
#ifdef ONLINE_JUDGE
    freopen("bubble.in" , "r" , stdin );
    freopen("bubble.out" , "w" , stdout );
#endif
    main2();
}
