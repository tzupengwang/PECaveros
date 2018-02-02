#include<bits/stdc++.h>
using namespace std;

#define N 22

int n, k;

double dp[N][N][222];

int c[ N ] , f[ N ];  
bool pls[ N ][ N ];
int vl[ N ][ N ];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) {
    //int c, f;
    //scanf("%d%d", &c, &f);

    //for (int j = 0; j < f; j ++) {
    //}
    scanf( "%d%d" , &c[ i ] , &f[ i ] );

    for( int j = 0 ; j < f[ i ] ; j ++ ){
      char buf[ 64 ];
      scanf( "%s" , buf );
      int dump;
      if( sscanf( buf , "+%d" , &dump ) == 1 ){
        pls[ i ][ j ] = true;
        vl[ i ][ j ] = dump;
      }else{
        assert( sscanf( buf , "%d" , &vl[ i ][ j ] ) == 1 );
      }
    }

    dp[i][0][0] = 1;
    for (int j = 1; j <= c[i]; j ++) {
      dp[i][j][0] = 1;
      for (int v = 1; v <= 130 /*c[i] * f[i]*/; v ++) {
        for (int K = 0; K < f[i]; K ++) {
          int t = vl[i][K];
          if (pls[i][K]) {
            if (t > v) dp[i][j][v] += 1. / f[i];
            else dp[i][j][v] += 1. / f[i] * dp[i][j][v - t];
          } else {
            if (t > v) dp[i][j][v] += 1. / f[i];
            else dp[i][j][v] += 1. / f[i] * dp[i][j - 1][v - t];
          }
        }
      }
    }
  }

  scanf("%d", &k);
  //for (int i = 1; i <= k; i ++) {
    //printf("%.6f\n", dp[0][c[0]][i]);
  //}
  for (int i = 2; i <= k + 1; i ++) {
    int can = 0;
    for (int j = 1; j < n; j ++) {
      if (dp[j][c[j]][i] > dp[can][c[can]][i])
        can = j;
    }
    printf("%d\n", can + 1);
  }
}
