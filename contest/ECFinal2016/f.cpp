#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 303030;
struct SA{
#define REP(i,n) for(int i=0;i < int(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=int(b);i++)
  bool _t[N*2];
  int _s[N*2], _sa[N*2], _c[N*2], x[N], _p[N], _q[N*2], hei[N], r[N];
  void build(int *s, int n, int m){
    memcpy(_s, s, sizeof(int) * n);
    sais(_s, _sa, _p, _q, _t, _c, n, m);
    mkhei(n);
  }
  void mkhei(int n){
    REP(i,n) r[_sa[i]] = i;
    hei[0] = 0;
    REP(i,n) if(r[i]){
      int ans = i>0 ? max(hei[r[i-1]] - 1, 0) : 0;
      while(_s[i+ans] == _s[_sa[r[i] - 1] + ans]) ans ++;
      hei[r[i]] = ans;
    }
  }
  void sais(int *s, int *sa, int *p, int *q, bool *t, int *c , int n , int z){
    bool uniq = t[n-1] = true, neq;
    int nn = 0, nmxz = -1 , *nsa = sa + n , *ns = s + n , lst = -1;
#define MS0(x,n) memset((x),0,n*sizeof(*(x)))
#define MAGIC(XD) MS0(sa, n); \
    memcpy(x, c, sizeof(int) * z); \
    XD; \
    memcpy(x + 1, c, sizeof(int) * (z-1)); \
    REP(i,n) if(sa[i] and !t[sa[i]-1]) sa[x[s[sa[i]-1]]++] = sa[i]-1; \
    memcpy(x, c, sizeof(int) * z); \
    for(int i = n - 1; i >= 0; i --) if(sa[i] and t[sa[i]-1]) sa[--x[s[sa[i]-1]]] = sa[i]-1;
    MS0(c, z);
    REP(i, n) uniq &= ++ c[s[i]] < 2;
    REP(i, z-1) c[i+1] += c[i];
    if(uniq){ REP(i,n) sa[--c[s[i]]] = i; return; }
    for(int i = n - 2 ; i >= 0 ; i -- ) t[i] = (s[i] == s[i+1] ? t[i+1] : s[i] < s[i+1]);
    MAGIC(REP1(i,1,n-1) if(t[i] and !t[i-1]) sa[--x[s[i]]]=p[q[i]=nn++]=i);
    REP(i,n) if(sa[i] and t[sa[i]] and !t[sa[i]-1]) {
      neq=lst<0||memcmp(s+sa[i],s+lst,(p[q[sa[i]]+1]-sa[i])*sizeof(int));
      ns[q[lst=sa[i]]]=nmxz+=neq;
    }
    sais(ns, nsa, p + nn, q + n , t + n , c + z , nn , nmxz + 1);
    MAGIC(for(int i=nn-1;i>=0;i--) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
  }
} sa;
int H[ N ] , SA[ N ];
void suffix_array( int* ip , int len ){
  ip[len ++] = 0;
  sa.build(ip, len, 128);
  for( int i = 0 ; i < len ; i ++ ){
    H[i] = sa.hei[i + 1];
    SA[i] = sa._sa[i + 1];
  }
}
int n , len[ N ] , st[ N ] , ptr;
char cc[ N ];
int ip[ N ];
void init(){
  scanf( "%d" , &n );
  ptr = 0;
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , cc + ptr );
    st[ i ] = ptr;
    len[ i ] = strlen( cc + ptr );
    for( int j = 0 ; j < len[i] ; j ++ )
      ip[ ptr + j ] = cc[ ptr + j ] - 'a' + 1;
    if( i == 0 ) ip[ ptr + len[i] ] = 27;
    else ip[ ptr + len[i] ] = 28;
    ptr += len[ i ] + 1;
  }
  suffix_array( ip , ptr );
}
int _sum[ N ] , *sum;
#define lgN 19
int h[ lgN ][ N ];
int hh( int lb , int rb ){
  int bt = __lg( rb - lb + 1 );
  return min( h[ bt ][ lb ] ,
              h[ bt ][ rb - (1 << bt) + 1 ] );
}
int _cs;
void solve(){
  for( int i = 0 ; i < ptr ; i ++ )
    h[ 0 ][ i ] = H[ i ];
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 0 ; i + (1 << j) - 1 < ptr ; i ++ )
      h[ j ][ i ] = min( h[ j - 1 ][ i ] ,
                         h[ j - 1 ][ i + (1 << (j - 1)) ] );
  for( int i = 0 ; i < ptr ; i ++ )
    sum[ i ] = sum[ i - 1 ] + (SA[ i ] >= len[ 0 ]);
  int as = -1 , alen = len[ 0 ] + 1;
  for( int _ = 0 ; _ < ptr ; _ ++ ){
    int i = SA[ _ ];
    if( i >= len[ 0 ] ) continue;
    int cl = 1 , cr = min( alen - 1 , len[ 0 ] - i ) , ca = alen;
    while( cl <= cr ){
      int cmid = (cl + cr) >> 1;
      int lft , rgt;
      {
        int bl =  0 , br = _ - 1; lft = _;
        while( bl <= br ){
          int bmid = (bl + br) >> 1;
          if( hh( bmid + 1 , _ ) >= cmid )
            lft = bmid , br = bmid - 1;
          else
            bl = bmid + 1;
        }
      }
      {
        int bl = _ + 1 , br = ptr - 1; rgt = _;
        while( bl <= br ){
          int bmid = (bl + br) >> 1;
          if( hh( _ + 1 , bmid ) >= cmid )
            rgt = bmid , bl = bmid + 1;
          else
            br = bmid - 1;
        }
      }
      if( sum[ rgt ] - sum[ lft - 1 ] == 0 )
        ca = cmid , cr = cmid - 1;
      else
        cl = cmid + 1;
    }
    if( ca >= alen ) continue;
    as = i;
    alen = ca;
  }
  printf( "Case #%d: " , ++ _cs );
  if( as == -1 ) puts( "Impossible" );
  else{
    for( int i = 0 ; i < alen ; i ++ )
      putchar( cc[ as + i ] );
    puts( "" );
  }
}
int main(){
  sum = _sum + 1;
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
