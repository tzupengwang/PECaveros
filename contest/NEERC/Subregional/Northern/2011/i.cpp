// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 18
#define M (1<<18)
int n , m;
int dst[ N ][ N ];
vector<int> rd[ N ][ N ];
void build(){

}
void init(){
  n = getint(); m = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      dst[ i ][ j ] = INF;
      if( i == j ){
        dst[ i ][ j ] = 0;
        rd[ i ][ j ].PB( i );
      }
    }
  while( m -- ){
    int xi = getint() - 1;
    int yi = getint() - 1;
    int di = getint();
    if( di < dst[ xi ][ yi ] ){
      dst[ xi ][ yi ] = di;
      dst[ yi ][ xi ] = di;
      rd[ xi ][ yi ].clear();
      rd[ xi ][ yi ].PB( xi );
      rd[ xi ][ yi ].PB( yi );
      rd[ yi ][ xi ].clear();
      rd[ yi ][ xi ].PB( yi );
      rd[ yi ][ xi ].PB( xi );
    }
  }
  for( int k = 0 ; k < n ; k ++ )
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        if( dst[ i ][ k ] + dst[ k ][ j ] < dst[ i ][ j ] ){
          dst[ i ][ j ] = dst[ i ][ k ] + dst[ k ][ j ];
          rd[ i ][ j ].clear();
          for( size_t u = 0 ; u < rd[ i ][ k ].size() ; u ++ )
            rd[ i ][ j ].PB( rd[ i ][ k ][ u ] );
          for( size_t u = 1 ; u < rd[ k ][ j ].size() ; u ++ )
            rd[ i ][ j ].PB( rd[ k ][ j ][ u ] );
        }
}
int dp[ M ][ N ];
int bk[ M ][ N ];
bool got[ M ][ N ];
int DP( int msk , int lst ){
  if( msk == ( msk & (-msk) ) )
    return lst == 0 ? 0 : INF;
  if( got[ msk ][ lst ] ) return dp[ msk ][ lst ];
  got[ msk ][ lst ] = true;
  int bst = INF , fr = -1;
  for( int i = 0 ; i < n ; i ++ )
    if( ( ( msk >> i ) & 1 ) && i != lst ){
      int nxtmsk = msk ^ ( 1 << lst );
      int tdp = DP( nxtmsk , i ) + dst[ i ][ lst ];
      if( tdp < bst ){
        bst = tdp;
        fr = i;
      }
    }
  bk[ msk ][ lst ] = fr;
  return dp[ msk ][ lst ] = bst;
}
int adp[ M ] , adpf[ M ] , tdp[ M ] , fdp[ M ];
vector<int> pth;
void backt( int msk , int lst ){
  if( msk == 0 ) return;
  int from = bk[ msk ][ lst ];
  // printf( "%d %d %d\n" , msk , lst , from );
  backt( msk ^ ( 1 << lst ) , from );
  for( int i : rd[ from ][ lst ] )
    pth.PB( i );
}
inline void go( int msk ){
  pth.clear();
  backt( msk , adpf[ msk ] );
  int pre = -1;
  vector<int> ans;
  for( int i : pth ){
    if( i == pre ) continue;
    pre = i;
    ans.PB( i + 1 );
  }
  printf( "%d " , (int)ans.size() - 1 );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
void solve(){
  for( int i = 0 ; i < ( 1 << n ) ; i ++ ){
    adp[ i ] = INF;
    for( int j = 0 ; j < n ; j ++ ){
      if( ( i >> j ) & 1 ){
        int tmp = DP( i , j );
        if( tmp < adp[ i ] ){
          adp[ i ] = tmp;
          adpf[ i ] = j;
        }
      }
    }
    tdp[ i ] = adp[ i ];
    fdp[ i ] = i;
  }
  for( int i = ( 1 << n ) - 1 ; i >= 0 ; i -- )
    for( int j = 0 ; j < n ; j ++ )
      if( ( i >> j ) & 1 ){
        if( tdp[ i ] < tdp[ i ^ ( 1 << j ) ] ){
          tdp[ i ^ ( 1 << j ) ] = tdp[ i ];
          fdp[ i ^ ( 1 << j ) ] = fdp[ i ];
        }
      }
  int ans = INF , bsta = 0 , bstb = 0;
  for( int i = 1 ; i < ( 1 << n ) ; i ++ ){
    if( i % 2 == 0 ) continue;
    int tans = max( adp[ i ] , tdp[ ( ( ( 1 << n ) - 1 ) ^ i ) | 1 ] );
    if( tans < ans ){
      ans = tans;
      bsta = i;
      bstb = fdp[ ( ( ( 1 << n ) - 1 ) ^ i ) | 1 ];
    }
  }
  printf( "%d\n" , ans );
  go( bsta );
  go( bstb );
}
int main(){
  freopen( "immediate.in" , "r" , stdin );
  freopen( "immediate.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
