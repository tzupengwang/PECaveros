#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double D;
const ll mod = 998244353ll;
ll magic[ 4 ][ 4 ] = { { 1 , 1 , 0 , 0 },
                { 1 , 2 , 0 , 1 },
                { 1 , 2 , 1 , 2 },
                { 0 , 0 , 1 , 1 } };
class Mat{
public:
    ll a[ 4 ][ 4 ];
    Mat(){
        for( int i = 0 ; i < 4 ; i ++ )
            for( int j = 0 ; j < 4 ; j ++ )
                a[ i ][ j ] = 0;
    }
    Mat operator+( const Mat & m ) const{
        Mat tans;
        for( int i = 0 ; i < 4 ; i ++ )
            for( int j = 0 ; j < 4 ; j ++ )
                tans.a[ i ][ j ] = ( a[ i ][ j ] + m.a[ i ][ j ] ) % mod;
        return tans;
    }
    Mat operator*( const Mat & m ) const{
        Mat tans;
        for( int i = 0 ; i < 4 ; i ++ )
            for( int j = 0 ; j < 4 ; j ++ )
                for( int k = 0 ; k < 4 ; k ++ )
                    tans.a[ i ][ j ] = ( tans.a[ i ][ j ] + ( a[ i ][ k ] * m.a[ k ][ j ] ) % mod ) % mod;
        return tans;
    }
    Mat operator^( int & k ) const{
        Mat I , A = *this;
        for( int i = 0 ; i < 4 ; i ++ ) I.a[ i ][ i ] = 1;
        while( k ){
            if( k & 1 ) I = I * A;
            A = A * A; k >>= 1;
        }
        return I;
    }
};
int n;
void init(){
    
}
void solve(){
    Mat tmp;
    for( int i = 0 ; i < 4 ; i ++ )
        for( int j = 0 ; j < 4 ; j ++ )
            tmp.a[ i ][ j ] = magic[ i ][ j ];
    Mat ans = tmp ^ n;
    cout << ans.a[ 0 ][ 0 ] << endl;
}
int main(){
    freopen( "figure.in" , "r" , stdin );
    freopen( "figure.out" , "w" , stdout );
    while( scanf( "%d" , &n ) == 1 && n ){
        init();
        solve();
    }
}
