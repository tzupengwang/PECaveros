#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> set_t;
typedef long long LL;
#define N 101010
#define MAGIC 777
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
struct Treap{
	int sz , pri , val;
	Treap *l , *r;
  LL cnt , sum , ans;
	Treap( int _val ){
		sz = 1;
		pri = rand(); l = r = NULL;
    val = sum = ans = _val;
	}
};
LL Sum( Treap* a ){ return a ? a->sum : 0; }
LL Ans( Treap* a ){ return a ? a->ans : 0; }
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
  a->sum = Sum( a->l ) + Sum( a->r ) + a->val;
  a->ans = Ans( a->l ) + a->val + Ans( a->r ) +
           Sum( a->l ) + ( Sum( a->l ) + a->val ) * Size( a->r );
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
int n , g , t[ N ];
void init(){
  n = getint();
  g = getint();
  for( int i = 1 ; i <= n ; i ++ )
    t[ i ] = getint();
}
vector< pair<int,int> > vv;
set_t all;
Treap *root , *tl , *tr;
int gogo( Treap* tt , int cand ){
  if( !tt ) return 0;
  if( tt->val < cand )
    return Size( tt->l ) + 1 + gogo( tt->r , cand );
  return gogo( tt->l , cand );
}
void clear( Treap* tt ){
  if( !tt ) return;
  clear( tt->l );
  clear( tt->r );
  delete tt;
}
Treap *wwt[ N ];
void solve1(){
  root = NULL;
  for( auto i : vv )
    root = merge( root , new Treap( i.first ) );
  int q = getint(); while( q -- ){
    int who = getint();
    int nt = getint();
    int at = all.order_of_key( { t[ who ] , who } );
    all.erase( { t[ who ] , who } );
    split( root , at , tl , root );
    split( root , 1 , root , tr );
    root = merge( tl , tr );
    t[ who ] = nt;
    all.insert( { t[ who ] , who } );
    int sml = gogo( root , t[ who ] );
    split( root , sml , tl , root );
    root = merge( new Treap( t[ who ] ) , root );
    root = merge( tl , root );
    LL ans = 0;
    LL per = n / g;
    int tot = n / g + ( n % g != 0 );
    for( int i = 0 ; i < tot ; i ++ )
      split( root , min( g , Size( root ) ) , wwt[ i ] , root );
    for( int i = 0 ; i < tot ; i ++ ){
      split( wwt[ i ] , n % g , tl , tr );
      ans += ( per + 1 - i ) * Sum( tl );
      ans += ( per + 0 - i ) * Sum( tr );
      root = merge( root , tl );
      root = merge( root , tr );
    }
    printf( "%lld\n" , ans );
  }
  clear( root );
}
Treap *rr[ MAGIC + MAGIC ] , *wt[ MAGIC + MAGIC ];
int st[ N ];
void solve2(){
  for( int i = 0 ; i < g ; i ++ )
    rr[ i ] = NULL;

  for( size_t i = 0 ; i < vv.size() ; i ++ )
    rr[ i % g ] = merge( rr[ i % g ] , new Treap( vv[ i ].first ) );

  int q = getint(); while( q -- ){
    int who = getint();
    int nt = getint();
    int at = all.order_of_key( { t[ who ] , who } );
    all.erase( { t[ who ] , who } );

    {
      int which = at % g;
      int pos = at / g , pp = pos;
      for( int i = which ; i < which + g ; i ++ ){
        if( i == g ) pp ++;
        st[ i % g ] = pp;
      }
      split( rr[ which ] , pos , tl , rr[ which ] );
      split( rr[ which ] , 1 , rr[ which ] , tr );
      rr[ which ] = tl;
      wt[ which ] = tr;
      for( int i = which + 1 ; i < which + g ; i ++ )
        split( rr[ i % g ] , st[ i % g ] , rr[ i % g ] , wt[ i % g ] );
      for( int i = which ; i < which + g ; i ++ )
        rr[ i % g ] = merge( rr[ i % g ] , wt[ ( i + 1 ) % g ] );
    }
    t[ who ] = nt;
    all.insert( { t[ who ] , who } );
    at = all.order_of_key( { t[ who ] , who } );

    {
      int which = at % g;
      int pos = at / g , pp = pos;
      for( int i = which ; i < which + g ; i ++ ){
        if( i == g ) pp ++;
        st[ i % g ] = pp;
      }
      for( int i = which ; i < which + g ; i ++ )
        split( rr[ i % g ] , st[ i % g ] , rr[ i % g ] , wt[ i % g ] );
      rr[ which % g ] = merge( rr[ which % g ] , new Treap( t[ who ] ) );
      for( int i = which ; i < which + g ; i ++ )
        rr[ i % g ] = merge( rr[ i % g ] , wt[ ( i - 1 + g ) % g ] );
    }

    LL ans = 0;
    for( int i = 0 ; i < g ; i ++ )
      ans += Ans( rr[ i ] );
    printf( "%lld\n" , ans );
  }

  for( int i = 0 ; i < g ; i ++ )
    clear( rr[ i ] );
}
int _cs;
void solve(){
  printf( "Case %d:\n" , ++ _cs );
  all.clear();
  vv.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    vv.push_back( { t[ i ] , i } );
    all.insert( { t[ i ] , i } );
  }
  sort( vv.begin() , vv.end() );
  if( g >= MAGIC ) solve1();
  else solve2();
}
int main(){
  int _ = getint(); while( _ -- ){
    init();
    solve();
  }
}
