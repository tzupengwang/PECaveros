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
#define N 1010
vector< pair<int,pair<ll,ll> > > pos[ N ];
int len;
char c[ N ];
void build(){

}
void init(){
  len = strlen( c + 1 );
  for( int i = 1 ; i <= len ; i ++ )
    pos[ i ].clear();
}
void test( int tpos ){
  if( c[ tpos ] >= '1' && c[ tpos ] <= '9' ){
    ll tnum = 0;
    for( int k = tpos ; k <= min( len , tpos + 8 ) ; k ++ )
      if( c[ k ] >= '0' && c[ k ] <= '9' ){
        tnum *= 10ll;
        tnum += c[ k ] - '0';
        pos[ tpos ].PB( MP( k , MP( tnum , tnum ) ) );
      }else break;
  }else if( c[ tpos ] == '0' ){
    pos[ tpos ].PB( MP( tpos , MP( 0 , 0 ) ) );
  }else if( c[ tpos ] == '+' && tpos < len ){
    bool npos[ N ] = {};
    ll tmin[ N ] = {};
    ll tmax[ N ] = {};
    for( int i = 0 ; i < (int)pos[ tpos + 1 ].size() ; i ++ ){
      ll lmin = pos[ tpos + 1 ][ i ].SE.FI;
      ll lmax = pos[ tpos + 1 ][ i ].SE.SE;
      int ti = pos[ tpos + 1 ][ i ].FI;
      if( ti < len ){
        for( int j = 0 ; j < (int)pos[ ti + 1 ].size() ; j ++ ){
          ll rmin = pos[ ti + 1 ][ j ].SE.FI;
          ll rmax = pos[ ti + 1 ][ j ].SE.SE;
          int tj = pos[ ti + 1 ][ j ].FI;
          if( !npos[ tj ] ){
            tmin[ tj ] = lmin + rmin;
            tmax[ tj ] = lmax + rmax;
            npos[ tj ] = true;
          }else{
            tmin[ tj ] = min( tmin[ tj ] , lmin + rmin );
            tmax[ tj ] = max( tmax[ tj ] , lmax + rmax );
          }
        }
      }
    }
    for( int i = tpos ; i <= len ; i ++ )
      if( npos[ i ] ){
        pos[ tpos ].PB( MP( i , MP( tmin[ i ] , tmax[ i ] ) ) );
      }
  }else if( c[ tpos ] == '-' && tpos < len ){
    bool npos[ N ] = {};
    ll tmin[ N ] = {};
    ll tmax[ N ] = {};
    for( int i = 0 ; i < (int)pos[ tpos + 1 ].size() ; i ++ ){
      ll lmin = pos[ tpos + 1 ][ i ].SE.FI;
      ll lmax = pos[ tpos + 1 ][ i ].SE.SE;
      int ti = pos[ tpos + 1 ][ i ].FI;
      if( ti < len ){
        for( int j = 0 ; j < (int)pos[ ti + 1 ].size() ; j ++ ){
          ll rmin = pos[ ti + 1 ][ j ].SE.FI;
          ll rmax = pos[ ti + 1 ][ j ].SE.SE;
          int tj = pos[ ti + 1 ][ j ].FI;
          if( !npos[ tj ] ){
            tmin[ tj ] = lmin - rmax;
            tmax[ tj ] = lmax - rmin;
            npos[ tj ] = true;
          }else{
            tmin[ tj ] = min( tmin[ tj ] , lmin - rmax );
            tmax[ tj ] = max( tmax[ tj ] , lmax - rmin );
          }
        }
      }
      if( !npos[ ti ] ){
        tmin[ ti ] = -lmax;
        tmax[ ti ] = -lmin;
        npos[ ti ] = true;
      }else{
        tmin[ ti ] = min( tmin[ ti ] , -lmax );
        tmax[ ti ] = max( tmax[ ti ] , -lmin );
      }
    }
    for( int i = tpos ; i <= len ; i ++ )
      if( npos[ i ] ){
        pos[ tpos ].PB( MP( i , MP( tmin[ i ] , tmax[ i ] ) ) );
      }
  }
}
void solve(){
  for( int i = len ; i >= 1 ; i -- )
    test( i );
  ll ansmin = 0 , ansmax = 0;
  for( int i = 0 ; i < (int)pos[ 1 ].size() ; i ++ )
    if( pos[ 1 ][ i ].FI == len ){
      ansmin = pos[ 1 ][ i ].SE.FI;
      ansmax = pos[ 1 ][ i ].SE.SE;
    }
  cout << ansmin << " ";
  cout << ansmax << "\n";
}
int main(){
  build();
  //__ = getint();
  while( scanf( "%s" , c + 1 ) == 1 ){
    init();
    solve();
  }
}
