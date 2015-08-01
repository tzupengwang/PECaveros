#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 3010
map< tuple<ll,ll,ll> , int > M;
int n , m;
ll x[ N ] , y[ N ] , r[ N ];
ll sqr( ll tmp ){
    return tmp * tmp;
}
void init(){
    M.clear();
    for( int i = 0 ; i < n ; i ++ ){
        cin >> x[ i ] >> y[ i ];
        r[ i ] = x[ i ] * x[ i ] + y[ i ] * y[ i ];
    }
    for( int i = 0 ; i < n ; i ++ )
        for( int j = i + 1 ; j < n ; j ++ ){
            ll a = min( r[ i ] , r[ j ] );
            ll b = max( r[ i ] , r[ j ] );
            ll c = sqr( x[ i ] - x[ j ] ) + sqr( y[ i ] - y[ j ] );
            M[ make_tuple( a , b , c ) ] ++;
        }
}
void solve(){
    scanf( "%d" , &m );
    while( m -- ){
        ll a , b , c;
        cin >> a >> b >> c;
        if( a > b ) swap( a , b );
        if( M.count( make_tuple( a , b , c ) ) )
            cout << M[ make_tuple( a , b , c ) ] << endl;
        else puts( "0" );
    }
}
int main(){
    freopen( "astronomy.in" , "r" , stdin );
    freopen( "astronomy.out" , "w" , stdout );
    while( scanf( "%d" , &n ) == 1 && n ){
        init();
        solve();
    }
}
