
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 302
const int K = 8;
const int mod = 1000000007;
inline int add( int ai , int bi ){
  ai += bi;
  return ai >= mod ? ai - mod : ai;
}
inline int mul( LL ai , int bi ){
  ai *= bi;
  return ai >= mod ? ai % mod : ai;
}
int n;
void mul( int a[ N ][ N ] , int b[ N ][ N ] , int c[ N ][ N ] ){ // to c
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      c[ i ][ j ] = 0;
      for( int k = 0 ; k < n ; k ++ )
        c[ i ][ j ] = add( c[ i ][ j ] ,
                           mul( a[ i ][ k ] , b[ k ][ j ] ) );
    }
}
bool is_zero( int c[ N ][ N ] ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( c[ i ][ j ] )
        return false;
  return true;
}
int m[ 9 ][ N ][ N ];
int tmp[ 11 ][ N ][ N ];
int v[K][N][N], w[N], u[N];
int ord[K];
bool chk(int e) {
  for (int t = 0; t < K; ++t) {
    int mx = *max_element(v[t][e], v[t][e]+n);
    if (mx != 0) return 0;
  }
  return 1;
}
int main(){
  srand(514514);
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      scanf( "%d" , &m[ 0 ][ i ][ j ] );
  for (int t = 0; t < K; ++t) {
    for (int j = 0; j < n; ++j) {
      v[t][0][j] = rand() & 1;
    }
    for (int e = 0; e < n; ++e) {
      fill(v[t][e+1], v[t][e+1]+n, 0);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          v[t][e+1][i] = add(v[t][e+1][i], mul(m[0][i][j], v[t][e][j]));
        }
      }
    }
  }
  int ans = -1;
  for (int e = 1; e <= n; ++e) {
    if (chk(e)) {
      ans = e;
      break;
    }
  }
  if( ans != -1 )
    printf( "%d\n" , ans );
  else
    puts( "Infinity" );
}
