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
#define N 514
void build(){

}
void init(){

}
int op[ N ][ N ];
bool can( int nx , int ny ){
  if( op[ nx ][ ny ] ) return false;
  op[ nx ][ ny ] = 2;
  printf( "%d %d\n" , nx , ny );
  fflush( stdout );
  return true;
}
int di[]={0,1,1,1};
int dj[]={1,0,1,-1};
inline bool in( int xi , int xj ){
  return 1 <= xi && xi <= 19 &&
         1 <= xj && xj <= 19;
}
inline PII gowin(){
  for( int i = 1 ; i <= 19 ; i ++ )
    for( int j = 1 ; j <= 19 ; j ++ )
      if( op[ i ][ j ] == 1 ){
        for( int dir = 0 ; dir < 4 ; dir ++ ){
          int cnt = 0 , cnt2 = 0;
          vector< PII > con;
          for( int k = -1 ; k < 4 ; k ++ ){
            int ni = i + di[ dir ] * k;
            int nj = j + dj[ dir ] * k;
            if( in( ni , nj ) ){
              if( op[ ni ][ nj ] == 1 ) cnt ++;
              else if( op[ ni ][ nj ] == 2 ) cnt2 ++;
              else con.push_back( { ni , nj } );
            }
          }
          if( cnt2 == 0 && cnt == 3 && con.size() ){
            if( (int)con.size() == 1 || con[ 0 ] != MP( i - di[ dir ] ,
                                                        j - dj[ dir ] ) )
              return con[ 0 ];
            return con[ 1 ];
          } 
        }
        for( int dir = 0 ; dir < 4 ; dir ++ ){
          int cnt = 0;
          vector<PII> con;
          for( int k = -1 ; k < 5 ; k ++ ){
            int ni = i + di[ dir ] * k;
            int nj = j + dj[ dir ] * k;
            if( in( ni , nj ) ){
              if( op[ ni ][ nj ] == 1 ) cnt ++;
              else if( op[ ni ][ nj ] == 0 )
                con.push_back( { ni , nj } );
            }
          }
          if( cnt >= 4 && con.size() ){
            if( (int)con.size() == 1 || con[ 0 ] != MP( i - di[ dir ] ,
                                                        j - dj[ dir ] ) )
              return con[ 0 ];
            return con[ 1 ];
          }
        }
      }
  return { -1 , -1 };
}
int nxt = 5;
void go( int _ ){
  PII pos = gowin();
  if( pos.FI == -1 || _ >= 5 )
    assert( can( 1 , nxt -- ) );
  else
    assert( can( pos.FI , pos.SE ) );
}
void solve(){
  for( int _ = 0 ; ; _ ++ ){
    int hx , hy;
    scanf( "%d %d" , &hx , &hy );
    if( hx == -1 && hy == -1 ) break;
    op[ hx ][ hy ] = 1;
    go( _ );
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
