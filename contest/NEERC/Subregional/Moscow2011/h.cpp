#include <bits/stdc++.h>
using namespace std;
int n;
bool is_p( int x ){
  if( x == 1 ) return false;
  if( x == 4 ) return true;
  for( long long i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 )
      return false;
  return true;
}
int main(){
  scanf( "%d" , &n );
  puts( is_p( n ) ? "NO" : "YES" );
}
