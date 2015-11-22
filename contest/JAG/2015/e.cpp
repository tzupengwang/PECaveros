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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 1021
int n , l;
char c[ N ];
class Map{
public:
  int nxti[ 111 ][ 111 ];
  int nxtj[ 111 ][ 111 ];
  bool tag[ 111 ][ 111 ];
  vector<PII> sv;
  void print() const{
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ ){
        printf( "%d %d : %d\n" , i , j , nxti[ i ][ j ] );
        printf( "%d %d : %d\n" , i , j , nxtj[ i ][ j ] );
      }
    puts( "=====" );
  }
  Map operator*( const Map& x ) const{
    Map tmp;
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ ){
        int tni = nxti[ i ][ j ];
        int tnj = nxtj[ i ][ j ];
        tmp.nxti[ i ][ j ] = x.nxti[ tni ][ tnj ];
        tmp.nxtj[ i ][ j ] = x.nxtj[ tni ][ tnj ];
      }
    return tmp;
  }
  Map operator^( const int& k ){
    Map tmp;
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        tag[ i ][ j ] = false;
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        if( !tag[ i ][ j ] ){
          sv.clear();
          int ni = i, nj = j;
          while( !tag[ ni ][ nj ] ){
            tag[ ni ][ nj ] = true;
            sv.PB( MP( ni , nj ) );
            int nxi = nxti[ ni ][ nj ];
            int nxj = nxtj[ ni ][ nj ];
            ni = nxi; nj = nxj;
          }
          int sz = (int)sv.size();
          int sft = k % sz;
          for( int u = 0 ; u < sz ; u ++ ){
            int xx = ( u + sft ) % sz;
            tmp.nxti[ sv[ u ].FI ][ sv[ u ].SE ] = sv[ xx ].FI;
            tmp.nxtj[ sv[ u ].FI ][ sv[ u ].SE ] = sv[ xx ].SE;
          }
        }
    return tmp;
  }
};
Map dir[ 4 ][ N ], o;
// L R U D
int find_dir( char ctmp ){
  if( ctmp == 'L' ) return 0;
  if( ctmp == 'R' ) return 1;
  if( ctmp == 'U' ) return 2;
  if( ctmp == 'D' ) return 3;
  return -1;
}
int di[]={0,0,-1,1};
int dj[]={-1,1,0,0};
void pre_build(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      o.nxti[ i ][ j ] = i,
      o.nxtj[ i ][ j ] = j;
  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      for( int k = 1 ; k <= n ; k ++ )
        for( int k2 = 1 ; k2 <= n ; k2 ++ )
          dir[ i ][ j ].nxti[ k ][ k2 ] = k,
          dir[ i ][ j ].nxtj[ k ][ k2 ] = k2;
      if( i < 2 ){
        for( int k2 = 1 ; k2 <= n ; k2 ++ ){
          int tnxt = k2 + dj[ i ];
          if( tnxt < 1 ) tnxt += n; if( tnxt > n ) tnxt -= n;
          dir[ i ][ j ].nxtj[ j ][ k2 ] = tnxt;
        }
      }else{
        for( int k2 = 1 ; k2 <= n ; k2 ++ ){
          int tnxt = k2 + di[ i ];
          if( tnxt < 1 ) tnxt += n; if( tnxt > n ) tnxt -= n;
          dir[ i ][ j ].nxti[ k2 ][ j ] = tnxt;
        }
      }
    }
}
void build(){

}
void init(){
  n = getint();
  l = getint();
  scanf( "%s" , c );
  pre_build();
}
int ptr;
int getInt(){
  int vl = 0;
  while( ptr < l && c[ ptr ] >= '0' && c[ ptr ] <= '9' )
    vl = vl * 10 + c[ ptr ++ ] - '0';
  return vl;
}
Map parse(){
  Map now = o, now2;
  while( c[ ptr ] != ')' && ptr < l ){
    int ndir = -1;
    if( c[ ptr ] == '(' ){
      ptr ++;
      now2 = parse();
      // now.print();
      // printf( "==========> %d\n" , ptr );
      ptr ++; // for ')'
    }else ndir = find_dir( c[ ptr ++ ] );
    int x = getInt();
    // printf( "=======> %d %d\n" , x , ndir );
    if( ndir >= 0 ) now = now * dir[ ndir ][ x ];
    else now = now * ( now2 ^ x );
    // now.print();
  }
  // printf( "%d\n" , ptr );
  // now.print();
  // puts( "===========" );
  return now;
}
int ans[ N ][ N ];
void solve(){
  Map fans = parse();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      int ai = fans.nxti[ i ][ j ];
      int aj = fans.nxtj[ i ][ j ];
      ans[ ai ][ aj ] = ( i - 1 ) * n + j;
    }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      printf( "%d%c" , ans[ i ][ j ] , " \n"[ j == n ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
