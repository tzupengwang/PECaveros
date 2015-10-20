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
#define N 410
map<string,int> M;
vector<string> rv[ N ];
vector<int> v[ N ];
string in;
int n , k;
bool rn[ N ];
queue<int> Q;
void build(){

}
string program = "::PROGRAM";
bool is_program( const string& s1 ){
  int len = s1.length();
  if( len < 9 ) return false;
  for( int i = 9, j = 0; j < 9 ; i -- , j ++ )
    if( s1[ len - i ] != program[ j ] )
      return false;
  return true;
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    cin >> in >> k;
    M[ in ] = i;
    if( is_program( in ) ){
      rn[ M[ in ] ] = true;
      Q.push( M[ in ] );
    }
    //cout << "\"" << in << "\"" << endl;
    int nidx = M[ in ];
    getline( cin , in );
    getline( cin , in );
    //cout << "\"" << in << "\"" << endl;
    stringstream ss( in );
    while( k -- ){
      ss >> in;
      rv[ nidx ].PB( in );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < (int)rv[ i ].size() ; j ++ )
      v[ M[ rv[ i ][ j ] ] ].PB( i );
}
void solve(){
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( int i = 0 ; i < (int)v[ tn ].size() ; i ++ )
      if( !rn[ v[ tn ][ i ] ] ){
        rn[ v[ tn ][ i ] ] = true;
        Q.push( v[ tn ][ i ] );
      }
  }
  int ans = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( !rn[ i ] )
      ans ++;
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
