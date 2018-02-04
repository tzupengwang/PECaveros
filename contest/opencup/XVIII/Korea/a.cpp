#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
struct Nd{
  LL bst , tag;
  Nd *tl , *tr;
  Nd(){
    tl = tr = NULL;
    bst = tag = 0;
  }
};
const LL inf = 1e10;
#define mid ((l+r)>>1)
LL Bst( Nd* td ){
  return td ? td->bst : 0;
}
void push( Nd* now , LL l , LL r ){
  if( !now->tag ) return;
  if( !now->tl ) now->tl = new Nd();
  if( !now->tr ) now->tr = new Nd();
  now->tl->bst += now->tag;
  now->tl->tag += now->tag;
  now->tr->bst += now->tag;
  now->tr->tag += now->tag;
  now->tag = 0;
}
void modify( Nd* now , LL l , LL r , LL ql , LL qr , LL qd ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    now->bst += qd;
    now->tag += qd;
    return;
  }
  push( now , l , r );
  if( ql <= mid and !now->tl ) now->tl = new Nd();
  if( mid < qr  and !now->tr ) now->tr = new Nd();
  modify( now->tl , l , mid , ql , qr , qd );
  modify( now->tr , mid + 1 , r , ql , qr , qd );
  now->bst = max( Bst( now->tl ) , Bst( now->tr ) );
}
LL n , l , r , ans;
vector< pair< LL , tuple<LL,LL,LL> > > events;
void init(){
  scanf( "%lld%lld%lld" , &n , &l , &r );
  while( n -- ){
    LL x , y , s;
    scanf( "%lld%lld%lld" , &x , &y , &s );
    // [x - r, x + r]
    // [y - r, y + r]
    events.push_back( { x - r     , make_tuple( y - r , y + r , + s ) } );
    events.push_back( { x + r + 1 , make_tuple( y - r , y + r , - s ) } );
    // [x - l + 1 , x + l - 1]
    events.push_back( { x - l + 1 , make_tuple( y - l + 1 , y + l - 1 , - s ) } );
    events.push_back( { x + l     , make_tuple( y - l + 1 , y + l - 1 , + s ) } );
  }
  sort( events.begin() , events.end() );
}
Nd* root;
void solve(){
  root = new Nd();
  for( size_t bl = 0 , br = 0 ; bl < events.size() ; bl = br ){
    while( br < events.size() and events[ bl ].first == events[ br ].first ) br ++;
    for( size_t i = bl ; i < br ; i ++ ){
      LL ly = get<0>( events[ i ].second );
      LL ry = get<1>( events[ i ].second );
      LL dd = get<2>( events[ i ].second );
      modify( root , -inf , +inf , ly , ry , dd );
    }
    ans = max( ans , Bst( root ) );
  }
  printf( "%lld\n" ,ans );
}
int main(){
  init();
  solve();
}
