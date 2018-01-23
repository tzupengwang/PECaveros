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
#define N 30303
char c[ N ];
void build(){

}
int len , pl[ N ] , pr[ N ];
void init(){
  scanf( "%s" , c + 1 );
  len = strlen( c + 1 );
  vector< int > v;
  for( int i = 1 ; i <= len ; i ++ ){
    if( c[ i ] == '(' ) v.push_back( i );
    if( c[ i ] == ')' ){
      pl[ i ] = v.back();
      pr[ v.back() ] = i;
      v.pop_back();
    }
  }
}
pair<string,int> cal2( pair<string,int> p1 , pair<string,int> p2 ){
  int cst = p1.SE + p2.SE;
  p1.FI += p2.FI;
  bool flag = true;
  string ns = p1.FI;
  while( flag ){
    flag = false;
    int tlen = ns.length();
    string ts = "";
    for( int i = 0 ; i < tlen ; i ++ )
      if( ns[ i ] == 'B' ){
        if( i + 3 < tlen ){
          cst ++;
          ts += ns[ i + 1 ];
          pair<string,int> pp = cal2( { string( "" + ns[ i + 2 ] ) , 0 } ,
                                      { string( "" + ns[ i + 3 ] ) , 0 } );
          cst += pp.SE;
          ts += pp.FI;
          i += 3;
          flag = true;
        }else ts += 'B';
      }else if( ns[ i ] == 'C' ){
        if( i + 3 < tlen ){
          ts += ns[ i + 1 ];
          ts += ns[ i + 3 ];
          ts += ns[ i + 2 ];
          i += 3;
          cst ++;
          flag = true;
        }else ts += 'C';
      }else if( ns[ i ] == 'K' ){
        if( i + 2 < tlen ){
          cst ++;
          ts += ns[ i + 1 ];
          i += 2;
          flag = true;
        }else ts += 'K';
      }else if( ns[ i ] == 'I' ){
        if( i + 1 < tlen ){
          cst ++;
          ts += ns[ i + 1 ];
          i += 1;
          flag = true;
        }else ts += 'I';
      }
    ns = ts;
  }
  return { ns , cst };
}
pair<string,int> cal( int l , int r ){
  if( l > r ) return { string( "" ) , 0 };
  if( l == r ) return { string( "" + c[ l ] ) , 0 };
  deque< pair<string,int> > kd;
  for( int i = l ; i <= r ; ){
    if( c[ i ] == '(' ){
      kd.push_back( cal( i + 1 , pr[ i ] - 1 ) );
      i = pr[ i ];
    }
    if( c[ i ] == ')' );
    else{
      if( c[ i ] == 'B' ) kd.push_back( { string( "B" ) , 0 } );
      if( c[ i ] == 'C' ) kd.push_back( { string( "C") , 0 } );
      if( c[ i ] == 'K' ) kd.push_back( { string( "K" ) , 0 } );
      if( c[ i ] == 'I' ) kd.push_back( { string( "I" ) , 0 } );
    }
    i ++;
  }
  bool flag = true;
  int cst = 0;
  while( flag ){
    flag = false;
    if( kd[ 0 ].FI.length() > 0 ){
      pair<string,int> pp = kd[ 0 ];
      cst += pp.SE;
      kd.pop_front();
      int xlen = pp.FI.length();
      for( int i = xlen - 1 ; i >= 0 ; i -- )
        kd.push_front( { string( "" + pp.FI[ i ] ) , 0 } );
    }
    deque< pair<string,int> > tkd;
    for( size_t i = 0 ; i < kd.size() ; i ++ )
      if( kd[ i ].FI[ 0 ] == 'B' ){
        if( i + 3 < kd.size() ){
          cst ++;
          pair<string,int> pp = cal2( kd[ i + 2 ] , kd[ i + 3 ] );
          tkd.push_back( kd[ i + 1 ] );
          tkd.push_back( pp );
          flag = true;
          i += 3;
        }else tkd.push_back( kd[ i ] );
      }else if( kd[ i ].FI[ 0 ] == 'C' ){
        if( i + 3 < kd.size() ){
          cst ++;
          tkd.push_back( kd[ i + 1 ] );
          tkd.push_back( kd[ i + 3 ] );
          tkd.push_back( kd[ i + 2 ] );
          flag = true;
          i += 3;
        }else tkd.push_back( kd[ i ] );
      }else if( kd[ i ].FI[ 0 ] == 'K' ){
        if( i + 2 < kd.size() ){
          cst ++;
          tkd.push_back( kd[ i + 1 ] );
          i += 2;
          flag = true;
        }else tkd.push_back( kd[ i ] );
      }else if( kd[ i ].FI[ 0 ] == 'I' ){
        if( i + 1 < kd.size() ){
          cst ++;
          tkd.push_back( kd[ i + 1 ] );
          i += 1;
          flag = true;
        }else tkd.push_back( kd[ i ] );
      }
    kd = tkd;
  }
  string res = "";
  for( size_t i = 0 ; i < kd.size() ; i ++ ){
    res += kd[ i ].FI;
    cst += kd[ i ].SE;
  }
  return { res , cst };
}
void solve(){
  printf( "%d\n" , cal( 1 , len ).SE );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
