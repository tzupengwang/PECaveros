#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
#define N 101010
const int inf = 1000000000;
LL n , t[ N ];
void init(){
  n = getint();
  //n = 100000;
  t[ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    t[ i ] = getint();
    //t[ i ] = rand();
  t[ n + 1 ] = inf;
  n += 2;
}
LL dp[ N ];
void solve(){
  for( int i = 1 ; i < n ; i ++ )
    dp[ i ] = (LL)inf * N;
  LL pmx = -1;
  for( int i = 0 ; i + 1 < n ; i ++ ){
    LL c = 0 , sm = 0 , smc = 0 , mx = pmx;
    if( dp[ i ] + (n - 1 - i) <= dp[ n - 1 ] ){
      for( int j = i + 1 ; j < n ; j ++ ){
        LL ndp = dp[ i ] + c + sm * t[ i ] - smc;
        if( ndp >= dp[ n - 1 ] ) break;
        if( ndp < dp[ j ] and t[ j ] >= t[ i ] )
          dp[ j ] = ndp;
        if( t[ j ] > t[ i ] ){
          if( t[ j ] >= mx ) mx = t[ j ];
          else c += mx - t[ j ];
        }else
          sm ++ , smc += t[ j ];
      }
    }
    pmx = max( pmx , t[ i ] );
  }
  printf( "%lld\n" , dp[ n - 1 ] );
}
int main(){
  init();
  solve();
}
