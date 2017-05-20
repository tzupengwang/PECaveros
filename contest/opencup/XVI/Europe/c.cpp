#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 200020
#define M 1048576
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
struct StackT{
  set<int> S[ M << 1 ];
  void build( int no , int l , int r ){
    S[ no ].clear();
    if( l == r ) return;
    build( L( no ) , l , mid );
    build( R( no ) , mid + 1 , r );
  }
  void modify( int no , int l , int r , int p , int v ){
    S[ no ].insert( v );
    if( l == r ) return;
    if( p <= mid ) modify( L( no ) , l , mid , p , v );
    else modify( R( no ) , mid + 1 , r , p , v );
  }
  void erase( int no , int l , int r , int p , int v ){
    S[ no ].erase( v );
    if( l == r ) return;
    if( p <= mid ) erase( L( no ) , l , mid , p , v );
    else erase( R( no ) , mid + 1 , r , p , v );
  }
  int query( int no , int l , int r , int ql , int qr , int thres ){
    if( r < ql or l > qr ) return M;
    if( ql <= l and r <= qr ){
      auto it = S[ no ].lower_bound( thres );
      if( it == S[ no ].end() ) return M;
      return *it;
    }
    return min( query( L( no ) , l , mid , ql , qr , thres ) ,
                query( R( no ) , mid + 1 , r , ql , qr , thres ) );
  }
} st1;
struct SegT{
  int st[ M << 1 ];
  bool cl[ M << 1 ];
  void build( int no , int l , int r ){
    st[ no ] = 0; cl[ no ] = false;
    if( l == r ) return;
    build( L( no ) , l , mid );
    build( R( no ) , mid + 1 , r );
  }
  void push( int no , int l , int r ){
    if( not cl[ no ] ) return;
    for( int son : { L( no ) , R( no ) } ){
      st[ son ] = 0;
      cl[ son ] = true;
    }
    cl[ no ] = false;
  }
  void modify( int no , int l , int r , int p , int vl ){
    if( l == r ){
      st[ no ] += vl;
      return;
    }
    push( no , l , r );
    if( p <= mid ) modify( L( no ) , l , mid , p , vl );
    else modify( R( no ) , mid + 1 , r , p , vl );
    st[ no ] = st[ L( no ) ] + st[ R( no ) ];
  }
  void clear( int no , int l , int r , int ql , int qr ){
    if( r < ql or l > qr ) return;
    if( ql <= l and r <= qr ){
      st[ no ] = 0;
      cl[ no ] = true;
      return;
    }
    push( no , l , r );
    clear( L( no ) , l , mid , ql , qr );
    clear( R( no ) , mid + 1 , r , ql , qr );
    st[ no ] = st[ L( no ) ] + st[ R( no ) ];
  }
  int query( int no , int l , int r , int ql , int qr ){
    if( r < ql or l > qr ) return 0;
    if( ql <= l and r <= qr ) return st[ no ];
    push( no , l , r );
    return query( L( no ) , l , mid , ql , qr ) +
           query( R( no ) , mid + 1 , r , ql , qr );
  }
} st2;
int fence , flower , cow;
int r1[ N ] , c1[ N ] , r2[ N ] , c2[ N ];
int sr1[ N ] , sc1[ N ] , sr2[ N ] , sc2[ N ];
int fr[ N ] , fc[ N ];
int cr[ N ] , cc[ N ];
vector<int> dr , dc;
const int inf = 1000010;
int szr , szc;
void init(){
  dr.clear(); dc.clear();
  //fence = 200000;
  for( int i = 0 ; i <= fence ; i ++ ){
    if( i == 0 )
      r1[ i ] = c1[ i ] = 0 , r2[ i ] = c2[ i ] = inf;
    else{
      scanf( "%d%d%d%d" , &r1[ i ] , &c1[ i ] , &r2[ i ] , &c2[ i ] );
      //c1[ i ] = 4 * i;
      //r1[ i ] = 1;
      //c2[ i ] = 4 * 
      //r2[ i ] = inf;
    }
    dr.push_back( r1[ i ] );
    dr.push_back( r2[ i ] );
    dc.push_back( c1[ i ] );
    dc.push_back( c2[ i ] );
  }
  scanf( "%d" , &flower );
  //flower = 200000;
  for( int i = 0 ; i < flower ; i ++ ){
    scanf( "%d%d" , &fr[ i ] , &fc[ i ] );
    //fr[ i ] = rand() % 1000000 + 1;
    //fc[ i ] = rand() % 1000000 + 1;
    dr.push_back( fr[ i ] );
    dc.push_back( fc[ i ] );
  }
  scanf( "%d" , &cow );
  //cow = 200000;
  for( int i = 0 ; i < cow ; i ++ ){
    scanf( "%d%d" , &cr[ i ] , &cc[ i ] );
    //cr[ i ] = rand() % 1000000 + 1;
    //cc[ i ] = rand() % 1000000 + 1;
    dr.push_back( cr[ i ] );
    dc.push_back( cc[ i ] );
  }
  sort( dr.begin() , dr.end() );
  dr.resize( unique( dr.begin() , dr.end() ) - dr.begin() );
  sort( dc.begin() , dc.end() );
  dc.resize( unique( dc.begin() , dc.end() ) - dc.begin() );
  for( int i = 0 ; i <= fence ; i ++ ){
    sr1[ i ] = r1[ i ] = lower_bound( dr.begin() , dr.end() , r1[ i ] ) - dr.begin() + 1;
    sr2[ i ] = r2[ i ] = lower_bound( dr.begin() , dr.end() , r2[ i ] ) - dr.begin() + 1;
    sc1[ i ] = c1[ i ] = lower_bound( dc.begin() , dc.end() , c1[ i ] ) - dc.begin() + 1;
    sc2[ i ] = c2[ i ] = lower_bound( dc.begin() , dc.end() , c2[ i ] ) - dc.begin() + 1;
  }
  for( int i = 0 ; i < flower ; i ++ ){
    fr[ i ] = lower_bound( dr.begin() , dr.end() , fr[ i ] ) - dr.begin() + 1;
    fc[ i ] = lower_bound( dc.begin() , dc.end() , fc[ i ] ) - dc.begin() + 1;
  }
  for( int i = 0 ; i < cow ; i ++ ){
    cr[ i ] = lower_bound( dr.begin() , dr.end() , cr[ i ] ) - dr.begin() + 1;
    cc[ i ] = lower_bound( dc.begin() , dc.end() , cc[ i ] ) - dc.begin() + 1;
  }
  szr = (int)dr.size();
  szc = (int)dc.size();
}
vector<int> fin[ M ] , fout[ M ];
vector<int> wtf[ M ] , wtc[ M ];
vector<int> ff[ N ];
vector<int> ccc[ N ];
vector<int> son_reg[ N ];
int prt[ N ] , he[ M ];
void pre_solve(){
  st1.build( 1 , 0 , szr );
  st1.modify( 1 , 0 , szr , 0 , szr );
  he[ szr ] = 0;
  for( int i = 0 ; i <= fence ; i ++ )
    son_reg[ i ].clear();
  for( int i = 1 ; i <= fence ; i ++ ){
    fin[ c1[ i ] ].push_back( i );
    fout[ c2[ i ] ].push_back( i );
  }
  for( int i = 0 ; i < flower ; i ++ )
    wtf[ fc[ i ] ].push_back( i );
  for( int i = 0 ; i < cow ; i ++ )
    wtc[ cc[ i ] ].push_back( i );
  for( int i = 0 ; i <= szc ; i ++ ){
    for( auto id : fin[ i ] ){
      int vl = st1.query( 1 , 0 , szr , 0 , r1[ id ] , r2[ id ] );
      int who = he[ vl ];
      prt[ id ] = who;
      son_reg[ who ].push_back( id );
      //printf( "Ins fence %d %d\n" , r1[ id ] , r2[ id ] );
      st1.modify( 1 , 0 , szr , r1[ id ] , r2[ id ] );
      he[ r2[ id ] ] = id;
    }
    for( auto id : wtf[ i ] ){
      int vl = st1.query( 1 , 0 , szr , 0 , fr[ id ] , fr[ id ] );
      int who = he[ vl ];
      ff[ who ].push_back( id );
      //printf( "flower %d : %d  r=%d vl=%d\n" , id , who , fr[ id ] ,
              //vl);
    }
    for( auto id : wtc[ i ] ){
      int vl = st1.query( 1 , 0 , szr , 0 , cr[ id ] , cr[ id ] );
      int who = he[ vl ];
      ccc[ who ].push_back( id );
    }
    for( auto id : fout[ i ] ){
      st1.erase( 1 , 0 , szr , r1[ id ] , r2[ id ] );
      //printf( "Out fence %d %d\n" , r1[ id ] , r2[ id ] );
    }
  }
  for( int i = 1 ; i <= fence ; i ++ ){
    fin[ c1[ i ] ].clear();
    fout[ c2[ i ] ].clear();
  }
  for( int i = 0 ; i < flower ; i ++ )
    wtf[ fc[ i ] ].clear();
  for( int i = 0 ; i < cow ; i ++ )
    wtc[ cc[ i ] ].clear();
}
int ans[ N ];
void solve(){
  for( int i = 0 ; i <= fence ; i ++ ){
    if( ccc[ i ].empty() ){
      ff[ i ].clear();
      continue;
    }
    son_reg[ i ].push_back( i );
    vector<int> ddr , ddc;
    for( auto id : son_reg[ i ] ){
      r1[ id ] = sr1[ id ];
      r2[ id ] = sr2[ id ];
      c1[ id ] = sc1[ id ];
      c2[ id ] = sc2[ id ];
      ddr.push_back( r1[ id ] );
      ddr.push_back( r1[ id ] - 1 );
      ddr.push_back( r2[ id ] );
      ddc.push_back( c1[ id ] );
      ddc.push_back( c2[ id ] );
    }
    for( auto id : ff[ i ] ){
      ddr.push_back( fr[ id ] );
      ddc.push_back( fc[ id ] );
    }
    for( auto id : ccc[ i ] ){
      ddr.push_back( cr[ id ] );
      ddc.push_back( cc[ id ] );
    }
    sort( ddr.begin() , ddr.end() );
    ddr.resize( unique( ddr.begin() , ddr.end() ) - ddr.begin() );
    sort( ddc.begin() , ddc.end() );
    ddc.resize( unique( ddc.begin() , ddc.end() ) - ddc.begin() );
    for( auto id : son_reg[ i ] ){
      r1[ id ] = lower_bound( ddr.begin() , ddr.end() , r1[ id ] )
        - ddr.begin() + 1;
      r2[ id ] = lower_bound( ddr.begin() , ddr.end() , r2[ id ] )
        - ddr.begin() + 1;
      c2[ id ] = lower_bound( ddc.begin() , ddc.end() , c2[ id ] )
        - ddc.begin() + 1;
      c1[ id ] = lower_bound( ddc.begin() , ddc.end() , c1[ id ] )
        - ddc.begin() + 1;
      fin[ c2[ id ] ].push_back( id );
      fout[ c1[ id ] ].push_back( id );
    }
    for( auto id : ff[ i ] ){
      fr[ id ] = lower_bound( ddr.begin() , ddr.end() , fr[ id ] )
        - ddr.begin() + 1;
      fc[ id ] = lower_bound( ddc.begin() , ddc.end() , fc[ id ] )
        - ddc.begin() + 1;
      wtf[ fc[ id ] ].push_back( id );
    }
    for( auto id : ccc[ i ] ){
      cr[ id ] = lower_bound( ddr.begin() , ddr.end() , cr[ id ] )
        - ddr.begin() + 1;
      cc[ id ] = lower_bound( ddc.begin() , ddc.end() , cc[ id ] )
        - ddc.begin() + 1;
      wtc[ cc[ id ] ].push_back( id );
    }
    int rsz = (int)ddr.size();
    int csz = (int)ddc.size();
    st2.build( 1 , 0 , rsz );
    multiset<int> S;
    S.insert( rsz + 1 );
    for( int cur_c = csz ; cur_c >= 1 ; cur_c -- ){
      for( auto id : fin[ cur_c ] ){
        int xx = st2.query( 1 , 0 , rsz , r1[ id ] , r2[ id ] );
        st2.clear( 1 , 0 , rsz , r1[ id ] , r2[ id ] );
        st2.modify( 1 , 0 , rsz , r1[ id ] - 1 , xx );
        S.insert( r1[ id ] );
      }
      for( auto id : wtf[ cur_c ] )
        st2.modify( 1 , 0 , rsz , fr[ id ] , 1 );
      for( auto id : wtc[ cur_c ] ){
        int til = *S.upper_bound( cr[ id ] );
        ans[ id ] = st2.query( 1 , 0 , rsz , cr[ id ] , til - 1 );
      }
      for( auto id : fout[ cur_c ] )
        S.erase( S.find( r1[ id ] ) );
    }
    for( auto id : son_reg[ i ] ){
      fin[ c2[ id ] ].clear();
      fout[ c1[ id ] ].clear();
    }
    for( auto id : ff[ i ] )
      wtf[ fc[ id ] ].clear();
    for( auto id : ccc[ i ] )
      wtc[ cc[ id ] ].clear();
    ff[ i ].clear();
    ccc[ i ].clear();
  }
  for( int i = 0 ; i < cow ; i ++ )
    printf( "%d\n" , ans[ i ] );
}
int main(){
  while( scanf( "%d" , &fence ) == 1 ){
    init();
    pre_solve();
    solve();
  }
}
