#include <bits/stdc++.h>
using namespace std;
int n;
#define K 100
char c[ K ][ K ];
int dis[ K ][ K ] , len[ K ];
int dp[ 1 << 15 ][ 15 ];
int tg[ 1 << 15 ][ 15 ] , stmp;
int DP( int msk , int cur ){
  if( msk == (1 << cur) )
    return len[ cur ];
  if( tg[ msk ][ cur ] == stmp )
    return dp[ msk ][ cur ];
  tg[ msk ][ cur ] = stmp;
  int nmsk = msk ^ (1 << cur);
  int tans = 1e6;
  for( int pre = 0 ; pre < n ; pre ++ )
    if( ( nmsk >> pre ) & 1 )
      tans = min( tans , DP( nmsk , pre ) + dis[ pre ][ cur ] );
  return dp[ msk ][ cur ] = tans;
}
bool in[ K ][ K ];
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    for( int i = 0 ; i < n ; i ++ ){
      scanf( "%s" , c[ i ] );
      len[ i ] = strlen( c[ i ] );
    }
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ ){
        in[ i ][ j ] = false;
        if( i == j ) continue;
        for( int st = 0 ; st <= len[ j ] - len[ i ] ; st ++ ){
          bool ok = true;
          for( int k = 0 ; k < len[ i ] ; k ++ )
            if( c[ i ][ k ] != c[ j ][ k + st ] ){
              ok = false;
              break;
            }
          if( ok ){
            in[ i ][ j ] = true;
            break;
          }
        }
      }
    vector<int> res;
    for( int i = 0 ; i < n ; i ++ ){
      bool keep = true;
      for( int j = 0 ; j < n ; j ++ )
        if( in[ i ][ j ] ){
          keep = false;
          break;
        }
      if( keep )
        res.push_back( i );
    }
    n = (int)res.size();
    for( int i = 0 ; i < n ; i ++ ){
      len[ i ] = len[ res[ i ] ];
      for( int j = 0 ; j < len[ i ] ; j ++ )
        c[ i ][ j ] = c[ res[ i ] ][ j ];
    }
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ ){
        if( i == j ) continue;
        int s = min( len[ i ] , len[ j ] );
        int dlt = 0;
        for( int k = s ; k > 0 ; k -- ){
          bool ok = true;
          for( int ii = len[ i ] - k , jj = 0 ; jj < k ; ii ++ , jj ++ )
            if( c[ i ][ ii ] != c[ j ][ jj ] ){
              ok = false;
              break;
            }
          if( ok ){
            dlt = k;
            break;
          }
        }
        dis[ i ][ j ] = len[ j ] - dlt;
      }
    ++ stmp;
    int ans = 1e6;
    for( int i = 0 ; i < n ; i ++ )
      ans = min( ans , DP( (1 << n) - 1 , i ) );
    printf( "%d\n" , ans );
  }
}
