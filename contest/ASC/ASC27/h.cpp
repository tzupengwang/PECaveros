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
struct Treap{
	int sz , val , pri;
	Treap *l , *r;
	Treap( int _val ){
		val = _val; sz = 1;
		pri = rand(); l = r = NULL;
	}
};
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
}
Treap* merge( Treap *a , Treap *b ){
	if( !a || !b ) return a ? a : b;
	if( a->pri > b->pri ){
		a->r = merge( a->r , b );
		pull( a );
		return a;
	}else{
		b->l = merge( a , b->l );
		pull( b );
		return b;
	}
}
void split( Treap *t , int k , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	if( Size( t->l ) + 1 <= k ){
		a = t;
		split( t->r , k - Size( t->l ) - 1 , a->r , b );
		pull( a );
	}else{
		b = t;
		split( t->l , k , a , b->l );
		pull( b );
	}
}
void build(){

}
int n , m;
void init(){
  n = getint();
  m = getint();
}
void solve(){
  Treap *tl , *t = NULL , *tr;
  for( int i = 1 ; i <= n ; i ++ )
    t = merge( t , new Treap( i ) );
  while( m -- ){
    int l = getint();
    int r = getint();
    split( t , r , t , tr );
    split( t , l - 1 , tl , t );
    t = merge( t , tl );
    t = merge( t , tr );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    split( t , 1 , tl , t );
    printf( "%d%c" , tl->val , " \n"[ i == n ] );
  }
}
int main(){
  freopen( "movetofront.in" , "r" , stdin );
  freopen( "movetofront.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
