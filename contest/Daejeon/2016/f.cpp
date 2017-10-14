#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
#define N 101010
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
typedef long long LL;
struct Line{
  LL m , b;
  int id;
};
// m1x + b1 = m2x + b2
// (m2-m1)x = b1 - b2
inline bool better( const Line& l1 , const Line& l2 , const Line& l3 ){
  return (l1.b - l3.b) * (l2.m - l1.m) <=
         (l1.b - l2.b) * (l3.m - l1.m);
}
struct SegT{
  int n;
  deque<Line> st[ N << 2 ];
  void init( int no , int l , int r ){
    st[ no ].clear();
    if( l == r ) return;
    init( L( no ) , l , mid );
    init( R( no ) , mid + 1 , r );
  }
  void init( int _n ){
    n = _n;
    init( 1 , 1 , n );
  }
  void add( deque<Line>& cur , int nm , int nb , int id ){
    Line newl = { nm , nb , id };
    while( cur.size() > 1u and
           better( cur[ (int)cur.size() - 2 ] ,
                   cur[ (int)cur.size() - 1 ] ,
                   newl ) )
      cur.pop_back();
    cur.push_back( newl );
  }
  void modify( int no , int l , int r , int p , int nm , int nb , int id ){
    add( st[ no ] , nm , nb , id );
    if( l == r ) return;
    if( p <= mid )
      modify( L( no ) , l , mid , p , nm , nb , id );
    else
      modify( R( no ) , mid + 1 , r , p , nm , nb , id );
  }
  void modify( int p , int nm , int nb , int id ){
    modify( 1 , 1 , n , p , nm , nb , id );
  }
  pair<double,int> query( int no , int l , int r , int ql , int qr , double qx ){
    if( st[ no ].empty() or r < ql or l > qr ) return { -1 , -1 };
    if( ql <= l and r <= qr ){
      deque<Line>& cur = st[ no ];
      while( cur.size() > 1u ){
        if( ( cur[ 0 ].b - cur[ 1 ].b ) < qx * ( cur[ 1 ].m - cur[ 0 ].m ) )
          cur.pop_front();
        else
          break;
      }
      double vl = qx * cur[ 0 ].m + cur[ 0 ].b;
      return { vl , cur[ 0 ].id };
    }
    pair<double,int> retl = query( L( no ) , l , mid , ql , qr , qx );
    pair<double,int> retr = query( R( no ) , mid + 1 , r , ql , qr , qx );
    if( retl.second == -1 ) return retr;
    if( retr.second == -1 ) return retl;
    return max( retl , retr );
  }
  int query( double qx , double qy , int ql ){
    int bl = ql , br = n , ba = -1;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      pair<double,int> ret = query( 1 , 1 , n , ql , bmid , qx );
      if( ret.first > qy - eps )
        ba = ret.second , br = bmid - 1;
      else
        bl = bmid + 1;
    }
    return ba;
  }
} seg;

int X;
int n, q;
int x[2][N], h[N];
int qx[N], qy[N], dx[N], dy[N];
int ord[N];
int ans[N];
int line_id[N];

void do_dx0() {
  for (int i = 1; i <= q; ++i) if (dx[i] == 0) {
    int id = lower_bound(x[1]+1, x[1]+1+n, qx[i]) - x[1];
    if (id <= n and x[0][id] <= qx[i]) {
      ans[i] = id;
    }
  }
}

double m[N];

void calc(int i) {
  double C = m[i] * qx[i] + qy[i];
  int lb = lower_bound(x[1]+1, x[1]+1+n, qx[i]) - x[1];

  int res = seg.query(m[i], C, lb);
  if (res != -1) ans[i] = res;
}

void gogo() {
  seg.init(n);
  for (int i = 1; i <= n; ++i) {
    seg.modify(i, x[1][i], h[i], line_id[i]);
  }

  for (int i = 1; i <= q; ++i) {
    m[i] = -1;
    if (dx[i] > 0) {
      m[i] = -1.0 * dy[i] / dx[i];
    }
  }

  sort(ord+1, ord+1+q, [&](int a, int b){return m[a] < m[b];});

  for (int i = 1; i <= q; ++i) if (dx[ord[i]] > 0) {
    calc(ord[i]);
  }
}

void solve() {
  fill(ans, ans+q+1, 0);
  for (int i = 1; i <= n; ++i) line_id[i] = i;
  for (int i = 1; i <= q; ++i) ord[i] = i;

  do_dx0();

  gogo();
  
  X = *max_element(qx+1, qx+1+n);
  X = max(X, x[1][n]);

  for (int i = 1; i <= n; ++i) {
    x[1][i] = X - x[1][i];
    x[0][i] = X - x[0][i];
    swap(x[1][i], x[0][i]);
  }
  reverse(x[0]+1, x[0]+1+n);
  reverse(x[1]+1, x[1]+1+n);
  reverse(h+1, h+1+n);
  reverse(line_id+1, line_id+1+n);

  for (int i = 1; i <= q; ++i) {
    qx[i] = X - qx[i];
    dx[i] = -dx[i];
  }

  gogo();

  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}

int main(){
  while (scanf("%d", &n) != EOF) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d%d", x[0]+i, x[1]+i, h+i);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d%d%d%d", qx+i, qy+i, dx+i, dy+i);
    }
    solve();
  }
}
