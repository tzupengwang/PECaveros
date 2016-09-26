#include <bits/stdc++.h>
using namespace std;
#define N 202020
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
int n;
Pt p[ N ] , o[ 2 ];
bool init(){
  scanf( "%d" , &n );
  if( n == 0 ) return false;
  for( int i = 0 ; i < n ; i ++ ){
    int xi , yi; scanf( "%d%d" , &xi , &yi );
    p[ i ] = p[ i + n ] = { xi , yi };
  }
  for( int i = 0 ; i < 2 ; i ++ )
    scanf( "%lld%lld" , &o[ i ].X , &o[ i ].Y );
  return true;
}
LL ans;
inline int cal( int x ){
  int al = x + n , ar = x;
  {
    int bl = x + 2 , br = x + n - 2;
    while( bl <= br ){
      int bmid = ( bl + br ) >> 1;
      LL ret1 = ( p[ bmid ] - p[ x ] ) ^ ( o[ 0 ] - p[ x ] );
      LL ret2 = ( p[ bmid ] - p[ x ] ) ^ ( o[ 1 ] - p[ x ] );
      if( ret1 > ret2 ) swap( ret1 , ret2 );
      if( ret1 < 0 && ret2 > 0 ) al = bmid , br = bmid - 1;
      else if( ret1 >= 0 && ret2 >= 0 ) bl = bmid + 1;
      else br = bmid - 1;
    }
  }
  {
    int bl = x + 2 , br = x + n - 2;
    while( bl <= br ){
      int bmid = ( bl + br ) >> 1;
      LL ret1 = ( p[ bmid ] - p[ x ] ) ^ ( o[ 0 ] - p[ x ] );
      LL ret2 = ( p[ bmid ] - p[ x ] ) ^ ( o[ 1 ] - p[ x ] );
      if( ret1 > ret2 ) swap( ret1 , ret2 );
      if( ret1 < 0 && ret2 > 0 ) ar = bmid , bl = bmid + 1;
      else if( ret1 >= 0 && ret2 >= 0 ) bl = bmid + 1;
      else br = bmid - 1;
    }
  }
  return max( ar - al + 1 , 0 );
}
void solve(){
  ans = 0;
  for( int i = 0 ; i < n ; i ++ )
    ans += cal( i );
  printf( "%lld\n" , ans / 2 );
}
int main(){
  freopen( "kingdom.in" , "r" , stdin );
  freopen( "kingdom.out" , "w" , stdout );
  while( init() ) solve();
}
