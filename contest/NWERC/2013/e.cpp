// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define P 200000
int a , b , c;
bool p[ P ];
vector<ll> pset , cnt;
vector<ll> fac;
int psz;
ll dp[ P ];
ll pp[ P ];
void build(){
  for( int i = 2 ; i < P ; i ++ ) if( !p[ i ] ){
    pset.PB( i ); cnt.PB( 0 );
    for( int j = P / i ; j >= i ; j -- )
      p[ i * j ] = true;
  }
  psz = (int)pset.size();
  int pre = 400;
  for( int i = 2 ; i < P ; i ++ ) pp[ i ] = i;
  for( int i = 2 ; i < P ; i ++ ){
    dp[ i ] ++;
    for( int j = 2 ; j <= pre ; j ++ ){
      pp[ j ] *= j;
      if( pp[ j ] >= P ){
        pre = j - 1;
        break;
      }
      dp[ pp[ j ] ] += dp[ i ];
    }
  }
}
void init(){
  int beta = 1;
  for( int i = 2 ; i < a ; i ++ ){
    bool got = false;
    for( int j = 1 , num = i ; num <= a ; j ++ , num *= i )
      if( num == a ){
        beta = j;
        got = true;
        break;
      }
    if( got ) break;
  }
  a = beta;
  for( int i = 0 ; i < psz ; i ++ ) cnt[ i ] = 0;
  for( int i = 0 ; i < psz ; i ++ ){
    if( a % pset[ i ] == 0 ){
      int tcnt = 0;
      while( a % pset[ i ] == 0 ){
        tcnt ++;
        a /= pset[ i ];
      }
      cnt[ i ] += tcnt;
    }
    if( b % pset[ i ] == 0 ){
      int tcnt = 0;
      while( b % pset[ i ] == 0 ){
        tcnt ++;
        b /= pset[ i ];
      }
      cnt[ i ] += tcnt * c;
    }
  }
  fac.clear();
  for( int i = 0 ; i < psz ; i ++ ) if( cnt[ i ] ){
    fac.PB( cnt[ i ] );
//    printf( "%d : %lld\n" , pset[ i ] , cnt[ i ] );
  }
}
void solve(){
  ll maxc = 0;
  for( int i = 0 ; i < (int)fac.size() ; i ++ )
    maxc = max( maxc , fac[ i ] );
  ll ans = 0;
  for( int i = 2 ; i <= maxc ; i ++ ){
    ll tmp = 1;
    for( int j = 0 ; j < (int)fac.size() ; j ++ )
      tmp *= ( ( fac[ j ] / i ) + 1ll );
    tmp --;
    tmp *= dp[ i ];
    ans += tmp;
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( scanf( "%d^%d^%d" , &a , &b , &c ) == 3 ){
    init();
    solve();
  }
}
