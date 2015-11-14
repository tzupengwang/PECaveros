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
#define N 2048
int n;
void build(){

}
void init(){
  n = getint();
}
int cnt[ N ];
void cal( vector<int>& v ){
  int tans = 0;
  for( int i = 0 ; i < n ; i ++ ){
    bool flag = false;
    if( v[ i ] == i + 1 ) flag = true;
    if( v[ ( i + 1 ) % n ] == i + 1 ) flag = true;
    if( v[ ( i - 1 + n ) % n ] == i + 1 ) flag = true;
    if( flag ) tans ++;
  }
  cnt[ tans ] ++;
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ ) cnt[ i ] = 0;
  vector<int> v;
  for( int i = 1 ; i <= n ; i ++ ) v.PB( i );
  do cal( v );
  while( next_permutation( ALL( v ) ) );
  for( int i = 0 ; i <= n ; i ++ )
    printf( "%d : %d\n" , i , cnt[ i ] );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
