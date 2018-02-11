#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Nd{
  LL sum , cnt;
  Nd *tl , *tr;
  Nd(){
    tl = tr = NULL;
    sum = cnt = 0;
  }
};
Nd* copy( Nd * x ){
  Nd* ret = new Nd();
  if( x ){
    ret->tl = x->tl;
    ret->tr = x->tr;
    ret->sum = x->sum;
    ret->cnt = x->cnt;
  }
  return ret;
}
LL Sum( Nd* now ){ return now ? now->sum : 0; }
LL Cnt( Nd* now ){ return now ? now->cnt : 0; }
#define mid ((l+r)>>1)
void modify( Nd* now , int l , int r , int p , int v ){
  if( l == r ){
    now->sum += v;
    now->cnt ++;
    return;
  }
  if( p <= mid ){
    now->tl = copy( now->tl );
    modify( now->tl , l , mid , p , v );
  }else{
    now->tr = copy( now->tr );
    modify( now->tr , mid + 1 , r , p , v );
  }
  now->sum = Sum( now->tl ) + Sum( now->tr );
  now->cnt = Cnt( now->tl ) + Cnt( now->tr );
}
pair<LL,LL> query( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr or ql > qr ) return {0, 0};
  if( ql <= l and r <= qr ) return {now->sum, now->cnt};
  pair<LL,LL> retl = query( now->tl , l , mid , ql , qr );
  pair<LL,LL> retr = query( now->tr , mid + 1 , r , ql , qr );
  return {retl.first + retr.first,
          retl.second + retr.second};
}
#define N 101010
const int inf = 1000000000;
LL n , t[ N ];
Nd *root[ N ];
void init(){
  scanf( "%lld" , &n );
  //n = 100000;
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &t[ i ] );
    //t[ i ] = rand() % inf + 1;
  for( int i = n - 1 ; i >= 0 ; i -- ){
    root[ i ] = copy( root[ i + 1 ] );
    modify( root[ i ] , 1 , inf , t[ i ] , t[ i ] );
  }
}
void solve(){
  vector< pair<LL, pair<int,int> > > v;
  v.push_back( { 0 , { 0 , 0 } } );
  int K = max( 10 , (int)1e6 / (int)n );
  //cerr << K << endl;
  for( int i = 0 ; i < n ; i ++ ){
    vector< pair<LL, pair<int,int> > > nv;
    for( auto st : v ){
      LL cst = st.first;
      int t1 = st.second.first;
      int t2 = st.second.second;
      if( t[ i ] >= t1 ){
        nv.push_back( { cst , { t[ i ] , t2 } } );
      }else if( t[ i ] <= t2 and t2 ){
        //nv.push_back( { cst , { t1 , t2 } } );
        nv.push_back( { cst + t2 - t[ i ] , { t1 , t2 } } );
      }else{
        LL join_1 = t1 - t[ i ];
        LL join_2 = 0;
        {
          pair<LL,LL> rr = query( root[ i + 1 ] , 1 , inf , t2 + 1 , t[ i ] );
          join_2 += rr.second * t[ i ] - rr.first;
        }
        {
          pair<LL,LL> rr = query( root[ i + 1 ] , 1 , inf , 1 , t2 );
          join_2 += rr.second * (t[ i ] - t2);
        }
        nv.push_back( { cst + join_1 , { t1 , t2 } } );
        //nv.push_back( { cst + join_2 , { t1 , t[ i ] } } );
        nv.push_back( { cst , { t1 , t[ i ] } } );
      }
    }
    sort( nv.begin() , nv.end() );
    size_t nsz = 1;
    for( size_t ii = 1 ; ii < nv.size() ; ii ++ ){
      bool ok = true;
      for( size_t j = 0 ; j < nsz and ok ; j ++ )
        if( nv[ ii ].second == nv[ j ].second )
          ok = false;
      if( not ok ) continue;
      nv[ nsz ++ ] = nv[ ii ];
    }
    nv.resize( nsz );
    if( (int)nsz > K ){
      random_shuffle( nv.begin() + K / 2 , nv.begin() + nv.size() );
      nv.resize( K );
    }
    v.swap( nv );
    //for( auto ii : v )
      //printf( "%lld %d %d\n" , ii.first , ii.second.first , ii.second.second );
    //puts( "" );
  }
  printf( "%lld\n" , v[ 0 ].first );
}
int main(){
  init();
  solve();
}
