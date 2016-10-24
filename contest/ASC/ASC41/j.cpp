#include <bits/stdc++.h>
using namespace std;
#define N 33
int n , m;
char c[ N ][ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
}
typedef long long LL;
typedef pair<long long,long long> PLL;
#define X first
#define Y second
inline PLL operator-( const PLL& p1 , const PLL& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator*( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline LL operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
int ori( const PLL& o , const PLL& a , const PLL& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const PLL& p1 , const PLL& p2 ,
             const PLL& q1 , const PLL& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) <= 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) <= 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) <= 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) <= 0;
  }
  return ( ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0 ) &&
         ( ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0 );
}
bool bye[ N ][ N ][ N ][ N ];
bool Bye( int i1 , int j1 , int i2 , int j2 ){
  int li = min( i1 , i2 ) , ri = max( i1 , i2 );
  int lj = min( j1 , j2 ) , rj = max( j1 , j2 );
  for( int ii = li ; ii <= ri ; ii ++ )
    for( int jj = lj ; jj <= rj ; jj ++ )
      if( c[ ii ][ jj ] == '#' ){
        if( banana( { i1 * 2 , j1 * 2 } , { i2 * 2 , j2 * 2 } ,
                    { ii * 2 - 1 , jj * 2 - 1 } , { ii * 2 - 1 , jj * 2 + 1 } ) )
          return false;
        if( banana( { i1 * 2 , j1 * 2 } , { i2 * 2 , j2 * 2 } ,
                    { ii * 2 - 1 , jj * 2 - 1 } , { ii * 2 + 1 , jj * 2 - 1 } ) )
          return false;
        if( banana( { i1 * 2 , j1 * 2 } , { i2 * 2 , j2 * 2 } ,
                    { ii * 2 + 1 , jj * 2 + 1 } , { ii * 2 - 1 , jj * 2 + 1 } ) )
          return false;
        if( banana( { i1 * 2 , j1 * 2 } , { i2 * 2 , j2 * 2 } ,
                    { ii * 2 + 1 , jj * 2 + 1 } , { ii * 2 + 1 , jj * 2 - 1 } ) )
          return false;
      }
  return true;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( c[ i ][ j ] == '.' )
        for( int ii = 0 ; ii < n ; ii ++ )
          for( int jj = 0 ; jj < m ; jj ++ )
            if( c[ ii ][ jj ] == '.' )
              bye[ i ][ j ][ ii ][ jj ] = Bye( i , j , ii , jj );
  vector< pair<int,int> > ans;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( c[ i ][ j ] == '.' ){
        bool okay = true;
        for( int ii = 0 ; ii < n && okay ; ii ++ )
          for( int jj = 0 ; jj < m && okay ; jj ++ ){
            if( i == ii && j == jj ) continue;
            if( c[ i ][ j ] == '.' ){
              bool tokay = false;
              for( int ti = i ; ti < n && !tokay ; ti ++ ){
                if( c[ ti ][ j ] == '#' ) break;
                if( !bye[ ti ][ j ][ ii ][ jj ] )
                  tokay = true;
              }
              for( int ti = i ; ti >= 0 && !tokay ; ti -- ){
                if( c[ ti ][ j ] == '#' ) break;
                if( !bye[ ti ][ j ][ ii ][ jj ] )
                  tokay = true;
              }
              for( int tj = j ; tj < m && !tokay ; tj ++ ){
                if( c[ i ][ tj ] == '#' ) break;
                if( !bye[ i ][ tj ][ ii ][ jj ] )
                  tokay = true;
              }
              for( int tj = j ; tj >= 0 && !tokay ; tj -- ){
                if( c[ i ][ tj ] == '#' ) break;
                if( !bye[ i ][ tj ][ ii ][ jj ] )
                  tokay = true;
              }
              if( !tokay ) okay = false;
            }
          }
        if( okay )
          ans.push_back( { i , j } );
      }
  printf( "%d\n" , (int)ans.size() );
  for( auto i : ans )
    printf( "%d %d\n" , i.first + 1 , i.second + 1 );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "jealous.in" , "r" , stdin );
  freopen( "jealous.out" , "w" , stdout );
#endif
  init();
  solve();
}
