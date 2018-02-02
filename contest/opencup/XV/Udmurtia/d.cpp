#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int V = 1010;

struct SCC {
  int n;
  vector<int> g[V], rg[V], vs;
  bool vis[V];
  int mk[V], m;
  void init(int _n) {
    n = _n;
    vs.clear();
    for (int i = 1; i <= n; ++i) {
      g[i].clear();
      rg[i].clear();
      vis[i] = 0;
      mk[i] = 0;
    }
  }
  void add_e(int u, int v) {
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  void dfs(int u) {
    vis[u] = 1;
    for (int v: g[u]) if (!vis[v]) dfs(v);
    vs.push_back(u);
  }
  void rdfs(int u, int i) {
    mk[u] = i;
    vis[u] = 1;
    for (int v: rg[u]) if (!vis[v]) rdfs(v, i);
  }
  void scc() {
    fill(vis, vis+1+n, 0);
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
    fill(vis, vis+1+n, 0);
    reverse(vs.begin(), vs.end());
    m = 0;
    for (int u: vs) if (!vis[u]) rdfs(u, ++m);
  }
};

struct SAT2 {
  int n;
  SCC g;
  bool val[V];
  void init(int _n) {
    n = _n;
    g.init(n*2);
  }
  int nt(int u) {
    if (u > n) return u-n;
    return u+n;
  }
  void imp(int a, int b) {
    g.add_e(a, b);
  }
  void solve() {
    g.scc();
    for (int i = 1; i <= n; ++i)
      val[i] = g.mk[i] > g.mk[nt(i)];
  }
} sat2;


#define N 514
#define M 10101
int n , m , c[ N ] , r[ N ];
int x[ M ] , y[ M ] , t[ M ];
bool nok[ N * 2 ][ N * 2 ];
set<int> lft[ N ] , rgt[ N ] , up[ N ] , dn[ N ];
bool collision( const set<int>& s1 , const set<int>& s2 , int tot ){
  for( auto i : s1 )
    if( s2.upper_bound( i - tot + 1 ) != s2.lower_bound( i + tot ) )
      return true;
  for( auto i : s2 )
    if( s1.upper_bound( i - tot + 1 ) != s1.lower_bound( i + tot ) )
      return true;
  return false;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &r[ i ] );
    //scanf( "%d" , &c[ i ] );
    //r[ c[ i ] ] = i;
    c[ r[ i ] ] = i;
  }
  scanf( "%d" , &m );
  for( int i = 0 ; i < m ; i ++ ){
    //scanf( "%d%d%d" , &x[ i ] , &y[ i ] , &t[ i ] );
    int xi , yi , ti;
    scanf( "%d%d%d" , &xi , &yi , &ti );
    x[ i ] = yi;
    y[ i ] = xi;
    t[ i ] = ti;

    if( x[ i ] == 0     ) lft[ y[ i ] ].insert( t[ i ] );
    if( x[ i ] == n + 1 ) rgt[ y[ i ] ].insert( t[ i ] );
    if( y[ i ] == 0     ) up[ x[ i ] ].insert( t[ i ] );
    if( y[ i ] == n + 1 ) dn[ x[ i ] ].insert( t[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    if( collision( lft[ c[ i ] ] , dn[ i ] , i + n + 1 - c[ i ] ) or
        collision( rgt[ c[ i ] ] , up[ i ] , n + 1 - i + c[ i ] ) ){
      //printf( "%d 0 gg\n" , i );
      nok[ i * 2     ][ i * 2     ] = true;
    }
    if( collision( lft[ c[ i ] ] , up[ i ] , i + c[ i ] ) or
        collision( rgt[ c[ i ] ] , dn[ i ] , n + 1 - i + n + 1 - c[ i ] ) ){
      nok[ i * 2 + 1 ][ i * 2 + 1 ] = true;
      //printf( "%d 1 gg\n" , i );
    }
  }
}



int who[ 2 ][ N ][ N ][ 4 ];
int wc[ 2 ][ N ][ N ];
int tg[ 2 ][ N ][ N ];
int que[ 2 ][ M * 2 ] , qsz[ 2 ] , stmp = -1;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
inline int encode( int mr , int mr_dr , int dir ){
  return (mr << 3) | (mr_dr << 2) | dir;
}
int now , pre;


bool collide( int nx , int ny , int me , int he ){
  if( c[ nx ] != ny ) return true;
  if( ((me >> 2) & 1) == ((he >> 2) & 1) ){
    if( ((me >> 2) & 1) == 0 ){
      return ( (me & 3) == 2 or (me & 3) == 1 ) ==
             ( (he & 3) == 2 or (he & 3) == 1 );
    }else{
      return ( (me & 3) == 2 or (me & 3) == 0 ) ==
             ( (he & 3) == 2 or (he & 3) == 0 );
    }
  }
  return false;
}

void add( int nx , int ny , int me , int ddd = 0 ){
  if( tg[ now ][ nx ][ ny ] != stmp ){
    tg[ now ][ nx ][ ny ] = stmp;
    wc[ now ][ nx ][ ny ] = 0;
    que[ now ][ qsz[ now ] ++ ] = nx * N + ny;
  }
  for( int i = 0 ; i < wc[ now ][ nx ][ ny ] - ddd ; i ++ ){
    if( not collide( nx , ny , me , who[ now ][ nx ][ ny ][ i ] ) )
      continue;
    nok[ who[ now ][ nx ][ ny ][ i ] >> 2 ][ me >> 2 ] = true;
    nok[ me >> 2 ][ who[ now ][ nx ][ ny ][ i ] >> 2 ] = true;
    //if( (me >> 2) == 7 and 
        //(who[ now ][ nx ][ ny ][ i ] >> 2 ) == 7 ){
      //printf( "%d %d\n" , nx , ny );
    //}
    if( (me >> 2) == 0 ){
      nok[ who[ now ][ nx ][ ny ][ i ] >> 2 ][ who[ now ][ nx ][ ny ][ i ] >> 2 ] = true;
    }
    if( (who[ now ][ nx ][ ny ][ i ] >> 2 ) == 0 ){
      nok[ me >> 2 ][ me >> 2 ] = true;
    }
  }
  who[ now ][ nx ][ ny ][ wc[ now ][ nx ][ ny ] ++ ] = me;
}
bool in( int nx , int ny ){
  return 1 <= nx and nx <= n and
         1 <= ny and ny <= n;
}
int rotate( int mr_dr , int in_dir ){
  if( mr_dr == 0 ){
    if( in_dir == 0 ) return 2;
    if( in_dir == 2 ) return 0;
    if( in_dir == 1 ) return 3;
    if( in_dir == 3 ) return 1;
  }else{
    if( in_dir == 0 ) return 3;
    if( in_dir == 3 ) return 0;
    if( in_dir == 1 ) return 2;
    if( in_dir == 2 ) return 1;
  }
  assert( false );
  return -1;
}
void simulate(){
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      for( int k = 0 ; k < N ; k ++ )
        tg[ i ][ j ][ k ] = -1;
  int ptr = 0;
  now = 0 , pre = 1;
  while( ptr < m or qsz[ pre ] ){
    now ^= 1; pre ^= 1;
    qsz[ now ] = 0;
    if( qsz[ pre ] == 0 )
      stmp = t[ ptr ];
    else
      stmp ++;
    while( ptr < m ){
      if( t[ ptr ] > stmp ) break;
      //que[ qsz[ now ] ] = 
      if( y[ ptr ] == 0 )
        add( x[ ptr ] , y[ ptr ] , 0 );
      if( y[ ptr ] == n + 1 )
        add( x[ ptr ] , y[ ptr ] , 1 );
      if( x[ ptr ] == 0 )
        add( x[ ptr ] , y[ ptr ] , 2 );
      if( x[ ptr ] == n + 1 )
        add( x[ ptr ] , y[ ptr ] , 3 );
      ptr ++;
    }
    for( int i = 0 ; i < qsz[ pre ] ; i ++ ){
      int cx = que[ pre ][ i ] / N;
      int cy = que[ pre ][ i ] % N;
      for( int ii = 0 ; ii < wc[ pre ][ cx ][ cy ] ; ii ++ ){
        int cur = who[ pre ][ cx ][ cy ][ ii ];
        int ddir = cur & 3;
        int nxtx = cx + dx[ ddir ];
        int nxty = cy + dy[ ddir ];
        if( not in( nxtx , nxty ) ) continue;
        if( c[ nxtx ] == nxty ){
          for( int mr_d = 0 ; mr_d < 2 ; mr_d ++ ){
            int nxtd = rotate( mr_d , ddir );
            add( nxtx , nxty , encode( nxtx , mr_d , nxtd ) , mr_d );
          }
        }else{
          add( nxtx , nxty , cur );
        }
      }
    }
  }
}

char cca[ N ];

void solve(){
  simulate();
  sat2.init(n);
  //for (int i = 1; i <= n; ++i) {
    //for (int j = i; j <= n; ++j) {
      //printf("%d %d %d %d %d %d\n", i, j, nok[i*2][j*2], nok[i*2][j*2+1], nok[i*2+1][j*2], nok[i*2+1][j*2+1]);
    //}
  //}
  for (int i = 1; i <= n; ++i) {
    if (nok[i*2][i*2]) {
      sat2.imp(i, sat2.nt(i));
    }
    if (nok[i*2+1][i*2+1]) {
      sat2.imp(sat2.nt(i), i);
    }
    for (int j = 1; j <= n; ++j) if (i!=j) {
      if (nok[i*2][j*2]) {
        sat2.imp(i, sat2.nt(j));
        sat2.imp(j, sat2.nt(i));
      }
      if (nok[i*2][j*2+1]) {
        sat2.imp(i, j);
        sat2.imp(sat2.nt(j), sat2.nt(i));
      }
      if (nok[i*2+1][j*2]) {
        sat2.imp(sat2.nt(i), sat2.nt(j));
        sat2.imp(j, i);
      }
      if (nok[i*2+1][j*2+1]) {
        sat2.imp(sat2.nt(i), j);
        sat2.imp(sat2.nt(j), i);
      }
    }
  }
  sat2.solve();
  for (int i = 1; i <= n; ++i)
    //putchar("01"[sat2.val[i]]);
    cca[c[i]] = "10"[sat2.val[i]];
  //puts("");
  puts( cca + 1 );
}
int main(){
  init();
  solve();
}
