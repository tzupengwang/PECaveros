#include <bits/stdc++.h>
using namespace std;
#define N 505050
struct Treap{
	int sz , val , pri , tag;
	Treap *l , *r;
	Treap( int _val ){
		val = _val; sz = 1;
		pri = rand(); l = r = NULL; tag = 0;
	}
};
void push( Treap * a ){
	if( a->tag ){
		Treap *swp = a->l; a->l = a->r; a->r = swp;
		if( a->l ) a->l->tag ^= 1;
		if( a->r ) a->r->tag ^= 1;
		a->tag = 0;
	}
}
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
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
char c[ N ];
vector<int> a;
int n;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "prefixes.in" , "r" , stdin );
  freopen( "prefixes.out" , "w" , stdout );
#endif
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  int bst = 1;
  while( bst + 1 <= n and c[ bst ] <= c[ bst + 1 ] )
    bst ++;
  if( bst == n ){
    puts( c + 1 );
    exit(0);
  }
  int pre = 1;
  for( int i = bst + 1 ; i <= n ; )
    if( c[ i ] <= c[ pre ] ){
      a.push_back( i - 1 );
      int til = i;
      while( til + 1 <= n and c[ til + 1 ] <= c[ til ] )
        til ++;
      a.push_back( til );
      i = til + 1;
      pre = til;
    }else i ++;
  Treap *t = NULL;
  for( int i = 1 ; i <= n ; i ++ )
    t = merge( t , new Treap( i ) );
  for( auto id : a ){
    Treap *tl , *tr;
    split( t , id , tl , tr );
    if( tl ) tl->tag ^= 1;
    t = merge( tl , tr );
  }
  vector<int> ans;
  for( int i = 1 ; i <= n ; i ++ ){
    Treap *tl , *tr;
    split( t , 1 , tl , tr );
    ans.push_back( tl->val );
    delete tl;
    t = tr;
  }
  for( int i = 0 ; i < n ; i ++ )
    putchar( c[ ans[ i ] ] );
  puts( "" );
}
