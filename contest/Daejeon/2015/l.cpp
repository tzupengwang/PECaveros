#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , m , k[ N ];
string a , b;
void init(){
  scanf( "%d%d" , &n , &m );
  a = b = "";
  for( int i = 0 ; i < m ; i ++ ){
    int u; scanf( "%d" , &u );
    a += (char)( u + '0' );
  }
  for( int i = 0 ; i < m ; i ++ ){
    int u; scanf( "%d" , &u );
    b += (char)( u + '0' );
  }
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &k[ i ] );
}
bool okay( int x ){
  string c = "";
  for( int i = x ; i < x + m ; i ++ )
    c += (char)( k[ i % n ] + '0' );
  return a <= c && c <= b;
}
void solve(){
  int ans = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( okay( i ) )
      ans ++;
  printf( "%d\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
