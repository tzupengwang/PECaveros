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
struct Treap{
  PLL key , maxkey;
	ll sum , as , pri , tag , maxas;
	Treap *l , *r;
	Treap( ll _val , ll _as , int _idx ){
    maxkey = key = MP( _val , _idx );
		sum = _val;
    maxas = as = _as;
		pri = rand(); l = r = NULL; tag = 0;
	}
  void print(){
    if( l ) l->print();
    printf( "%lld %lld\n" , key.FI , key.SE );
    if( r ) r->print();
  }
};
inline ll Sum( Treap * a ){
  return a ? a->sum : 0;
}
inline void push( Treap * a ){
	if( a->tag ){
    if( a->l ){
      a->l->as += a->tag;
      a->l->tag += a->tag;
      a->l->maxas += a->tag;
    }
    if( a->r ){
      a->r->as += a->tag;
      a->r->tag += a->tag;
      a->r->maxas += a->tag;
    }
	}
	a->tag = 0;
}
inline void pull( Treap * a ){
  if( !a ) return;
  a->sum = Sum( a->l ) + Sum( a->r ) + a->key.first;
  a->maxas = a->as;
  a->maxkey = a->key;
  if( a->l && a->l->maxas > a->maxas ){
    a->maxas = a->l->maxas;
    a->maxkey = a->l->maxkey;
  }
  if( a->r && a->r->maxas > a->maxas ){
    a->maxas = a->r->maxas;
    a->maxkey = a->r->maxkey;
  }
}
Treap* merge( Treap *a , Treap *b ){
	if( !a || !b ) return a ? a : b;
	if( a->pri > b->pri ){
		push( a );
		a->r = merge( a->r , b );
		pull( a );
		return a;
	}else{
		push( b );
		b->l = merge( a , b->l );
		pull( b );
		return b;
	}
}
void split( Treap *t , PLL key , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	push( t );
  if( t->key <= key ){
		a = t;
		split( t->r , key , a->r , b );
		pull( a );
	}else{
		b = t;
		split( t->l , key , a , b->l );
		pull( b );
	}
}
#define N 101010
ll n , ff[ N ];
vector< PLL > f;
Treap *t , *tl , *tr , *t1;
inline void Insert( Treap* k ){
  split( t , k->key , tl , tr );
  t = merge( tl , k );
  t = merge( t , tr );
}
inline Treap* Best(){
  split( t , t->maxkey , t , tr );
  PLL tkey = t->maxkey; tkey.SE --;
  split( t , tkey , tl , t );
  Treap* tmp = t;
  t = merge( tl , tr );
  return tmp;
}
void build(){

}
inline void init(){
  n = getint(); t = NULL;
  for( int i = 1 ; i <= n ; i ++ ){
    ff[ i ] = getint();
    f.PB( MP( ff[ i ] , i ) );
  }
  ll psum = 0;
  sort( ALL( f ) );
  for( int i = 0 ; i < n ; i ++ ){
	  t = merge( t , new Treap( f[ i ].FI , f[ i ].FI - psum , f[ i ].SE ) );
    psum += f[ i ].FI;
  }
}
inline int query(){
  int ans = 0;
  vector<Treap*> vv;
  while( t ){
    Treap* bst = Best();
    vv.PB( bst );
    if( bst->maxas < 0 ) break;
    ans ++;
  }
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    Insert( vv[ i ] );
  return ans;
}
inline void solve(){
  int pans = query();
  printf( "%d\n" , pans );
  int m = getint(); while( m -- ){
    ll xi = getint();
    ll fi = getint();
    if( fi != ff[ xi ] ){
      PLL tkey = MP( ff[ xi ] , xi );
      split( t , tkey , t , tr );
      tkey.SE --;
      split( t , tkey , tl , t );
      PLL nkey = MP( fi , xi );
      if( ff[ xi ] < fi ){
        split( tr , nkey , t1 , tr );
        if( t1 ){
          t1->tag += ff[ xi ];
          t1->as += ff[ xi ];
          t1->maxas += ff[ xi ];
        }
        if( tr ){
          tr->tag -= fi - ff[ xi ];
          tr->as -= fi - ff[ xi ];
          tr->maxas -= fi - ff[ xi ];
        }
        t = merge( tl , t1 );
        t = merge( t , new Treap( fi , fi - Sum( t ) , xi ) );
        t = merge( t , tr );
      }else{
        split( tl , nkey , tl , t1 );
        if( t1 ){
          t1->tag -= fi;
          t1->as -= fi;
          t1->maxas -= fi;
        }
        if( tr ){
          tr->tag += ff[ xi ] - fi;
          tr->as += ff[ xi ] - fi;
          tr->maxas += ff[ xi ] - fi;
        }
        t = merge( tl , new Treap( fi , fi - Sum( tl ) , xi ) );
        t = merge( t , t1 );
        t = merge( t , tr );
      }
      pans = query();
      ff[ xi ] = fi;
    }
    printf( "%d\n" , pans );
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
