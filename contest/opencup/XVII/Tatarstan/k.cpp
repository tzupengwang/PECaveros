#include <bits/stdc++.h>
using namespace std;
#define N 131072
int n , m , v[ N ];
struct SegT{
  int mn[ N << 1 ] , lwho[ N << 1 ] , rwho[ N << 1 ];
  int cc[ N << 1 ] , lmc[ N << 1 ] , rmc[ N << 1 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
  void build_st( int no , int l , int r ){
    cc[ no ] = 0;
    lmc[ no ] = 0;
    rmc[ no ] = 0;
    if( l == r ) return;
    build_st( L( no ) , l , mid );
    build_st( R( no ) , mid + 1 , r );
  }
  void modify( int no , int l , int r , int p , int vv ){
    if( l == r ){
      mn[ no ] = vv;
      lwho[ no ] = rwho[ no ] = l;
      cc[ no ] ++;
      lmc[ no ] = cc[ no ] - l;
      rmc[ no ] = cc[ no ] + l;
      return;
    }
    if( p <= mid ) modify( L( no ) , l , mid , p , vv );
    else modify( R( no ) , mid + 1 , r , p , vv );
    if( mn[ L( no ) ] <= mn[ R( no ) ] ){
      mn[ no ] = mn[ L( no ) ];
      lwho[ no ] = lwho[ L( no ) ];
    }else{
      mn[ no ] = mn[ R( no ) ];
      lwho[ no ] = lwho[ R( no ) ];
    }
    if( mn[ L( no ) ] < mn[ R( no ) ] ){
      mn[ no ] = mn[ L( no ) ];
      rwho[ no ] = rwho[ L( no ) ];
    }else{
      mn[ no ] = mn[ R( no ) ];
      rwho[ no ] = rwho[ R( no ) ];
    }
    lmc[ no ] = max( lmc[ L( no ) ] , lmc[ R( no ) ] );
    rmc[ no ] = max( rmc[ L( no ) ] , rmc[ R( no ) ] );
  }
  int query_lb( int no , int l , int r , int dd ){
    if( l == r ) return lmc[ no ] < dd ? 0 : l;
    if( lmc[ R( no ) ] >= dd )
      return query_lb( R( no ) , mid + 1 , r , dd );
    return query_lb( L( no ) , l , mid , dd );
  }
  int query_rb( int no , int l , int r , int dd ){
    if( l == r ) return rmc[ no ] < dd ? m + 1 : l;
    if( rmc[ L( no ) ] >= dd )
      return query_rb( L( no ) , l , mid , dd );
    return query_rb( R( no ) , mid + 1 , r , dd );
  }
  pair<int,int> ok_intv( int p ){
    int hardlb = query_lb( 1 , 1 , m , n + 2 - p );
    int softlb = query_lb( 1 , 1 , m , n + 1 - p );
    int hardrb = query_rb( 1 , 1 , m , n + 2 + p );
    int softrb = query_rb( 1 , 1 , m , n + 1 + p );
    return { min( p , max( softlb , hardlb + 1 ) ) ,
             max( p , min( softrb , hardrb - 1 ) ) };
    //return { query_lb( 1 , 1 , m , n + 2 - p ) ,
             //query_rb( 1 , 1 , m , n + 2 + p ) };
  }
  pair<int,int> query_rr( int no , int l , int r , int ql , int qr ){
    if( l == ql and r == qr ) return { mn[ no ] , rwho[ no ] };
    if( qr <= mid ) return query_rr( L( no ) , l , mid , ql , qr );
    if( mid < ql ) return query_rr( R( no ) , mid + 1 , r , ql , qr );
    pair<int,int> p1 = query_rr( L( no ) , l , mid , ql , mid );
    pair<int,int> p2 = query_rr( R( no ) , mid + 1 , r , mid + 1 , qr );
    if( p1.first < p2.first ) return p1;
    return p2;
  }
  pair<int,int> query_ll( int no , int l , int r , int ql , int qr ){
    if( l == ql and r == qr ) return { mn[ no ] , lwho[ no ] };
    if( qr <= mid ) return query_ll( L( no ) , l , mid , ql , qr );
    if( mid < ql ) return query_ll( R( no ) , mid + 1 , r , ql , qr );
    pair<int,int> p1 = query_ll( L( no ) , l , mid , ql , mid );
    pair<int,int> p2 = query_ll( R( no ) , mid + 1 , r , mid + 1 , qr );
    if( p1.first <= p2.first ) return p1;
    return p2;
  }
  int best_post( int p ){
    int lb , rb;
    tie( lb , rb ) = ok_intv( p );
    //cout << p << " " << lb << " " << rb << endl;
    int lbst = query_rr( 1 , 1 , m , lb , p ).second;
    int rbst = query_ll( 1 , 1 , m , p , rb ).second;
    //cout << lbst << " " << rbst << endl;
    if( v[ lbst ] < v[ rbst ] ) return lbst;
    if( v[ lbst ] > v[ rbst ] ) return rbst;
    if( p - lbst <= rbst - p ) return lbst;
    return rbst;
  }
} seg;
int main(){
  scanf( "%d%d" , &m , &n );
  seg.build_st( 1 , 1 , m );
  long long sc = 0;
  for( int i = 1 ; i <= m ; i ++ ){
    scanf( "%d" , &v[ i ] );
    seg.modify( 1 , 1 , m , i , v[ i ] );
    sc += v[ i ];
  }
  int k; scanf( "%d" , &k ); while( k -- ){
    int pos , vv; scanf( "%d%d" , &pos , &vv );
    int bst = seg.best_post( pos );
    //printf( "   %d\n" , bst );
    sc -= v[ bst ];
    v[ bst ] = vv;
    sc += v[ bst ];
    seg.modify( 1 , 1 , m , bst , v[ bst ] );
    printf( "%lld\n" , sc );
  }
}
