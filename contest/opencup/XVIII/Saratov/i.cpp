#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 404040
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
} sa;
struct SegT{
  int who[ (1 << 20) ] , tg[ (1 << 20) ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
  void reset( int no , int l , int r ){
    who[ no ] = tg[ no ] = -1;
    if( l == r ) return;
    reset( L( no ) , l , mid );
    reset( R( no ) , mid + 1 , r );
  }
  void push( int no , int l , int r ){
    if( tg[ no ] == -1 ) return;
    tg[ L( no ) ] = who[ L( no ) ] = tg[ no ];
    tg[ R( no ) ] = who[ R( no ) ] = tg[ no ];
    tg[ no ] = -1;
  }
  void modify( int no , int l , int r , int ql , int qr , int vl ){
    if( r < ql or l > qr ) return;
    if( ql <= l and r <= qr ){
      tg[ no ] = who[ no ] = vl;
      return;
    }
    push( no , l , r );
    modify( L( no ) , l , mid , ql , qr , vl );
    modify( R( no ) , mid + 1 , r , ql , qr , vl );
  }
  int query( int no , int l , int r , int p ){
    if( l == r ) return who[ no ];
    push( no , l , r );
    if( p <= mid ) return query( L( no ) , l , mid , p );
    return query( R( no ) , mid + 1 , r , p );
  }
} segT;
int H[ N ], SA[ N ] , RA[ N ];
void suffix_array(int* ip, int len) {
  // should padding a zero in the back
  // ip is int array, len is array length
  // ip[0..n-1] != 0, and ip[len] = 0
  ip[len++] = 0;
  sa.build(ip, len, 128);
  for (int i=0; i<len; i++) {
    H[i + 1] = sa.hei[i + 1];
    SA[i + 1] = sa._sa[i + 1] + 1;
  }
  // resulting height, sa array \in [0,len)
}
#define K 19
int n , q , cc[ N ] , rmq[ K ][ N ];
char c[ N ];
int rmq_query( int lb , int rb ){
  int bt = __lg( rb - lb + 1 );
  return min( rmq[ bt ][ lb ],
              rmq[ bt ][ rb - (1 << bt) + 1 ] );
}
void init(){
  scanf( "%d%d" , &n , &q );
  scanf( "%s" , c + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    cc[ i ] = c[ i ] - 'a' + 1;
  suffix_array( cc + 1 , n );
  for( int i = 1 ; i <= n ; i ++ ){
    RA[ SA[ i ] ] = i;
    rmq[ 0 ][ i ] = H[ i ];
  }
  //for( int i = 1 ; i <= n ; i ++ )
    //printf( "%d SA=%d , RA = %d , H = %d\n" , i , SA[ i ] , RA[ i ] , H[ i ] );
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      rmq[ j ][ i ] = min( rmq[ j - 1 ][ i ] ,
                           rmq[ j - 1 ][ i + (1 << (j - 1)) ] );
}
int k , mod , l[ N ] , r[ N ] , ord[ N ];
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
bool cmp( int id1 , int id2 ){
  return r[ id1 ] - l[ id1 ] <
         r[ id2 ] - l[ id2 ];
}
vector<int> son[ N ];
int DP( int now ){
  int ret = 1;
  for( int ss : son[ now ] )
    ret = mul( ret , DP( ss ) );
  ret = add( ret , 1 );
  return ret;
}
void go(){
  segT.modify( 1 , 1 , n , 1 , n , 0 );
  for( int i = 0 ; i < k ; i ++ )
    ord[ i ] = i;
  sort( ord , ord + k , cmp );
  for( int i = 0 ; i <= k ; i ++ )
    son[ i ].clear();
  for( int _ = 0 ; _ < k ; _ ++ ){
    int i = ord[ _ ];
    int at = RA[ l[ i ] ];
    int len = r[ i ] - l[ i ] + 1;
    int fr , til;
    {
      int lb = at + 1 , rb = n , ba = at;
      while( lb <= rb ){
        int bmid = (lb + rb) >> 1;
        if( rmq_query( at + 1 , bmid ) >= len )
          ba = bmid , lb = bmid + 1;
        else
          rb = bmid - 1;
      }
      til = ba;
    }
    {
      int lb = 1 , rb = at - 1 , ba = at;
      while( lb <= rb ){
        int bmid = (lb + rb) >> 1;
        if( rmq_query( bmid + 1 , at ) >= len )
          ba = bmid , rb = bmid - 1;
        else
          lb = bmid + 1;
      }
      fr = ba;
    }
    int prt = segT.query( 1 , 1 , n , at );
    son[ prt ].push_back( i + 1 );
    //printf( "%d -> %d\n" , prt , i + 1 );

    segT.modify( 1 , 1 , n , fr , til , i + 1 );
  }
  printf( "%d\n" , sub( DP( 0 ) , 1 ) );
}
void solve(){
  segT.reset( 1 , 1 , n );
  while( q -- ){
    scanf( "%d%d" , &k , &mod );
    for( int i = 0 ; i < k ; i ++ )
      scanf( "%d%d" , &l[ i ] , &r[ i ] );
    go();
  }
}
int main(){
  init();
  solve();
}
