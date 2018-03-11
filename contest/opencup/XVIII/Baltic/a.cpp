#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
struct Info{
  int tot; // -1
  Info *tl , *tr;
  Info(){
    tl = tr = this;
  }
};
vector<int> a;
int ptr , nxt;
void unin( Info*& ptr1 , Info*& ptr2 ){
  if( ptr1->tot == 0 or ptr2->tot == 0 ) return;
  if( ptr1->tot > 0 and ptr2->tot > 0 ){
    uni( ptr1->tot , ptr2->tot );
    return;
  }
  unin( ptr1->tl , ptr2->tl );
  unin( ptr1->tr , ptr2->tr );
}
Info* merge( Info* p1 , Info* p2 ){
  Info* ret = new Info();
  if( p1->tot == 0 and p2->tot == 0 ){
    ret->tot = 0;
    return ret;
  }
  if( p1->tot > 0 and p2->tot > 0 ){
    ret->tot = p1->tot;
    uni( p1->tot , p2->tot );
    return ret;
  }
  ret->tot = -1;
  ret->tl = p1;
  ret->tr = p2;
  return ret;
}
void go( Info*& l , Info*& r , Info*& u , Info*& d ){
  int val = a[ ptr ++ ];
  if( val == 0 ){
    l = new Info(); r = new Info();
    u = new Info(); d = new Info();
    l->tot = r->tot = u->tot = d->tot = 0;
    return;
  }
  if( val == 1 ){
    l = new Info(); r = new Info();
    u = new Info(); d = new Info();
    l->tot = r->tot = u->tot = d->tot = ++ nxt;
    return;
  }
  Info *cl[ 4 ] , *cr[ 4 ] , *cu[ 4 ] , *cd[ 4 ];
  for( int i = 0 ; i < 4 ; i ++ )
    go( cl[ i ] , cr[ i ] , cu[ i ] , cd[ i ] );
  unin( cr[ 0 ] , cl[ 1 ] );
  unin( cd[ 1 ] , cu[ 2 ] );
  unin( cl[ 2 ] , cr[ 3 ] );
  unin( cu[ 3 ] , cd[ 0 ] );
  l = merge( cl[ 0 ] , cl[ 3 ] );
  r = merge( cr[ 1 ] , cr[ 2 ] );
  u = merge( cu[ 0 ] , cu[ 1 ] );
  d = merge( cd[ 3 ] , cd[ 2 ] );
}
int main(){
  for( int i = 0 ; i < N ; i ++ )
    p[ i ] = i;
  int x;
  while( cin >> x )
    a.push_back( x );
  Info *l , *r , *u , *d;
  go( l , r , u , d );
  int ans = 0;
  for( int i = 1 ; i <= nxt ; i ++ )
    if( f( i ) == i )
      ans ++;
  printf( "%d\n" , ans );
}
