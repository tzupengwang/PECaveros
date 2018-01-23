#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Treap{
	int sz , pri , gg , dg , mingg , id , res;
  LL tv , totv;
	Treap *l , *r;
	Treap( int _val , int _id , int ngg , int _res ){
    id = _id;
    sz = 1;
    res = _res;
		pri = rand();
    mingg = gg = dg = ngg;
    totv = tv = _val;
    l = r = NULL;
	}
};
void minus_g( Treap* a , int dlt ){
  a->dg += dlt;
  a->gg -= dlt;
  a->mingg -= dlt;
}
void push( Treap * a ){
  if( a->dg ){
    if( a->l ){
      a->l->dg += a->dg;
      a->l->gg -= a->dg;
      a->l->mingg -= a->dg;
    }else{
      a->r->dg += a->dg;
      a->r->gg -= a->dg;
      a->r->mingg -= a->dg;
    }
    a->dg = 0;
  }
}
int Size( Treap* a ){ return a ? a->sz : 0; }
int Min( Treap* a ){ return a ? a->mingg : 1e9; }
LL Tot( Treap* a ){ return a ? a->totv : 0; }
void pull( Treap * a ){
  a->mingg = min( a->gg , min( Min( a->l ) , Min( a->r ) ) );
  a->totv = a->tv + Tot( a->l ) + Tot( a->r );
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
map<int,Treap*> sell , buy;
map< tuple<int,int,int> , int > trade;
void gogogo( int cid , Treap* now , int pri , int nr ){
  if( !now ) return;
  trade[ make_tuple( cid , now->id , pri ) ] += nr * now->tv;
}
int find_til( Treap* now , int rv ){
  int ret = 0;
  push( now );
  if( Tot( now->l ) <= rv and Min( now->l ) > 0 ){
    if( Tot( now->l ) + now->tv <= rv and now->gg > 0 )
      return SZ( now->l ) + 1 + find_til( now->r , rv - Tot( now->l ) - tv );
    return SZ( now->l );
  }
  return find_til( now->l , rv );
}
void gogo( int cid , int& V , int pri , Treap*& root ){
  int round = 0;
  while( root and V > 0 ){
    round += min( Min( root ) , V / Tot( root ) );

    minus_g( root , round );

    V -= round * Tot( root );
    if( V ){
      int til = find_til( root , V );
      if( til ){
        Treap *tl , *tm , *tr;
        split(  )
      }
    }
  }
  if( round )
    gogogo( cid , root , pri , round );
  return root;
}
void Buy( int cid , int P , int V , int TV ){
  while( not sell.empty() and sell.begin()->first <= P and V > 0 ){
    gogo( cid , V , sell->begin()->first , sell.begin()->second );
    if( sell.begin()->second == NULL )
      sell.erase( sell.begin() );
  }
  if( V )
    buy[ P ] = merge( buy[ P ] , new Treap( TV , cid , V / TV , V % TV ) );
}
void solve(){
  int n; scanf( "%d" , &n ); while( n -- ){
    int id , T , P , V , TV;
    scanf( "%d%d%d%d%d" , &id , &T , &P , &V , &TV );
    if( T == 1 ) Buy( id , P , V , TV );
    else Sell( id , P , V , TV );
  }
  for( auto i : trade )
    printf( "%d %d %d %d\n" , i.first.first , i.first.second ,
                              i.second.first , i.second.second );
  while( sell.size() and buy.size() ){
    if( sell.begin()->first < buy.begin()->firs ){
      print( sell.begin()->second , 2 );
      sell.erase( sell.begin() );
    }else{
      print( buy.begin()->second , 1 );
      buy.erase( buy.begin() );
    }
  }
  while( sell.size() ){
    print( sell.begin()->second , 2 );
    sell.erase( sell.begin() );
  }
  while( buy.size() ){
    print( buy.begin()->second , 1 );
    buy.erase( buy.begin() );
  }
}
int main(){
#ifndef EDDY
  freopen( ".in" , "r" , stdin );
  freopen( ".out" , "w" , stdout );
#endif
  solve();
}
