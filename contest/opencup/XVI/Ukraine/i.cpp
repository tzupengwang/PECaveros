#include <bits/stdc++.h>
using namespace std;
const int N = 101010;
struct SA{
#define REP(i,n) for ( int i=0; i<int(n); i++ )
#define REP1(i,a,b) for ( int i=(a); i<=int(b); i++ )
  bool _t[N*2];
  int _s[N*2], _sa[N*2], _c[N*2], x[N], _p[N], _q[N*2], hei[N], r[N];
  int operator [] (int i){ return _sa[i]; }
  void build(int *s, int n, int m){
    memcpy(_s, s, sizeof(int) * n);
    sais(_s, _sa, _p, _q, _t, _c, n, m);
    mkhei(n);
  }
  void mkhei(int n){
    REP(i,n) r[_sa[i]] = i;
    hei[0] = 0;
    REP(i,n) if(r[i]) {
      int ans = i>0 ? max(hei[r[i-1]] - 1, 0) : 0;
      while(_s[i+ans] == _s[_sa[r[i]-1]+ans]) ans++;
      hei[r[i]] = ans;
    }
  }
  void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z){
    bool uniq = t[n-1] = true, neq;
    int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, lst = -1;
#define MS0(x,n) memset((x),0,n*sizeof(*(x)))
#define MAGIC(XD) MS0(sa, n); \
    memcpy(x, c, sizeof(int) * z); \
    XD; \
    memcpy(x + 1, c, sizeof(int) * (z - 1)); \
    REP(i,n) if(sa[i] && !t[sa[i]-1]) sa[x[s[sa[i]-1]]++] = sa[i]-1; \
    memcpy(x, c, sizeof(int) * z); \
    for(int i = n - 1; i >= 0; i--) if(sa[i] && t[sa[i]-1]) sa[--x[s[sa[i]-1]]] = sa[i]-1;
    MS0(c, z);
    REP(i,n) uniq &= ++c[s[i]] < 2;
    REP(i,z-1) c[i+1] += c[i];
    if (uniq) { REP(i,n) sa[--c[s[i]]] = i; return; }
    for(int i = n - 2; i >= 0; i--) t[i] = (s[i]==s[i+1] ? t[i+1] : s[i]<s[i+1]);
    MAGIC(REP1(i,1,n-1) if(t[i] && !t[i-1]) sa[--x[s[i]]]=p[q[i]=nn++]=i);
    REP(i, n) if (sa[i] && t[sa[i]] && !t[sa[i]-1]) {
      neq=lst<0||memcmp(s+sa[i],s+lst,(p[q[sa[i]]+1]-sa[i])*sizeof(int));
      ns[q[lst=sa[i]]]=nmxz+=neq;
    }
    sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
    MAGIC(for(int i = nn - 1; i >= 0; i--) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
  }
}sa;
int H[ N ], SA[ N ];
void suffix_array(int* ip, int len) {
  // should padding a zero in the back
  // ip is int array, len is array length
  // ip[0..n-1] != 0, and ip[len] = 0
  ip[len++] = 0;
  sa.build(ip, len, 128);
  for (int i=0; i<len; i++) {
    H[i] = sa.hei[i + 1];
    SA[i] = sa._sa[i + 1];
  }
  // resulting height, sa array \in [0,len)
}
struct SegT{
  SegT *tl , *tr;
  int sum;
  SegT(){
    tl = tr = NULL;
    sum = 0;
  }
};
SegT* root[ N ];
#define mid ((l+r)>>1)
int Sum( SegT* now ){
  return now ? now->sum : 0;
}
void modify_seg( SegT* now , int l , int r , int p , int dlt ){
  if( l == r ){
    now->sum = dlt;
    return;
  }
  if( p <= mid ){
    if( !now->tl ) now->tl = new SegT();
    modify( now->tl , l , mid , p , dlt );
  }else{
    if( !now->tr ) now->tr = new SegT();
    modify( now->tr , mid + 1 , p , dlt );
  }
  now->sum = Sum( now->tl ) + Sum( now->tr );
}
int query_seg( SegT* now , int l , int r , int nd ){
  if( Sum( now ) < nd ) return -1;
  if( l == r ) return l;
  if( Sum( now->tl ) >= nd )
    return query( now->tl , l , mid , nd );
  return query( now->tr , mid + 1 , r , nd - Sum( now->tl ) );
}
int BIT[ N ];
int lb( int x ){ return x & (-x); }
void modify_bit( int x , int v ){
  ++ x;
  for( int i = x ; i < N ; i += lb( i ) )
    BIT[ i ] += v;
}
int query_bit( int x ){
  ++ x;
  int ret = 0;
  for( int i = x ; i ; i -= lb( i ) )
    ret += BIT[ i ];
  return ret;
}
char c[ N ];
int cc[ N ] , len;
#define K 20
int rmq[ N ][ K ];
int at[ N ];
void init(){
  scanf( "%s" , c );
  len = strlen( c );
  for( int i = 0 ; i < len ; i ++ )
    cc[ i ] = c[ i ] - 'a' + 1;
  suffix_array( cc , len );
  for( int i = 0 ; i < len ; i ++ ){
    rmq[ i ][ 0 ] = H[ i ];
    at[ SA[ i ] ] = i;
    root[ i ] = new SegT();
  }
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 0 ; i + ( 1 << j ) <= len ; i ++ )
      rmq[ i ][ j ] = min( rmq[ i ][ j - 1 ] ,
                           rmq[ i + ( 1 << ( j - 1 ) ) ][ j - 1 ] );
}
void solve(){
  int q; scanf( "%d" , &q ); while( q -- ){
    int cmd , x , p; scanf( "%d%d%d" , &cmd , &x , &p );
    int find_pos( x , p );
    if( cmd == 1 ){

    }
  }
}
int main(){
  init();
  solve();
}
