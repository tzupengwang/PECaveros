#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10101
int n , k , s[ N ] , a[ N ];
int id[N], w[N];
int lq;

int wt[ N ];

int weight( int wi ){
  if( !wi ) return 0;
  return (1 << wi);
}

int which(){
  sort( id , id + n , [&](int x, int y) { return s[x] < s[y]; } );

  int mn = N;
  for( int i = 0 ; i < n ; i ++ )
    if( w[ i ] )
      mn = min( mn , w[ i ] );

  int tot = 0;
  for( int i = 0 ; i < n ; i ++ ) {
    tot += weight( w[ i ] );
  }

  int hv = 0;
  for( int _ = 0 ; _ < n ; _ ++ ) {
    int i = id[_];
    if( !w[ i ] ) continue;
    hv += weight( w[ i ] );
    //printf("%d %d\n", hv, tot);
    if (hv + hv >= tot) {
      lq = s[i];
      return s[i];
    }
  }
  assert(0);
}

int main(){
  /*
  int st = 100000;
  for (int i = 0; i < 50; i ++) {
    int k = (st + 1) / 2;
    int t = (k + 9) / 10;
    st -= t;
    printf("step %d: %d\n", i + 1, st);
  }

  return 0;
  */

  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ ) {
    scanf( "%d" , &s[ i ] );
    w[i] = k;
    id[i] = i;
  }

  while( true ){
    printf( "%d\n" , which() );
    fflush( stdout );
    char buf[ 99 ];
    scanf( "%s" , buf );
    if( !strcmp( buf , "End" ) ) break;

    if (buf[0] == '<') {
      for (int i = 0; i < n; i ++) if (s[i] && s[i] <= lq) w[i] --;
    } else if (buf[0] == '>') {
      for (int i = 0; i < n; i ++) if (s[i] && s[i] >= lq) w[i] --;
    }

    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &s[ i ] );
  }
}
