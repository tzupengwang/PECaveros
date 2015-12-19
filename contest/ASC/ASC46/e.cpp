#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double D;
#define N 3010
int n;
ll a[ N ] , dp[ N ] , psum[ N ] , pdp[ N ][ N ];
ll Sum( int l , int r ){
    if( l > r ) return 0;
    return psum[ r ] - psum[ l - 1 ];
}
void init(){
    for( int i = 1 ; i <= n ; i ++ ){
        cin >> a[ i ];
        psum[ i ] = psum[ i - 1 ] + a[ i ];
    }
    for( int i = 1 ; i <= n ; i ++ ){
        ll tsum = 0;
        for( ll j = i , b = 0 ; j >= 1 ; j -- , b += 2 ){
            tsum += a[ j ] * b;
            pdp[ i ][ j ] = tsum;
        }
    }
}
ll magic( ll j , ll i ){
    if( j >= i ) return 0;
    ll dlt = i - j;
    return 4 * dlt - 2;
    return 2 * dlt + 2 * ( dlt - 1 );
}
void solve(){
    for( int i = 1 ; i <= n ; i ++ ){
        ll sdlt = 0;
        dp[ i ] = dp[ i - 1 ] + Sum( i + 1 , n ) * 2ll + a[ i ];
        for( int j = i - 2 ; j >= 0 ; j -- ){
            ll dlt = ( i - j - 1 ) * 3ll * a[ j + 1 ];
            ll tsum = Sum( j + 2 , i ); 
            ll cst = pdp[ i ][ j + 1 ] + (ll)( i - j ) * Sum( j + 1 , i ) + Sum( i + 1 , n ) * magic( j , i );
            if( dlt > tsum ) sdlt += dlt - tsum;
            dp[ i ] = min( dp[ i ] , dp[ j ] + cst - sdlt );
        }
        //cout << dp[ i ] << endl;
    }
    cout << dp[ n ] - psum[ n ] << endl;
}
int main(){
    freopen( "ebola.in" , "r" , stdin );
    freopen( "ebola.out" , "w" , stdout );
    while( scanf( "%d" , &n ) == 1 && n ){
        init();
        solve();
    }
}
