#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<ll> pset;
#define N 10000
bool p[ N + N ];
#define K 32
ll m[ K ][ K ];
#define SEED 514514
void init(){
    scanf( "%d" , &n );
    for( ll i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
        pset.push_back( i );
        if( (int)pset.size() == 5 * n ) break;
        for( ll j = N / i ; j >= i ; j -- )
            p[ i * j ] = true;
    }
}
bool notokay(){
    set<ll> S;
    for( int i = 0 ; i < n ; i ++ )
        for( int j = 0 ; j < n ; j ++ ){
            if( S.count( m[ i ][ j ] ) )
                return true;
            S.insert( m[ i ][ j ] );
        }
    return false;
}
void solve(){
    vector<int> tv;
    for( int i = 0 ; i < n ; i ++ )
        tv.push_back( i );
    do{
        for( int i = 0 ; i < n ; i ++ )
            for( int j = 0 ; j < n ; j ++ )
                m[ i ][ j ] = 1;
        for( int i = 0 ; i < 5 ; i ++ ){
            random_shuffle( tv.begin() , tv.end() );
            for( int j = 0 ; j < n ; j ++ ){
                for( int k = 0 ; k < n ; k ++ )
                    m[ j ][ ( tv[ j ] + k ) % n ] *= pset[ i * n + k ];
            }
        }
    }while( notokay() );
    for( int i = 0 ; i < n ; i ++ )
        for( int j = 0 ; j < n ; j ++ ){
            cout << m[ i ][ j ];
            if( j == n - 1 ) puts( "" );
            else putchar( ' ' );
        }
}
int main(){
    freopen( "elegant.in" , "r" , stdin );
    freopen( "elegant.out" , "w" , stdout );
    srand( SEED );
    init();
    solve();
}
