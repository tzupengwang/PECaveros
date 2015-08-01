#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double D;
int cnt[ 2 ];
int n , k;
const ll mod = 242121643ll;
#define N 110
ll C[ N ][ N ];
void build(){
    for( int i = 0 ; i < N ; i ++ ) C[ i ][ 0 ] = C[ i ][ i ] = 1;
    for( int i = 2 ; i < N ; i ++ )
        for( int j = 1 ; j < i ; j ++ )
            C[ i ][ j ] = ( C[ i - 1 ][ j - 1 ] + C[ i - 1 ][ j ] ) % mod;
}
void init(){
    cnt[ 0 ] = cnt[ 1 ] = 0;
    for( int i = 0 ; i < n ; i ++ ){
        int tmp; scanf( "%d" , &tmp );
        if( tmp == 1 ) cnt[ 0 ] ++;
        else cnt[ 1 ] ++;
    }
}
void solve(){
    ll ans = 0;
    for( int i = 1 ; i <= cnt[ 0 ] ; i += 2 ){
        int nd = k - i;
        if( nd < 0 ) break;
        if( nd > cnt[ 1 ] ) continue;
        ll tans = ( C[ cnt[ 0 ] ][ i ] * C[ cnt[ 1 ] ][ nd ] ) % mod;
        ans = ( ans + tans ) % mod;
    }
    cout << ans << endl;
}
int main(){
    freopen( "game.in" , "r" , stdin );
    freopen( "game.out" , "w" , stdout );
    build();
    while( scanf( "%d%d" , &n , &k ) == 2 && n ){
        init();
        solve();
    }
}
