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
set< tuple<ll,ll,ll> > S;
typedef set< tuple<ll,ll,ll> >::iterator si;
int n;
void build(){

}
void init(){
  n = getint();
}
ll area( ll len , ll h ){
  ll th = h - len + 1;
  return ( h + th ) * len / 2;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    ll tx = getint();
    ll ty = getint();
    // puts( "========" );
    // for( si it = S.begin() ; it != S.end() ; it ++ )
      // printf( "%lld %lld %lld\n" , get<0>( *it ) ,
                                   // get<1>( *it ) ,
                                   // get<2>( *it ) );
    ll tx2 = tx + ty;
    si it = S.lower_bound( MT( tx , -1000000001 ,
                                    -1000000001 ) );
    ll narea = area( tx2 - tx + 1 , ty + 1 );
    vector< tuple<ll,ll,ll> > New, Old;
    ll nr = tx2;
    while( it != S.end() &&
           max( get<1>( *it ) , tx ) <=
           min( get<0>( *it ) , tx2 ) ){
      // printf( "%lld %lld %lld\n" , get<0>( *it ) ,
                                   // get<1>( *it ) ,
                                   // get<2>( *it ) );
      if( get<1>( *it ) + get<2>( *it ) - 1 >= tx2 ){
        nr = get<1>( *it ) - 1;
        ll th = ty - ( max( 0LL , get<1>( *it ) - tx ) ) + 1;
        narea -= area( tx2 - max( tx , get<1>( *it ) ) + 1 , th );
        break;
      }
      if( get<1>( *it ) <= tx ){
        Old.PB( *it );
        if ( get<1>( *it ) < tx )
          New.PB( MT( tx - 1 , get<1>( *it ) , get<2>( *it ) ) );
        ll th = get<2>( *it ) - ( tx - get<1>( *it ) );
        narea -= area( get<0>( *it ) - tx + 1 , th );
      } else{
        Old.PB( *it );
        narea -= area( get<0>( *it ) - get<1>( *it ) + 1 , get<2>( *it ) );
      }
      it ++;
    }
    if ( nr >= tx ) New.PB( MT( nr , tx , ty + 1 ) );
    cout << narea << endl;
    for( int j = 0 ; j < (int)Old.size() ; j ++ )
      S.erase( S.find( Old[ j ] ) );
    for( int j = 0 ; j < (int)New.size() ; j ++ )
      S.insert( New[ j ] );
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
