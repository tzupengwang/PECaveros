#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
#define K 20
int n , k , a[ N ];
LL whol[ N ][ K ];
LL whor[ N ][ K ];
LL dpl[ N ][ K ];
LL dpr[ N ][ K ];
LL gr[K][K];
int grp[K][K];
LL gl[K][K];
int glp[K][K];
const LL INF = 1e16;

LL ans;
int ansl, ansr, ansc;
void update(LL val, int l, int r, int ch) {
  if (val > ans) {
    // printf("update %lld %d %d %d\n", val, l, r, ch);
    ans = val, ansl = l, ansr = r, ansc = ch;
  }
}

void go( int l , int r ){
  if (l == r) {
    update(a[l], l, r, 0);
    return;
  }
  int mid = (l + r) >> 1;
  go(l, mid);
  go(mid + 1, r);

  // printf("go %d %d\n", l, r);
  // clear gl, gr
  for (int i = 0; i <= k; i ++) {
    for (int j = 0; j <= k; j ++) {
      gl[i][j] = gr[i][j] = -INF;
    }
  }

  dpr[mid + 1][0] = 0;
  for (int i = mid; i >= l; i --) {
    for (int j = 0; j <= k; j ++) {
      if (j == 0) {
        dpr[i][0] = a[i] + dpr[i + 1][0];
      } else {
        if (mid - i + 1 < j) break;
        dpr[i][j] = dpr[i + 1][j - 1];
        if (mid - i >= j) {
          dpr[i][j] = max(dpr[i][j], dpr[i + 1][j] + a[i]);
        }
          // printf("dpr %d %d = %lld\n", i, j, dpl[i][j]);
      }
      for (int p = 0; p <= k; p ++) {
        if (p > i - 1) break;
        if (gl[j][p] < dpr[i][j] + whol[i - 1][p]) {
          gl[j][p] = dpr[i][j] + whol[i - 1][p];
          // printf("glp %d %d %d = %lld\n", j, p, i, gl[j][p]);
          glp[j][p] = i;
        }
      }
    }
  }
  dpl[mid][0] = 0;
  for (int i = mid + 1; i <= r; i ++) {
    for (int j = 0; j <= k; j ++) {
      if (j == 0) {
        dpl[i][0] = a[i] + dpl[i - 1][0];
      } else {
        if (i - mid < j) break;
        dpl[i][j] = dpl[i - 1][j - 1];
        if (i - mid - 1 >= j) {
          dpl[i][j] = max(dpl[i][j], dpl[i - 1][j] + a[i]);
        }
      }
      for (int p = 0; p <= k; p ++) {
        if (p > n - i) break;
        if (gr[j][p] < dpl[i][j] + whor[i + 1][p]) {
          gr[j][p] = dpl[i][j] + whor[i + 1][p];
          // printf("grp %d %d %d = %lld\n", j, p, i, gr[j][p]);
          grp[j][p] = i;
        }
      }
    }
  }

  for (int i = 0; i <= k; i ++) {
    for (int j = 0; i + j <= k; j ++) {
      for (int p = 0; p <= i + j; p ++) {
        if (gr[i][p] > -INF && gl[j][i + j - p] > -INF) {
          // printf("pre-update %d %d %d\n", i, j, p);
          update(gr[i][p] + gl[j][i + j - p], glp[j][i + j - p], grp[i][p], i + j);
        }
      }
    }
  }
}

int main(){
  scanf( "%d" , &n );
  k = 1;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );

  ans = 0;
  for (int i = 0; i <= n + 1; i ++) {
    for (int j = 0; j <= k; j ++) {
      whol[i][j] = whor[i][j] = -INF;
    }
  }

  whol[0][0] = 0;
  for (int i = 1; i <= n; i ++) {
    whol[i][0] = 0;
    for (int j = 1; j <= k; j ++) {
      whol[i][j] = whol[i - 1][j];
      whol[i][j] = max(whol[i][j], whol[i - 1][j - 1] + a[i]);
    }
  }
  whor[n + 1][0] = 0;
  for (int i = n; i >= 1; i --) {
    whor[i][0] = 0;
    for (int j = 1; j <= k; j ++) {
      whor[i][j] = whor[i + 1][j];
      whor[i][j] = max(whor[i][j], whor[i + 1][j - 1] + a[i]);
    }
  }
  // ans = *max_element( a + 1 , a + n + 1 );
  // vt = 0;
  go( 1 , n );

  LL check = 0;

  set< pair<int,int> > out , in;

  for( int i = 1 ; i <= n ; i ++ ){
    if( i < ansl or i > ansr )
      out.insert( { a[ i ] , i } );
    else {
      check += a[i];
      in.insert( { a[ i ] , i } );
    }
    while( (int)out.size() > ansc )
      out.erase( out.begin() );
    while( (int)in.size() > ansc )
      in.erase( --in.end() );
  }
  vector<int> O , I;
  for( auto ii : out ) {
    O.push_back( ii.second );
    check += ii.first;
  }
  for( auto ii : in ) {
    I.push_back( ii.second );
    check -= ii.first;
  }
  if( *max_element( a + 1 , a + n + 1 ) < 0 ){
    ans = *max_element( a + 1 , a + n + 1 );
    ansl = ansr = 1;
  }
  printf("%lld\n", ans);
  
  if( ansc == 0 ){
    I.resize( 1 );
    O.resize( 1 );
    if( ansl < ansr ){
      I[ 0 ] = ansl;
      O[ 0 ] = ansr;
    }else{
      I[ 0 ] = 1;
      O[ 0 ] = 2;
    }
    ansc = 1;
  }

  for( int i = 0 ; i < ansc ; i ++ )
    printf( "%d %d\n" , I[ i ] , O[ i ] );

  //printf("%d %d\n", ansl, ansr);
}
