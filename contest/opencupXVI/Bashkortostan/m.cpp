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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
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
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 11
#define M 1048576
int bt[ M ] , n , a , b , q;
inline int bit( int msk , int pos ){
  return ( msk >> ( ( n - pos - 1 ) * 2 ) ) & 3;
}
vector<int> st;
// 0 pre0 , 1 , 2 post0
vector<int> nxt[ M ];
void build(){
  for( int i = 1 ; i < M ; i ++ )
    bt[ i ] = bt[ i / 2 ] + i % 2;
}
void DFS2( int pre , int now , int msk , int cnt ){
  if( now == n ){
    if( cnt >= a && cnt <= b )
      nxt[ pre ].PB( msk );
    return;
  }
  int nb = bit( pre , now );
  if( nb == 2 ) DFS2( pre , now + 1 , msk * 4 + 2 , cnt );
  else if( nb == 1 ){
    DFS2( pre , now + 1 , msk * 4 + 2 , cnt );
    DFS2( pre , now + 1 , msk * 4 + 1 , cnt + 1 );
  }else{
    DFS2( pre , now + 1 , msk * 4 + 0 , cnt );
    DFS2( pre , now + 1 , msk * 4 + 1 , cnt + 1 );
  }
}
void DFS( int now , int pre , int cnt , bool flag ){
  if( now == n ){
    if( cnt >= a && cnt <= b ){
      if( !flag ) st.PB( pre );
      DFS2( pre , 0 , 0 , 0 );
      // for( int m = 0 ; m < ( 1 << n ) ; m ++ ){
        // if( bt[ m ] < a || bt[ m ] > b ) continue;
        // int nxtmsk = 0; bool okay = true;
        // for( int i = 0 ; i < n ; i ++ ){
          // int nbt = bit( pre , i );
          // if( nbt == 2 && ( ( m >> ( n - i - 1 ) ) & 1 ) ){
            // okay = false; break;
          // }
          // if( nbt == 2 ) nxtmsk = nxtmsk * 4 + 2;
          // else if( ( m >> ( n - i - 1 ) ) & 1 ){
            // nxtmsk = nxtmsk * 4 + 1;
          // }else{
            // if( nbt == 0 ) nxtmsk = nxtmsk * 4;
            // else nxtmsk = nxtmsk * 4 + 2;
          // }
        // }
        // if( okay ) nxt[ pre ].PB( nxtmsk );
      // }
    }
    return;
  }
  for( int i = 0 ; i < 3 ; i ++ )
    DFS( now + 1 , pre * 4 + i , cnt + ( i == 1 ) , flag | ( i == 2 ) );
}
void init(){
  n = getint();
  a = getint();
  b = getint();
  q = getint();
  DFS( 0 , 0 , 0 , false );
}
ll dp[ N ][ M ];
bool got[ N ][ M ];
ll DP( int now , int msk ){
  if( got[ now ][ msk ] ) return dp[ now ][ msk ];
  if( now >= n ){
    for( int i = 0 ; i < n ; i ++ )
      if( bit( msk , i ) == 0 )
        return dp[ now ][ msk ] = 0ll;
    return dp[ now ][ msk ] = 1ll;
  }
  got[ now ][ msk ] = true;
  for( size_t i = 0 ; i < nxt[ msk ].size() ; i ++ ){
    int nxtmsk = nxt[ msk ][ i ];
    dp[ now ][ msk ] += DP( now + 1 , nxtmsk );
  }
  return dp[ now ][ msk ];
}
vector<PLL> qry;
bool gg[ 1010 ];
vector<int> ans[ 1010 ];
ll qsz;
void go( int now , int msk , int l , int r , ll presum ){
  for( int i = l ; i < r ; i ++ )
    ans[ qry[ i ].SE ].PB( msk );
  if( l >= r || now >= n ) return;
  int nl = l;
  for( size_t i = 0 ; i < nxt[ msk ].size() ; i ++ ){
    int nxtmsk = nxt[ msk ][ i ];
    ll tdp = DP( now + 1, nxtmsk );
    if( presum + tdp >= qry[ nl ].FI ){
      int nr = nl;
      while( nr < r && presum + tdp >= qry[ nr ].FI )
        nr ++;
      go( now + 1 , nxtmsk , nl , nr , presum );
      nl = nr;
    }
    presum += tdp;
  }
}
ll sumans;
void find_ans(){
  qsz = (ll)qry.size();
  ll presum = 0 , pre = 0;
  for( size_t i = 0 ; i < st.size() && pre < qsz ; i ++ ){
    ll tdp = DP( 1 , st[ i ] );
    if( presum + tdp >= qry[ pre ].FI ){
      ll tnxt = pre;
      while( tnxt < qsz && presum + tdp >= qry[ tnxt ].FI )
        tnxt ++;
      go( 1 , st[ i ] , pre , tnxt , presum );
      pre = tnxt;
    }
    presum += tdp;
    sumans = presum;
  }
}
ll sq[ 1010 ];
void solve(){
  // ll all = 0;
  // for( size_t i = 0 ; i < st.size() ; i ++ )
    // all += DP( 1 , st[ i ] );
  for( int i = 0 ; i < q ; i ++ ){
    ll qi = getint();
    sq[ i ] = qi;
    qry.PB( MP( qi , i ) );
  }
  sort( ALL( qry ) );
  find_ans();
  for( int i = 0 ; i < q ; i ++ ){
    if( sq[ i ] > sumans )
      puts( "No such matrix." );
    else{
      for( int j1 = 0 ; j1 < n ; j1 ++ , puts( "" ) )
        for( int j2 = 0 ; j2 < n ; j2 ++ )
          if( bit( ans[ i ][ j1 ] , j2 ) == 1 ) putchar( '1' );
          else putchar( '0' );
    }
    if( i != q - 1 ) puts( "" );
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
