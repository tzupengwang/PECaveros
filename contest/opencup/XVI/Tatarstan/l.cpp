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
void build(){

}
ll a , b , c , d;
vector< tuple<ll,ll,ll,ll,ll> > ans;
set<PII> S;
void init(){
  a = getint();
  b = getint();
  c = getint();
  d = getint();
}
bool rev;
inline void Add( int ta , int tb ){
  if( S.count( MP( ta + 1 , tb + 1 ) ) ) return;
  ans.PB( MT( 1 , ta , tb , 0 , 0 ) );
}
inline void Div( int ta , int tb ){
  if( S.count( MP( ta / 2 , tb / 2 ) ) ) return;
  ans.PB( MT( 2 , ta , tb , 0 , 0 ) );
}
inline void Merge( int ta , int tb , int tc ){
  if( S.count( MP( ta , tc ) ) ) return;
  ans.PB( MT( 3 , ta , tb , tb , tc ) );
}
void output(){
  if( (int)ans.size() > 15000 ){
    puts( "0" );
    exit( 0 );
  }
  if( rev ){
    for( size_t i = 0 ; i < ans.size() ; i ++ ){
      swap( get<1>( ans[ i ] ) , get<2>( ans[ i ] ) );
      swap( get<3>( ans[ i ] ) , get<4>( ans[ i ] ) );
      if( get<0>( ans[ i ] ) == 3 ){
        swap( get<1>( ans[ i ] ) , get<3>( ans[ i ] ) );
        swap( get<2>( ans[ i ] ) , get<4>( ans[ i ] ) );
      }
    }
  }
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    if( get<0>( ans[ i ] ) == 3 )
      printf( "3 %lld %lld %lld %lld\n" , get<1>( ans[ i ] ), 
                                          get<2>( ans[ i ] ),
                                          get<3>( ans[ i ] ),
                                          get<4>( ans[ i ] ) );
    else
      printf( "%lld %lld %lld\n" , get<0>( ans[ i ] ) ,
                                   get<1>( ans[ i ] ), 
                                   get<2>( ans[ i ] ) );
}
void solve(){
  if( a > b && c > d ){
    swap( a , b );
    swap( c , d );
    rev = true;
  }
  if( a < b && c < d ){
    S.insert( MP( a , b ) );
    ll dlta = b - a;
    ll dltc = d - c;
    while( dlta % 2 == 0 ) dlta /= 2;
    if( dltc % dlta ){
      puts( "0" );
      return;
    }
    while( ( b - a ) % 2 == 0 ){
      if( a % 2 == 0 && b % 2 == 0 ){
        Div( a , b );
        a /= 2; b /= 2;
      }else if( a % 2 == 1 ){
        Add( a , b );
        a ++; b ++;
      }else if( b % 2 == 1 ){
        ll sa = a , sb = b;
        while( a != sb ){
          Add( a , b );
          a ++; b ++;
        }
        Merge( sa , sb , b );
        a = sa;
      }
    }
    while( a > c ){
      for( ll i = a ; i < b ; i ++ )
        Add( i , i + b - a );
      Merge( a , b , b + b - a );
      b += b - a;
      if( a % 2 ){
        Add( a , b );
        a ++; b ++;
      }
      Div( a , b );
      a /= 2; b /= 2;
    }
    if( d - c != b - a ){
      ll sa = a , sb = b;
      while( b - sa != d - c ){
        Add( a , b );
        a ++; b ++;
      }
      for( ll aa = sb ; aa < b ; aa += b - a )
        Merge( sa , aa , aa + b - a );
      a = sa;
    }
    while( a < c ){
      Add( a , b );
      a ++; b ++;
    }
  }else if( a == b && c == d ){
    while( a > c ){
      if( a % 2 == 0 ){
        Div( a , b );
        a /= 2; b /= 2;
      }else{
        Add( a , b );
        a ++; b ++;
      }
    }
    while( a < c ){
      Add( a , b );
      a ++; b ++;
    }
  }else{
    puts( "0" );
    exit( 0 );
  }
  output();
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
