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
#define N 110
int W , H;
int n , w[ N ] , h[ N ];
void build(){

}
void init(){
  W = getint();
  H = getint();
  if( W > H ) swap( W , H );
  int tc = getint(); while( tc -- ){
    int ta = getint();
    int tw = getint();
    int th = getint();
    while( ta -- ){
      w[ n ] = tw;
      h[ n ++ ] = th;
    }
  }
}
int tn;
int sm[ N ] , mx[ N ];
bool goodword( const vector<PII>& tv , int msk ){
  for( int i = 1 ; i <= W ; i ++ )
    sm[ i ] = mx[ i ] = 0;
  //printf( "%d %d : \n" , W , H );
  for( int i = 0 ; i < tn ; i ++ ){
    int wi = tv[ i ].FI;
    int hi = tv[ i ].SE;
    if( ( 1 << i ) & msk ) swap( wi , hi );
    //printf( "%d %d\n" , wi , hi );
    if( wi > W ) return false;
    int ns = 1, nh = H + H;
    for( int l = 1 ; l <= W - wi + 1 ; l ++ )
      if( mx[ l ] < nh )
        nh = mx[ l ] , ns = l;
    for( int j = ns ; j < ns + wi ; j ++ )
      if( mx[ j ] > nh )
        nh = mx[ j ];
    for( int j = ns ; j < ns + wi ; j ++ ){
      sm[ j ] += hi;
      mx[ j ] = max( mx[ j ] , nh + hi );
    }
  }
  // for( int i = 1 ; i <= W ; i ++ )
    // printf( "%d %d\n" , sm[ i ] , mx[ i ] );
  for( int i = 1 ; i <= W ; i ++ )
    if( sm[ i ] != H || mx[ i ] != H )
      return false;
  return true;
}
bool good( int msk ){
  vector<int> per;
  vector<PII> st , st2;
  for( int i = 0 ; i < n ; i ++ )
    if( ( 1 << i ) & msk ){
      st.PB( MP( w[ i ] , h[ i ] ) );
      st2.PB( MP( w[ i ] , h[ i ] ) );
    }
  tn = (int)st.size();
  for( int i = 0 ; i < tn ; i ++ )
    per.PB( i );
  do{
     for( int i = 0 ; i < tn ; i ++ )
       st2[ i ] = st[ per[ i ] ];
    for( int j = 0 ; j < ( 1 << tn ) ; j ++ )
      if( goodword( st2 , j ) )
        return true;
  }while( next_permutation( ALL( per ) ) );
  return false;
}
void solve(){
  for( int i = 1 ; i < ( 1 << n ) ; i ++ )
    if( good( i ) ){
      puts( "yes" );
      return;
    }
  puts( "no" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
