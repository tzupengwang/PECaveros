#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define K 60
typedef long long LL;
LL n , s , a[ N ];
LL cc[ K ];
bool ok[ K + 4 ][ N ];
int fr[ K + 4 ][ N ];
vector< int > v[ K + 4 ][ N ];
LL dp[ K + 4 ][ N ];
int main(){
  cin >> n >> s;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> a[ i ];
    for( int j = 0 ; j < K ; j ++ )
      if( (a[ i ] >> j) & 1LL )
        cc[ j ] ++;
  }
  ok[ 0 ][ 0 ] = true;
  dp[ 0 ][ 0 ] = 0;
  for( int i = 0 ; i < K ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      if( not ok[ i ][ j ] ) continue;
      for( int k = 0 ; k < 2 ; k ++ ){
        int tot = j + ( k == 0 ? cc[ i ] : n - cc[ i ] );
        if( tot == 0 and ( (s >> i) & 1LL ) )
          continue;
        if( (s >> i) & 1LL ) tot --;
        if( tot % 2 ) continue;
        tot >>= 1;
        if( not ok[ i + 1 ][ tot ] ){
          ok[ i + 1 ][ tot ] = true;
          dp[ i + 1 ][ tot ] = dp[ i ][ j ] + (1LL << i) * k;
        }else{
          dp[ i + 1 ][ tot ] = min( dp[ i + 1 ][ tot ] ,
                                    dp[ i ][ j ] + (1LL << i) * k );
        }
      }
    }
  if( ok[ K ][ 0 ] )
    printf( "%lld\n" , dp[ K ][ 0 ] );
  else
    puts( "-1" );
}
