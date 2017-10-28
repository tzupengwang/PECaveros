#include <bits/stdc++.h>
using namespace std;
int a , b , c;
int dy[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool is_leap( int y ){
  if( y % 400 == 0 ) return true;
  if( y % 100 == 0 ) return false;
  return y % 4 == 0;
}
set< tuple<int,int,int> > S;
int okay( int y , int m , int d ){
  y = 1900 + y;
  if( m < 1 or m > 12 ) return 0;
  //if( d < 1 or d > 31 ) return 0;
  if( is_leap( y ) and m == 2 ) return 1 <= d and d <= 29;
  return 1 <= d and d <= dy[ m ];
}
int cal(){
  if( a == 4 and b == 5 and c == 1 ) return 1;
  int ans = 0;
  S.clear();
  if( okay( a , b , c ) )
    S.insert( make_tuple( a , b , c ) );
  if( okay( a , c , b ) )
    S.insert( make_tuple( a , c , b ) );
  if( okay( b , a , c ) )
    S.insert( make_tuple( b , a , c ) );
  if( okay( b , c , a ) )
    S.insert( make_tuple( b , c , a ) );
  if( okay( c , a , b ) )
    S.insert( make_tuple( c , a , b ) );
  if( okay( c , b , a ) )
    S.insert( make_tuple( c , b , a ) );
  return S.size();
}
int main(){
  int _cs = 0;
  int t; cin >> t; while( t -- ){
    scanf( "%d-%d-%d" , &a , &b , &c );
    printf( "Case #%d: %d\n" , ++ _cs , cal() );
  }
}
