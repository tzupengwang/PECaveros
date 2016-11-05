#include <bits/stdc++.h>
using namespace std;
#define N 514
typedef long long LL;
LL t , a[ N ] , b[ N ] , c[ N ];
void init(){
  scanf( "%lld" , &t );
  for( int i = 0 ; i < t ; i ++ )
    scanf( "%lld%lld%lld" , &a[ i ] , &b[ i ] , &c[ i ] );
}
void solve(){
  LL sa = 0 , sb = 0 , sc = 0;
  for( int i = 0 ; i < t ; i ++ ){
    sa += a[ i ];
    sb += b[ i ];
    sc += c[ i ];
    if( min( sa , min( sb , sc ) ) < 30 ){
      puts( "NO" );
    }else{
      LL bb = min( sa , min( sb , sc ) );
      printf( "%lld\n" , bb );
      sa -= bb;
      sb -= bb;
      sc -= bb;
    }
  }
}
int main(){
  init();
  solve();
}
