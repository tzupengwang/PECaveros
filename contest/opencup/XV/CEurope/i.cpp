#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
struct Nd{
  int ans , lft , rgt , mn , mn_who , cnt[ 2 ];
  int llen , rlen;
  Nd *tl , *tr;
  Nd(){
    ans = 0;
    lft = rgt = 0;
    llen = rlen = 0;
    mn = mn_who = 0;
    cnt[ 0 ] = cnt[ 1 ] = 0;
    tl = tr = NULL;
  }
};
int Ans( Nd* now ){ return now ? now->ans : 0; }
int Lft( Nd* now ){ return now ? now->lft : 0; }
int Rgt( Nd* now ){ return now ? now->rgt : 0; }
int Llen( Nd* now ){ return now ? now->llen : 0; }
int Rlen( Nd* now ){ return now ? now->rlen : 0; }
int Cnt0( Nd* now ){ return now ? now->cnt[ 0 ] : 0; }
int Cnt1( Nd* now ){ return now ? now->cnt[ 1 ] : 0; }
pair<int,int> Min( Nd* now ){
  return now ? make_pair(now->mn, now->mn_who) :
               make_pair(0, 0);
}
int f( int x ){
  return (x + 1) / 2;
}
#define mid ((l+r)>>1)
void modify( Nd* now , int l , int r , int p , int v ){
  if( l == r ){
    now->ans = f( 1 );
    now->lft = now->rgt = now->mn = v;
    now->llen = now->rlen = 1;
    now->mn_who = p;
    now->cnt[ 1 ] = 1;
    return;
  }
  if( p <= mid ){
    if( !now->tl ) now->tl = new Nd();
    modify( now->tl , l , mid , p , v );
  }else{
    if( !now->tr ) now->tr = new Nd();
    modify( now->tr , mid + 1 , r , p , v );
  }
  now->lft = Lft( now->tl );
  now->rgt = Rgt( now->tr );
  bool ok = Rgt( now->tl ) < Lft( now->tr );
  if( Llen( now->tl ) == mid - l + 1 and ok )
    now->llen = Llen( now->tl ) + Llen( now->tr );
  else
    now->llen = Llen( now->tl );
  if( Rlen( now->tr ) == r - mid and ok )
    now->rlen = Rlen( now->tr ) + Rlen( now->tl );
  else
    now->rlen = Rlen( now->tr );
  now->ans = Ans( now->tl ) + Ans( now->tr );
  now->cnt[ 0 ] = Cnt0( now->tl ) + Cnt0( now->tr );
  now->cnt[ 1 ] = Cnt1( now->tl ) + Cnt1( now->tr );
  if( ok ){
    now->cnt[ Rlen( now->tl ) & 1 ] --;
    now->cnt[ Llen( now->tr ) & 1 ] --;
    now->cnt[ (Rlen( now->tl ) + Llen( now->tr )) & 1 ] ++;
    now->ans -= f( Rlen( now->tl ) );
    now->ans -= f( Llen( now->tr ) );
    now->ans += f( Rlen( now->tl ) + Llen( now->tr ) );
  }
  tie( now->mn, now->mn_who ) = min( Min( now->tl ) , Min( now->tr ) );
}
pair<int,int> query_mn( Nd* now , int l , int r , int ql , int qr ){
  if( l == ql and r == qr ) return Min( now );
  if( qr <= mid ) return query_mn( now->tl , l , mid , ql , qr );
  if( mid < ql ) return query_mn( now->tr , mid + 1 , r , ql , qr );
  return min( query_mn( now->tl , l , mid , ql , mid ) ,
              query_mn( now->tr , mid + 1 , r , mid + 1 , qr ) );
}
#define A first.first
#define L first.second.first
#define R first.second.second
#define LL second.first.first
#define RL second.first.second
#define C0 second.second.first
#define C1 second.second.second
typedef pair< pair<int, pair<int,int>> , pair<pair<int,int>, pair<int,int>> > dat;
dat query( Nd* now , int l , int r , int ql , int qr ){
  if( l == ql and r == qr )
    return { { Ans( now ) , { Lft( now ) , Rgt( now ) } } ,
             { { Llen( now ) , Rlen( now ) } ,
               { Cnt0( now ) , Cnt1( now ) } } };
  if( qr <= mid )
    return query( now->tl , l , mid , ql , qr );
  if( mid < ql )
    return query( now->tr , mid + 1 , r , ql , qr );
  dat retl = query( now->tl , l , mid , ql , mid );
  dat retr = query( now->tr , mid + 1 , r , mid + 1 , qr );

  int left = retl.L;
  int right = retr.R;
  int llen = 0 , rlen = 0;
  int ans = 0;
  bool ok = retl.R < retr.L;
  if( retl.LL == mid - ql + 1 and ok )
    llen = retl.LL + retr.LL;
  else
    llen = retl.LL;
  if( retr.RL == qr - mid and ok )
    rlen = retr.RL + retl.RL;
  else
    rlen = retr.RL;
  ans = retl.A + retr.A;
  int cnt0 = retl.C0 + retr.C0;
  int cnt1 = retl.C1 + retr.C1;
  if( ok ){
    ans -= f( retl.RL );
    ans -= f( retr.LL );
    ans += f( retl.RL + retr.LL );
    if( retl.RL & 1 ) cnt1 --;
    else cnt0 --;
    if( retr.LL & 1 ) cnt1 --;
    else cnt0 --;
    if( (retl.RL + retr.LL) & 1 )
      cnt1 ++;
    else
      cnt0 ++;
  }
  return {{ ans , {left, right} } ,
    {{llen , rlen}, {cnt0, cnt1}}};
}
int n , p[ N ] , u[ N ] , at[ N ] , pos[ N ] , ac , sz[ N ] , hf[ N ];
bool vst[ N ];
vector<int> v[ N ];
Nd *root[ N ];
int ans , tans[ N ];
int cal( int no ){
  int st = query_mn( root[ no ] , 0 , sz[ no ] - 1 , 0 , hf[ no ] - 1 ).second;
  dat ret = query( root[ no ] , 0 , sz[ no ] - 1 , 
                                        st , st + hf[ no ] - 1 );
  int rret = ret.A - ret.C1;
  return max( 1 , rret );
}
int main(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &p[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &u[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    if( vst[ i ] ) continue;
    int now = i;
    while( !vst[ now ] ){
      at[ now ] = ac;
      pos[ now ] = v[ ac ].size();
      vst[ now ] = true;
      v[ ac ].push_back( now );
      now = p[ now ];
    }
    ac ++;
  }
  for( int i = 0 ; i < ac ; i ++ ){
    root[ i ] = new Nd();
    hf[ i ] = v[ i ].size();
    sz[ i ] = v[ i ].size() * 2;
    for( size_t j = 0 ; j < v[ i ].size() ; j ++ ){
      modify( root[ i ] , 0 , sz[ i ] - 1 , j           , u[ v[ i ][ j ] ] );
      modify( root[ i ] , 0 , sz[ i ] - 1 , j + hf[ i ] , u[ v[ i ][ j ] ] );
    }
    tans[ i ] = cal( i );
    ans += tans[ i ];
  }
  printf( "%d\n" , ans );
  int q; scanf( "%d" , &q ); while( q -- ){
    int ki , vi; scanf( "%d%d" , &ki , &vi );
    int cur = at[ ki ];
    ans -= tans[ cur ];
    modify( root[ cur ] , 0 , sz[ cur ] - 1 , pos[ ki ]             , vi );
    modify( root[ cur ] , 0 , sz[ cur ] - 1 , pos[ ki ] + hf[ cur ] , vi );
    tans[ cur ] = cal( cur );
    ans += tans[ cur ];
    printf( "%d\n" , ans );
  }
}
