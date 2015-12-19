//by tzupengwangâ„¢
#include<bits/stdc++.h>
using namespace std;

#define FO(it,c) for (__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
typedef long long ll;
typedef pair<int,int> ii;

int n ;
vector< int > st ;

int hd[ 200005 ] , tl[ 200005 ] ;
int val[ 200005 ] ;
int s[ 200005 ][ 20 ] ;
int dep[ 200005 ] ;

int cnt ;

bool isanc( int a , int b ) {
    if ( dep[ a ] > dep[ b ] ) return false ;
    int qq = dep[ b ] - dep[ a ] ;
    for ( int i = 0 ; i < 20 ; i ++ ) if ( qq & ( 1 << i ) ) b = s[ b ][ i ] ;
    return a == b ;
}

void init() {
    scanf( "%d" , &n ) ;
    cnt = 1 ;
    hd[ 0 ] = -1 , tl[ 0 ] = 0 , dep[ 0 ] = 0 ;
    for ( int i = 0 ; i < 20 ; i ++ ) s[ 0 ][ i ] = 0 ;

    for ( int i = 1 ; i <= n ; i ++ ) {
        int type ;
        scanf( "%d" , &type ) ;
        if ( type == 1 ) {
            int v , x ;
            scanf( "%d%d" , &v , &x ) ;
            int num = cnt ++ ;
            val[ num ] = x ;
            s[ num ][ 0 ] = tl[ v ] ;
            dep[ num ] = dep[ tl[ v ] ] + 1 ;
            for ( int j = 1 ; j < 20 ; j ++ ) s[ num ][ j ] = s[ s[ num ][ j - 1 ] ][ j - 1 ] ;
            tl[ i ] = num ;
            hd[ i ] = hd[ v ] ;
            if ( hd[ i ] == -1 ) hd[ i ] = num ;
        } else {
            int v ;
            scanf( "%d" , &v ) ;
            printf( "%d\n" , val[ hd[ v ] ] ) ;
            int pre = tl[ v ] ;
            for ( int j = 19 ; j >= 0 ; j -- ) if ( !isanc( s[ pre ][ j ] , hd[ v ] ) ) pre = s[ pre ][ j ] ;
            if ( pre == hd[ v ] ) hd[ i ] = -1 ;
            else hd[ i ] = pre ;
            tl[ i ] = tl[ v ] ;
        }
    }
}

void process() {
}

int main() {
    freopen( "queue.in" , "r" , stdin ) ;
    freopen( "queue.out" , "w" , stdout ) ;
    init() ;
    process() ;
    return 0 ;
}
