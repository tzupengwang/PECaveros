#include <bits/stdc++.h>
using namespace std;
struct Treap{
	int sz , pri;
  char val;
	Treap *l , *r;
	Treap( char _val ){
		val = _val; sz = 1;
		pri = rand(); l = r = NULL;
	}
};
Treap* copy( Treap* tmp ){
  if( tmp == NULL ) return NULL;
  Treap* tt = new Treap( ' ' );
  if( tmp ){
    tt->l = tmp->l;
    tt->r = tmp->r;
    tt->sz = tmp->sz;
    tt->val = tmp->val;
  }
  return tt;
}
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
}
Treap* merge( Treap *a , Treap *b ){
  a = copy( a );
  b = copy( b );
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
  t = copy( t );
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
#define N 50505
//string ans[ N ];
char ctmp[ 11000000 ];
int n , tp[ N ] , p[ N ] , s[ N ] , st[ N ] , len[ N ] , v[ N ];
//vector< pair< pair<int,int>, int> > q[ N ];
int qq;
void init(){
  scanf( "%d" , &n );
  int nst = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &tp[ i ] );
    if( tp[ i ] == 1 ){
      scanf( "%d" , &p[ i ] );
      scanf( "%s" , ctmp + nst );
      st[ i ] = nst;
      len[ i ] = strlen( ctmp + nst );
      nst += len[ i ] + 1;
    }else if( tp[ i ] == 2 )
      scanf( "%d%d" , &p[ i ] , &s[ i ] );
    else{
      scanf( "%d%d%d" , &v[ i ] , &p[ i ] , &s[ i ] );
      //int tv , ttp , tc;
      //scanf( "%d%d%d" , &tv , &ttp , &tc );
      //q[ tv ].push_back( { { ttp , tc } , qq } );
      //++ qq;
    }
  }
}
int d;
void go( Treap* now ){
  if( !now ) return;
  go( now->l );
  putchar( now->val );
  //ans[ iid ] += now->val;
  if( now->val == 'c' ) d ++;
  go( now->r );
}
Treap* root[ N ];
void solve(){
  Treap *tl , *tr;
  tl = tr = NULL;
  int curv = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( tp[ i ] == 3 ){
      v[ i ] -= d;
      p[ i ] -= d;
      s[ i ] -= d;
      //printf( "3 %d %d %d\n" , v[ i ] , p[ i ] , s[ i ] );
      split( root[ v[ i ] ] , p[ i ] - 1 , tl , root[ v[ i ] ] );
      split( root[ v[ i ] ] , s[ i ] , root[ v[ i ] ] , tr );
      go( root[ v[ i ] ] );
      puts( "" );
      root[ v[ i ] ] = merge( tl , root[ v[ i ] ] );
      root[ v[ i ] ] = merge( root[ v[ i ] ] , tr );
      continue;
    }
    ++ curv;
    root[ curv ] = copy( root[ curv - 1 ] );
    if( tp[ i ] == 1 ){
      p[ i ] -= d;
      //printf( "1 %d\n" , p[ i ] );
      split( root[ curv ] , p[ i ] , tl , tr );
      root[ curv ] = tl;
      for( int j = st[ i ] ; j < st[ i ] + len[ i ] ; j ++ )
        root[ curv ] = merge( root[ curv ] , new Treap( ctmp[ j ] ) );
      root[ curv ] = merge( root[ curv ] , tr );
    }else if( tp[ i ] == 2 ){
      p[ i ] -= d;
      s[ i ] -= d;
      //printf( "2 %d %d\n" , p[ i ] , s[ i ] );
      split( root[ curv ] , p[ i ] - 1 , tl , root[ curv ] );
      split( root[ curv ] , s[ i ] , root[ curv ] , tr );
      root[ curv ] = merge( tl , tr );
    }
    //for( auto j : q[ curv ] ){
      //int ttp = j.first.first;
      //int tc = j.first.second;
      //int qid = j.second;
      ////printf( "%d %d\n" , curv , qid );
      //split( t , ttp - 1 , tl , t );
      //split( t , tc , t , tr );
      //go( t , qid );
      //t = merge( tl , t );
      //t = merge( t , tr );
    //}
  }
  //for( int i = 0 ; i < qq ; i ++ )
    //printf( "%s\n" , ans[ i ].c_str() );
}
int main(){
  init();
  solve();
}
