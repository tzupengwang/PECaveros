#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 13
int n , tri[ N + N ];
char c[ N + N ][ N + N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i <= n + 1 ; i ++ )
    scanf( "%s" , c[ i ] );
  tri[ 0 ] = 1;
  for( int i = 1 ; i < N + N ; i ++ )
    tri[ i ] = tri[ i - 1 ] * 3;
}
int bt( int vl , int pos ){
  return ( vl / tri[ pos ] ) % 3;
}
int add( int vl , int pos , int nbt ){
  vl -= bt( vl , pos ) * tri[ pos ];
  vl += nbt * tri[ pos ];
  return vl;
}
int rr[ N ];
int clr[ N ] , cud[ N ];
#define MXS 1600000
LL dp[ 2 ][ MXS ][ 3 ];
bool inq[ 2 ][ MXS ][ 3 ];
vector< pair<int,int> > q[ 2 ];
void reset( int st ){
  for( auto i : q[ st ] ){
    dp[ st ][ i.first ][ i.second ] = 0;
    inq[ st ][ i.first ][ i.second ] = false;
  }
  q[ st ].clear();
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      rr[ i ] += ( c[ i ][ j ] == '.' );
  for( int i = 1 ; i <= n ; i ++ ){
    if( isalpha( c[ 0 ][ i ] ) )
      cud[ i ] ++;
    if( isalpha( c[ n + 1 ][ i ] ) )
      cud[ i ] ++;
    if( isalpha( c[ i ][ 0 ] ) )
      clr[ i ] ++;
    if( isalpha( c[ i ][ n + 1 ] ) )
      clr[ i ] ++;
  }
  int ini = 0;
  for( int i = 1 ; i <= n ; i ++ )
    ini = add( ini , i - 1 , cud[ i ] );
  dp[ 0 ][ ini ][ 0 ] = 1;
  q[ 0 ].push_back( { ini , 0 } );
  int pre = 1 , now = 0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      swap( pre , now );
      reset( now );
      if( j == 1 ){
        int nd = clr[ i ];
        if( rr[ i ] - clr[ i ] >= 0 ){
          for( auto pst : q[ pre ] ){
            int st = pst.first , rst = pst.second;
            if( rst ) continue;
            if( c[ i ][ j ] != '.' ){
              dp[ now ][ st ][ nd ] += dp[ pre ][ st ][ rst ];
              if( not inq[ now ][ st ][ nd ] ){
                inq[ now ][ st ][ nd ] = true;
                q[ now ].push_back( { st , nd } );
              }
              continue;
            }
            if( nd > 0 ){
              dp[ now ][ st ][ nd - 1 ] += dp[ pre ][ st ][ rst ];
              if( not inq[ now ][ st ][ nd - 1 ] ){
                inq[ now ][ st ][ nd - 1 ] = true;
                q[ now ].push_back( { st , nd - 1 } );
              }
            }
            int bb = bt( st , j - 1 );
            if( bb > 0 and c[ i ][ j ] == '.' ){
              int nst = add( st , j - 1 , bb - 1 );
              dp[ now ][ nst ][ nd ] += dp[ pre ][ st ][ rst ];
              if( not inq[ now ][ nst ][ nd ] ){
                inq[ now ][ nst ][ nd ] = true;
                q[ now ].push_back( { nst , nd } );
              }
            }
          }
        }
        continue;
      }
      for( auto pst : q[ pre ] ){
        int st = pst.first , rst = pst.second;
        if( c[ i ][ j ] != '.' ){
          dp[ now ][ st ][ rst ] += dp[ pre ][ st ][ rst ];
          if( not inq[ now ][ st ][ rst ] ){
            inq[ now ][ st ][ rst ] = true;
            q[ now ].push_back( { st , rst } );
          }
          continue;
        }
        if( rst > 0 ){
          dp[ now ][ st ][ rst - 1 ] += dp[ pre ][ st ][ rst ];
          if( not inq[ now ][ st ][ rst - 1 ] ){
            inq[ now ][ st ][ rst - 1 ] = true;
            q[ now ].push_back( { st , rst - 1 } );
          }
        }
        int bb = bt( st , j - 1 );
        if( bb > 0 and c[ i ][ j ] == '.' ){
          int nst = add( st , j - 1 , bb - 1 );
          dp[ now ][ nst ][ rst ] += dp[ pre ][ st ][ rst ];
          if( not inq[ now ][ nst ][ rst ] ){
            inq[ now ][ nst ][ rst ] = true;
            q[ now ].push_back( { nst , rst } );
          }
        }
      }
    }
  LL ans = dp[ now ][ 0 ][ 0 ] ;
  for( int i = 1 ; i <= n ; i ++ ){
    if( clr[ i ] > 1 and c[ i ][ 0 ] != c[ i ][ n + 1 ] )
      ans *= 2;
    if( cud[ i ] > 1 and c[ 0 ][ i ] != c[ n + 1 ][ i ] )
      ans *= 2 ;
  }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
