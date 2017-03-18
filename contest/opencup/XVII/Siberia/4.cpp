#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 1e5+10;

LL A , B;
int n;
PII in[ MAXN ];

int mom[ MAXN ] , mx[ MAXN ];
int find( int x ) {
  if ( x == mom[ x ] ) return x;
  return mom[ x ] = find( mom[ x ] );
}
void merge( int a , int b ) {
  a = find( a );
  b = find( b );
  mom[ b ] = a;
  mx[ a ] = max( mx[ a ] , mx[ b ] );
}

vector<int> grp[ MAXN ];

void input() {
  cin >> A >> B >> n;
  for ( int i = 1 ; i <= n ; i++ )
    cin >> in[ i ].X;
  for ( int i = 1 ; i <= n ; i++ )
    cin >> in[ i ].Y;
  sort( in+1 , in+n+1 );
}

void predo() {
  for ( int i = 1 ; i <= n ; i++ ) mom[ i ] = i , mx[ i ] = in[ i ].Y;
  set<PII> st;
  for ( int i = 1 ; i <= n ; i++ ) {
    while ( !st.empty() ) {
      auto it = st.begin();
      if ( -it->X < in[ i ].Y ) break;
      merge( i , it->Y );
      st.erase( it );
    }
    int p = find( i );
    st.insert( { -mx[ p ] , p } );
  }
  for ( int i = 1 ; i <= n ; i ++ )
    grp[ find( i ) ].push_back( i );
}

inline bool chk( int id ) {
  vector<int> &gp = grp[ id ];
  sort( gp.begin() , gp.end() );
  int ed1 = -1 , ed2 = -1;
  for ( int i : gp ) {
    if ( in[ i ].Y > ed1 ) ed1 = in[ i ].Y;
    else if ( in[ i ].Y > ed2 ) ed2 = in[ i ].Y;
    else return 0;
  }
  return 1;
}

inline double cal1( int i ) {
  double res = 0 , tmp = in[i].X-in[i].Y;
  res = B*B + tmp*tmp;
  return sqrt( res );
}

inline double cal2( int i ) {
  double r1 = in[i].X+in[i].Y;
  double r2 = A+A-r1;
  return B+min(r1, r2);
}

inline double go( int id ) {
  vector<int> &gp = grp[ id ];
  vector<int> v1 , v2;
  double res1 = 0 , res2 = 0;
  int ed1 = -1 , ed2 = -1;
  for ( int i : gp ) {
    if ( in[ i ].Y > ed1 ) ed1 = in[ i ].Y , v1.push_back( i );
    else if ( in[ i ].Y > ed2 ) ed2 = in[ i ].Y , v2.push_back( i );
  }
  for ( int i : v1 ) {
    res1 += cal1( i );
    res2 += cal2( i );
  }
  for ( int i : v2 ) {
    res1 += cal2( i );
    res2 += cal1( i );
  }
  return min( res1 , res2 );
}

void solve() {
  double res = 0;
  for ( int i = 1 ; i <= n ; i ++ ) {
    if ( !chk( i ) ) {
      cout << -1 << endl;
      return;
    }
    res += go( i );
  }
  printf("%.12f\n",res);
}

int main() {
  ios_base::sync_with_stdio( 0 );
  cin.tie( 0 );
  input();
  predo();
  solve();
}
