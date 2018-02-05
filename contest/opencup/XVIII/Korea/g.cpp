#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
struct Nd{
  int mx;
  Nd *tl , *tr;
};
inline Nd* copy( Nd* x ){
  Nd* ret = new Nd();
  if( x ){
    ret->mx = x->mx;
    ret->tl = x->tl;
    ret->tr = x->tr;
  }
  return ret;
}
#define mid ((l+r)>>1)
inline int Mx( Nd* now ){ return now ? now->mx : 0; }
void modify( Nd* now , int l , int r , int p , int v ){
  if( l == r ){
    now->mx = v;
    return;
  }
  if( p <= mid ){
    now->tl = copy( now->tl );
    modify( now->tl , l , mid , p , v );
  }else{
    now->tr = copy( now->tr );
    modify( now->tr , mid + 1 , r , p , v );
  }
  now->mx = max( Mx( now->tl ) , Mx( now->tr ) );
}
int query( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr ) return 0;
  if( ql <= l and r <= qr ) return now->mx;
  return max( query( now->tl , l , mid , ql , qr ) ,
              query( now->tr , mid + 1 , r , ql , qr ) );
}
int n , m , p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
vector< pair<LL, pair<LL,LL>> > e;
vector< pair<LL,LL> > v[ N ] , t[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int ui , vi , ci;
    scanf( "%d%d%d" , &ui , &vi , &ci );
    v[ ui ].push_back( { vi , ci } );
    v[ vi ].push_back( { ui , ci } );
    e.push_back( { ci , { ui , vi } } );
  }
}
LL mst_cst;
void build_mst(){
  for( int i = 1 ; i <= n ; i ++ ) p[ i ] = i;
  sort( e.begin() , e.end() );
  for( auto i : e ){
    if( f( i.second.first ) ==
        f( i.second.second  ) )
      continue;
    uni( i.second.first , i.second.second );
    mst_cst += i.first;
    t[ i.second.first ].push_back( { i.second.second , i.first } );
    t[ i.second.second ].push_back( { i.second.first , i.first } );
  }
}
#define K 18
int pp[ K ][ N ] , dep[ N ] , in[ N ] , out[ N ] , stmp;
Nd* root[ N ];
void go( int now , int prt , int tdep ){
  pp[ 0 ][ now ] = prt;
  dep[ now ] = tdep;
  in[ now ] = ++ stmp;
  for( auto ee : t[ now ] ){
    if( ee.first == prt ) continue;
    root[ ee.first ] = copy( root[ now ] );
    modify( root[ ee.first ] , 0 , N , tdep + 1 , ee.second );
    go( ee.first , now , tdep + 1 );
  }
  out[ now ] = stmp;
}
inline int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  while( dlt ){
    int bt = __lg( dlt & (-dlt) );
    vi = pp[ bt ][ vi ];
    dlt ^= (1 << bt);
  }
  if( ui == vi ) return ui;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( pp[ i ][ ui ] != pp[ i ][ vi ] ){
      ui = pp[ i ][ ui ];
      vi = pp[ i ][ vi ];
    }
  return pp[ 0 ][ ui ];
}
void pre_solve(){
  root[ 1 ] = new Nd();
  go( 1 , 1 , 0 );
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      pp[ j ][ i ] = pp[ j - 1 ][ pp[ j - 1 ][ i ] ];
}
int cand[ N ] , tag[ N ];
bool cmp( int id1 , int id2 ){
  if( out[ id1 ] != out[ id2 ] )
    return out[ id1 ] < out[ id2 ];
  return in[ id1 ] > in[ id2 ];
}
int ct;
inline LL find_best( int ui , int vi ){
  int tlca = lca( ui , vi );
  int ret = 0;
  if( ui != tlca )
    ret = max( ret , query( root[ ui ] , 0 , N , dep[ tlca ] + 1 , N ) );
  if( vi != tlca )
    ret = max( ret , query( root[ vi ] , 0 , N , dep[ tlca ] + 1 , N ) );
  return ret;
}
void go_cal( int i , const vector< pair<int,int> >& edges , LL ans ){
  for( int j = 0 ; j < ct ; j ++ )
    p[ cand[ j ] ] = cand[ j ];
  for( auto ee : v[ i ] )
    uni( i , ee.first );
  vector< pair<LL, pair<int,int>> > ee;
  for( auto j : edges ){
    int ui = j.first;
    int vi = j.second;
    LL bst = find_best( ui , vi );
    assert( bst );
    ee.push_back( { bst , { ui , vi } } );
    ans -= bst;
  }
  sort( ee.begin() , ee.end() );
  for( auto j : ee ){
    if( f( j.second.first ) ==
        f( j.second.second ) )
      continue;
    ans += j.first;
    uni( j.second.first ,
         j.second.second );
  }
  printf( "%lld\n" , ans );
}
void solve(){
  build_mst();
  pre_solve();
  for( int i = 1 ; i <= n ; i ++ ){
    LL ans = mst_cst;
    ct = 0;
    cand[ ct ++ ] = i;
    tag[ i ] = i;
    for( auto ee : v[ i ] ){
      ans += ee.second;
      cand[ ct ++ ] = ee.first;
      tag[ ee.first ] = i;
    }
    sort( cand , cand + ct , cmp );
    vector<int> wt;
    vector< pair<int,int> > edges;
    int cur_sz = ct;
    for( int ptr = 0 ; ptr < cur_sz ; ptr ++ ){
      int who = cand[ ptr ];
      while( true ){
        bool keep = false;
        if( (int)wt.size() > 1 ){
          int wtsz = (int)wt.size();
          int lst1 = wt[ wtsz - 1 ];
          int lst2 = wt[ wtsz - 2 ];
          if( lca( lst1 , lst2 ) == lst1 ){
            if( lst1 != lst2 )
              edges.push_back( { lst1 , lst2 } );
            wt[ wtsz - 2 ] = lst1;
            keep = true;
            wt.pop_back();
          }else if( dep[ lca( lst1 , lst2 ) ] > dep[ lca( lst2 , who ) ] ){
            int tlca = lca( lst1 , lst2 );
            if( tag[ tlca ] != i ){
              tag[ tlca ] = i;
              cand[ ct ++ ] = tlca;
            }
            if( lst1 != tlca )
              edges.push_back( { lst1 , tlca } );
            if( lst2 != tlca )
              edges.push_back( { lst2 , tlca } );
            wt.pop_back();
            wt.pop_back();
            wt.push_back( tlca );
            keep = true;
          }
        }
        if( keep ) continue;
        if( not wt.empty() ){
          if( lca( wt.back() , who ) == who ){
            if( wt.back() != who )
              edges.push_back( { wt.back() , who } );
            wt.pop_back();
            keep = true;
          }
        }
        if( not keep ) break;
      }
      wt.push_back( who );
    }
    while( (int)wt.size() > 1 ){
      int wtsz = (int)wt.size();
      int lst1 = wt[ wtsz - 1 ];
      int lst2 = wt[ wtsz - 2 ];
      if( lca( lst1 , lst2 ) == lst1 ){
        if( lst1 != lst2 )
          edges.push_back( { lst1 , lst2 } );
        wt[ wtsz - 2 ] = lst1;
        wt.pop_back();
      }else{
        int tlca = lca( lst1 , lst2 );
        if( tag[ tlca ] != i ){
          tag[ tlca ] = i;
          cand[ ct ++ ] = tlca;
        }
        if( lst1 != tlca )
          edges.push_back( { lst1 , tlca } );
        if( lst2 != tlca )
          edges.push_back( { lst2 , tlca } );
        wt.pop_back();
        wt.pop_back();
        wt.push_back( tlca );
      }
    }
    go_cal( i , edges , ans );
  }
}
int main(){
  init();
  solve();
}
