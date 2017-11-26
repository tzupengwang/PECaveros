#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 303030
double e[ N ] , deg[ N ];
vector<int> v[ N ] , q;
bool tag[ N ];
int n , m;

int id[N], rid[N];

int main(){
  clock_t s = clock();
  scanf( "%d%d" , &n , &m );
  //n = 100000;
  //m = 300000;
  while( m -- ){
    int a , b;
    scanf( "%d%d" , &a , &b );
    //a = rand() % n + 1;
    //b = rand() % n + 1;
    v[ a ].push_back( b );
    v[ b ].push_back( a );
    deg[ a ] += 1;
    deg[ b ] += 1;
  }
  for( int i = 1 ; i < n ; i ++ )
    e[ i ] = n;
  tag[ n ] = true;
  q.push_back( n );
  for( size_t i = 0 ; i < q.size() ; i ++ ){
    int now = q[ i ];
    for( int nxt : v[ now ] ){
      if( tag[ nxt ] ) continue;
      tag[ nxt ] = true;
      q.push_back( nxt );
    }
  }
  int esz = q.size();
  for (int i = 0; i < esz; i ++) {
    id[i] = q[i];
    rid[q[i]] = i;
  }
  int iter = 0;
  for( int _ = 0 ; ; _ ++ ){
    if( _ % 5 == 0 and ( (clock() - s) > 2.6 * CLOCKS_PER_SEC ) )
      break;
    for( int i = 1 ; i < esz ; i ++ ){
      int now = id[ i ] , cnt = 0;
      double cur = 0;
      for( int nxt : v[ now ] )
        if( rid[ nxt ] < rid[ now ] )
          cur += e[ nxt ];
        else
          cnt ++;
      e[ now ] = (1 + cur / deg[ now ]) * deg[ now ] / (deg[now] - cnt);
    }

    for (int i = 0; i < esz; i ++) {
      id[i] = q[i];
    }
    sort(id, id + esz, [&](int x, int y) {
      return e[x] < e[y];
    });
    for (int i = 0; i < esz; i ++) {
      rid[id[i]] = i;
    }
    
    //if( (++ iter) < 20 ){
      //for( int i = 1 ; i <= 10 ; i ++ )
        //printf( "%.6f%c" , e[ i ] , " \n"[ i == 10 ] );
    //}
  }
  cerr << iter << endl;
  printf( "%.12f\n" , e[ 1 ] );
}
