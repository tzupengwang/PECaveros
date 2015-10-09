#include <bits/stdc++.h>
using namespace std;
#define N 110
char c[ N ][ N ];
int all , hf , n , m;
void init(){
    freopen( "ascii.in" , "r" , stdin );
    freopen( "ascii.out" , "w" , stdout );
    scanf( "%d%d" , &n , &m );
    for( int i = 0 ; i < n ; i ++ )
        scanf( "%s" , c[ i ] );
}
void solve(){
    for( int i = 0 ; i < n ; i ++ ){
        int yes = 0;
        for( int j = 0 ; j < m ; j ++ )
            if( c[ i ][ j ] == '.' ){
                if( yes ) all ++;
            }else if( c[ i ][ j ] == '/' ||
                      c[ i ][ j ] == '\\' ){
                yes = 1 - yes;
                hf ++;
            }
    }
    cout << all + hf / 2 << endl;
}
int main(){
    init();
    solve();
}
