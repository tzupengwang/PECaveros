#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
#define N 404040
int BIT[ N ] , lb[ N ];
void modify( int x ){
  for( int i = x ; i < N ; i += lb[ i ] )
    BIT[ i ] ++;
}
int query( int x ){
  int ret = 0;
  for( int i = x ; i ; i -= lb[ i ] )
    ret += BIT[ i ];
  return ret;
}
int n , q;
Treap *rt[ N ];
vector<int> pos[ N ];
int ans[ N ] , at;
void go( Treap *t ){
  if( !t ) return;
  go( t->l );
  ans[ at ++ ] = t->val;
  go( t->r );
}
int main(){
  for( int i = 1 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    int ci , ai;
    scanf( "%d%d" , &ci , &ai );
    int bl = 0 , br = (int)pos[ ci ].size() - 1 , ba = -1;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( query( pos[ ci ][ bmid ] ) + 1 >= i - ai )
        ba = bmid , br = bmid - 1;
      else
        bl = bmid + 1;
    }
    if( ba == -1 ){
      pos[ ci ].push_back( ++ q );
      modify( q );
      rt[ q ] = merge( rt[ q ] , new Treap( i ) );
      continue;
    }
    int pre = query( pos[ ci ][ ba ] - 1 ) + 1;
    int lmst = i - ai;
    int tk = max( lmst , pre );
    int lsz = tk - pre;
    int cur = pos[ ci ][ ba ];
    modify( cur );
    Treap *tl , *tr;
    split( rt[ cur ] , lsz , tl , tr );
    rt[ cur ] = merge( tl , merge( new Treap( i ) , tr ) );
  }
  for( int i = 1 ; i <= q ; i ++ )
    go( rt[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == n ] );
}
