#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#define FILE( fn ) \
    freopen(fn".in","r",stdin); \
    freopen(fn".out","w",stdout);
#else
#define FILE( fn )
#endif
using namespace std;
#define N 3010
typedef double D;
int d , b , bs[ 11 ] , bs2[ 11 ] , type , type2;
int dp1[ N ][ N ] , dp2[ N ][ N ];
int take_bit( int x , int bt ){
    return ( x / bs[ bt ] ) % ( b + 1 );
}
void init(){
    bs[ 0 ] = bs2[ 0 ] = 1;
    for( int i = 1 ; i < d ; i ++ ){
        bs[ i ] = bs[ i - 1 ] * ( b + 1 );
        bs2[ i ] = bs2[ i - 1 ] * b;
    }
    type = 1;
    for( int i = 0 ; i < d ; i ++ )
        type *= ( b + 1 );
    type2 = bs2[ d - 1 ] * b;
    for( int i = 0 ; i < type ; i ++ )
        for( int j = 0 ; j < type ; j ++ )
            dp1[ i ][ j ] = dp2[ i ][ j ] = -1;
}
int DP1( int x , int y , int turn ){
    if( turn == 2 * d ){
        if( x > y ) return 1;
        return 0;
    }
    if( dp1[ x ][ y ] < 0 ){
        if( turn >= d ){
            dp1[ x ][ y ] = 0;
            for( int i = 1 ; i <= b ; i ++ ){
                //D pro = 1.0 / (D)b;
                int wst = type * type;
                for( int j = 0 ; j < d ; j ++ )
                    if( take_bit( y , j ) == 0 ){
                        int nxty = y + bs[ j ] * i;
                        int tdp = DP1( x , nxty , turn + 1 );
                        wst = min( wst , tdp );
                    }
                dp1[ x ][ y ] += wst;
                //dp2[ x ][ y ] += pro * wst;
            }
        }else{
            dp1[ x ][ y ] = 0;
            for( int i = 1 ; i <= b ; i ++ ){
                //D pro = 1.0 / (D)b;
                int bst = 0;
                for( int j = 0 ; j < d ; j ++ )
                    if( take_bit( x , j ) == 0 ){
                        int nxtx = x + bs[ j ] * i;
                        int tdp = DP1( nxtx , y , turn + 1 );
                        bst = max( bst , tdp );
                    }
                dp1[ x ][ y ] += bst;
            }
        }
    }
    return dp1[ x ][ y ];
}
int DP2( int x , int y , int turn ){
    if( turn == 2 * d ){
        if( x > y ) return 1;
        return 0;
    }
    if( dp2[ x ][ y ] < 0 ){
        if( turn & 1 ){
            dp2[ x ][ y ] = 0;
            for( int i = 1 ; i <= b ; i ++ ){
                //D pro = 1.0 / (D)b;
                int wst = type * type;
                for( int j = 0 ; j < d ; j ++ )
                    if( take_bit( y , j ) == 0 ){
                        int nxty = y + bs[ j ] * i;
                        int tdp = DP2( x , nxty , turn + 1 );
                        wst = min( wst , tdp );
                    }
                dp2[ x ][ y ] += wst;
                //dp2[ x ][ y ] += pro * wst;
            }
        }else{
            dp2[ x ][ y ] = 0;
            for( int i = 1 ; i <= b ; i ++ ){
                //D pro = 1.0 / (D)b;
                int bst = 0;
                for( int j = 0 ; j < d ; j ++ )
                    if( take_bit( x , j ) == 0 ){
                        int nxtx = x + bs[ j ] * i;
                        int tdp = DP2( nxtx , y , turn + 1 );
                        bst = max( bst , tdp );
                    }
                dp2[ x ][ y ] += bst;
            }
        }
    }
    return dp2[ x ][ y ];
}
void solve(){
    printf( "%.12f %.12f\n" , (D)DP2( 0 , 0 , 0 ) / ( (D)type2 * (D)type2 ) ,
                                (D)DP1( 0 , 0 , 0 ) / ( (D)type2 * (D)type2 ) );
}
int main(){
    FILE("greater");
    while( scanf( "%d%d" , &d , &b ) == 2 && d ){
        init();
        solve();
    }
}
