#include <bits/stdc++.h>
using namespace std;
struct Treap{
	int sz , pri , tag;
  char val;
	Treap *l , *r;
	Treap( char _val ){
		val = _val; sz = 1;
		pri = rand();
    l = r = NULL;
    tag = 0;
	}
};
void push( Treap * a ){
	if( a->tag ){
		Treap *swp = a->l; a->l = a->r; a->r = swp;
		if( a->l )
			a->l->tag ^= 1;
		if( a->r )
			a->r->tag ^= 1;
	}
	a->tag = 0;
}
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap* a ){
  if( a ){
    a->sz = Size( a->l ) + Size( a->r ) + 1;
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
void split( Treap *t , int k , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	push( t );
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
char c[ 202020 ];
int q;
void init(){
  gets( c + 1 );
  scanf( "%d" , &q );
}
void solve(){
	Treap *t = NULL , *tl = NULL , *tr = NULL;
  int len = strlen( c + 1 );
  for( int i = 1 ; i <= len ; i ++ )
    t = merge( t , new Treap( c[ i ] ) );
	while( q -- ){
    int v;
    scanf( "%d" , &v );
    split( t , v , tl , tr );
    if( tl ) tl->tag ^= 1;
    if( tr ) tr->tag ^= 1;
    t = merge( tl , tr );
	}
  for( int i = 1 ; i <= len ; i ++ ){
    split( t , 1 , tl , t );
    putchar( tl->val );
  }
  puts( "" );
}
int main(){
  init();
  solve();
}
