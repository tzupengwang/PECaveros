#include <bits/stdc++.h>
using namespace std;
vector<int> ans;
int n , m;
void print( int num , int bt ){
  for( int i = bt - 1 ; i >= 0 ; i -- )
    if( ( 1 << i ) & num ) putchar( '1' );
    else putchar( '0' );
  puts( "" );
}
void solve(){
  m = 1;
  while( ( 1 << m ) < n ) m ++;
  int p = 1 << ( m - 1 );
  for( int i = 0 ; i < p && n > 0 ; i ++ )
    if( ( p - i - 1 ) * 2 >= n - 1 ){
      print( i , m - 1 );
      n --;
    }else{
      print( i * 2 , m ); n --;
      if( n ){
        print( i * 2 + 1 , m );
        n --;
      }
    }
}
int main(){
  freopen( "binary.in" , "r" , stdin );
  freopen( "binary.out" , "w" , stdout );
  scanf( "%d" , &n );
  solve();
}
