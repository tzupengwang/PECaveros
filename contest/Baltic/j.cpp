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
#define N 100010
#define S 350
int n , on[ N ];
int from , sum;
deque<int> d[ S ];
void build(){
  
}
void init(){
  n = getint();
}
vector<int> v;
void rebuild(){
  v.clear();
  for( int i = from ; i < S ; i ++ )
    for( int j = 0 ; j < (int)d[ i ].size() ; j ++ )
      v.PB( d[ i ][ j ] );
  for( int i = 0 ; i < from ; i ++ )
    for( int j = 0 ; j < (int)d[ i ].size() ; j ++ )
      v.PB( d[ i ][ j ] );
  for( int i = 0 ; i < S ; i ++ ) d[ i ].clear();
  from = 0;
  for( int i = 0 ; i < (int)v.size() ; i ++ ){
    d[ i / S ].push_back( v[ i ] );
    on[ v[ i ] ] = i / S;
  }
}
char c[ 4 ];
void solve(){
  int idx = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( i % S == 0 ) rebuild();
    scanf( "%s" , c );
    if( c[ 0 ] == 'F' )
      d[ from ].push_front( ++ idx ),
        on[ idx ] = from , ++ sum;
    else if( c[ 0 ] == 'B' )
      d[ ( from - 1 + S ) % S ].push_back( ++ idx ),
        on[ idx ] = ( from - 1 + S ) % S, ++ sum;
    else{
      int tmp = getint();
      int didx = on[ tmp ];
      int dpre = ( didx - 1 + S ) % S;
      int tsum = 0;
      for( int j = from ; j != didx ; j = ( j + 1 ) % S )
        tsum += (int)d[ j ].size();
      --sum;
      while( d[ didx ].front() != tmp ){
        int vl = d[ didx ].front();
        d[ didx ].pop_front();
        tsum ++;
        d[ dpre ].push_back( vl );
        on[ vl ] = dpre;
      }
      d[ didx ].pop_front();
      printf( "%d\n" , min( tsum , sum - tsum ) );
      from = didx;
    }
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
