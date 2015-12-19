//by tzupengwang™
#include<bits/stdc++.h>
using namespace std;

#define FO(it,c) for (__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
typedef long long ll;
typedef pair<int,int> ii;

int n , k ;
vector< int > v ;

void init() {
    scanf( "%d%d" , &n , &k ) ;
    for ( int i = 1 ; i * i < n ; i ++ ) {
        v.push_back( n - i * i ) ;
    }
}

int dp[ 32 ][ 200005 ] ;

void process() {
    memset( dp , -1 , sizeof dp ) ;
    dp[ 0 ][ 0 ] = 0 ;
    for ( int i = 0 ; i < (int)v.size() ; i ++ ) {
        for ( int p = k - 1 ; p >= 0 ; p -- ) {
            for ( int j = n - v[ i ] ; j >= 0 ; j -- ) if ( dp[ p ][ j ] != -1 && dp[ p + 1 ][ j + v[ i ] ] == -1 ) {
                dp[ p + 1 ][ j + v[ i ] ] = j ;
            }
        }
    }
    if ( dp[ k ][ n ] == -1 ) puts( "NO" ) ;
    else {
        puts( "YES" ) ;
        int t = n ;
        while ( k ) {
            printf( "%d " , t - dp[ k ][ t ] ) ;
            t = dp[ k ][ t ] , k -- ;
        }
        puts( "" ) ;
    }
}

int main() {
    freopen( "squary.in" , "r" , stdin ) ;
    freopen( "squary.out" , "w" , stdout ) ;
    init() ;
    process() ;
    return 0 ;
}
