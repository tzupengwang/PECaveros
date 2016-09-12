#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
#define N 50505
int n;
#define X first
#define Y second
vector< pair<int,int> > v;
bool cmp( pair<int,int> p1 ,
          pair<int,int> p2 ){
  if( p1.Y != p2.Y )
    return p1.Y < p2.Y;
  return p1.X < p2.X;
}
map< pair<int,int> , int > id;
map< int , int  > yy;
int yycnt;
vector< int > s[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    int xi , yi;
    scanf( "%d%d" , &xi , &yi );
    id[ { xi , yi } ] = i + 1;
    v.push_back( { xi , yi } );
    if( yy.count( yi ) == 0 ) yy[ yi ] = yycnt ++;
    s[ yy[ yi ] ].push_back( xi );
  }
  id[ { 0 , 0 } ] = 0;
  v.push_back( { 0 , 0 } );
  sort( v.begin() , v.end() , cmp );
}
map< pair<int,int> , int > dp , pdp;
map< pair<int,int> , pair<int,int> > from , from2;
map< int , int > xay , xmy , x;
vector< pair<int,int> > vxay[ N ] , vxmy[ N ] , vx[ N ];
int ixay , ixmy , ix;
int bstl[ N ] , whol[ N ] , bstr[ N ] , whor[ N ];
int ans;
PII bst;
inline bool update( map< pair<int,int> , int >& _dp ,
                    const pair<int,int>& tp ,
                    int tdp ){
  if( _dp.count( tp ) == 0 ||
      tdp > _dp[ tp ] ){
    _dp[ tp ] = tdp;
    return true;
  }
  return false;
}
inline void go( const pair<int,int>& tp ){
  if( dp.count( tp ) == 0 ) return;
  // printf( "(%d,%d) %d %d\n" , tp.X , tp.Y , pdp[ tp ] , dp[ tp ] );
  if( dp[ tp ] > ans ){
    ans = dp[ tp ];
    bst = tp;
  }
}
vector< int > vans;
void gogo( pair<int,int>& tp ){
  if( tp.first == 0 && tp.second == 0 ) return;
  PII bk = from2[ tp ];
  if( bk == tp ){
    gogo( from[ bk ] );
    vans.push_back( id[ tp ] );
  }else{
    gogo( from[ bk ] );
    if( bk.X < tp.X ){
      vector< int > ox , oy;
      int tid = yy[ tp.Y ];
      for( int xx : s[ tid ] )
        if( xx <= bk.X )
          ox.push_back( xx );
        else if( xx <= tp.X )
          oy.push_back( xx );
      sort( ox.begin() , ox.end() );
      reverse( ox.begin() , ox.end() );
      sort( oy.begin() , oy.end() );
      for( int u : ox )
        vans.push_back( id[ { u , tp.Y } ] );
      for( int u : oy )
        vans.push_back( id[ { u , tp.Y } ] );
    }else{
      vector< int > ox , oy;
      int tid = yy[ tp.Y ];
      for( int xx : s[ tid ] )
        if( xx >= bk.X )
          ox.push_back( xx );
        else if( xx >= tp.X )
          oy.push_back( xx );
      sort( ox.begin() , ox.end() );
      sort( oy.begin() , oy.end() );
      reverse( oy.begin() , oy.end() );
      for( int u : ox )
        vans.push_back( id[ { u , tp.Y } ] );
      for( int u : oy )
        vans.push_back( id[ { u , tp.Y } ] );
    }
  }
}
inline void find_ans(){
  printf( "%d\n" , ans );
  gogo( bst );
  for( size_t i = 0 ; i < vans.size() ; i ++ )
    printf( "%d%c" , vans[ i ] , " \n"[ i + 1 == vans.size() ] );
}
void solve(){
  dp[ { 0 , 0 } ] = 0;
  xay[ 0 ] = ixay ++;
  xmy[ 0 ] = ixmy ++;
  x[ 0 ] = ix ++;
  vxay[ 0 ].push_back( { 0 , 0 } );
  vxmy[ 0 ].push_back( { 0 , 0 } );
  vx[ 0 ].push_back( { 0 , 0 } );
  for( int l = 1 , r = 1 ; l <= n ; l = r ){
    while( r <= n && v[ l ].Y == v[ r ].Y ) r ++;
    for( int i = l ; i < r ; i ++ ){
      if( xay.count( v[ i ].X + v[ i ].Y ) == 0 )
        xay[ v[ i ].X + v[ i ].Y ] = ixay ++;
      if( xmy.count( v[ i ].X - v[ i ].Y ) == 0 )
        xmy[ v[ i ].X - v[ i ].Y ] = ixmy ++;
      if( x.count( v[ i ].X ) == 0 )
        x[ v[ i ].X ] = ix ++;
      int idxay = xay[ v[ i ].X + v[ i ].Y ];
      int idxmy = xmy[ v[ i ].X - v[ i ].Y ];
      int idx   =   x[ v[ i ].X ];
      if( vxay[ idxay ].size() && dp.count( vxay[ idxay ].back() ) ){
        if( update( pdp , v[ i ] , dp[ vxay[ idxay ].back() ] + 1 ) )
          from[ v[ i ] ] = vxay[ idxay ].back();
      }
      if( vxmy[ idxmy ].size() && dp.count( vxmy[ idxmy ].back() ) ){
        if( update( pdp , v[ i ] , dp[ vxmy[ idxmy ].back() ] + 1 ) )
          from[ v[ i ] ] = vxmy[ idxmy ].back();
      }
      if( vx[ idx ].size() && dp.count( vx[ idx ].back() ) ){
        if( update( pdp , v[ i ] , dp[ vx[ idx ].back() ] + 1 ) )
          from[ v[ i ] ] = vx[ idx ].back();
      }
    }
    for( int i = l ; i < r ; i ++ )
      if( pdp.count( v[ i ] ) ){
        dp[ v[ i ] ] = pdp[ v[ i ] ];
        from2[ v[ i ] ] = v[ i ];
      }
    for( int i = l ; i < r ; i ++ ){
      if( i == l ){
        bstl[ i ] = -1;
        whol[ i ] = -1;
      }else{
        bstl[ i ] = bstl[ i - 1 ];
        whol[ i ] = whol[ i - 1 ];
        if( pdp.count( v[ i - 1 ] ) &&
          pdp[ v[ i - 1 ] ] > bstl[ i ] ){
          bstl[ i ] = pdp[ v[ i - 1 ] ];
          whol[ i ] = i - 1;
        }
      }
    }
    for( int i = r - 1 ; i >= l ; i -- ){
      if( i == r - 1 ){
        bstr[ i ] = -1;
        whor[ i ] = -1;
      }else{
        bstr[ i ] = bstr[ i + 1 ];
        whor[ i ] = whor[ i + 1 ];
        if( pdp.count( v[ i + 1 ] ) &&
            pdp[ v[ i + 1 ] ] > bstr[ i ] ){
          bstr[ i ] = pdp[ v[ i + 1 ] ];
          whor[ i ] = i + 1;
        }
      }
    }
    for( int i = l ; i < r ; i ++ ){
      if( bstl[ i ] != -1 ){
        int tdp = bstl[ i ] + i - l;
        // printf( "(%d,%d) from (%d,%d) get %d + %d\n" , v[ i ].X , v[ i ].Y ,
              // v[ whol[ i ] ].X , v[ whol[ i ] ].Y , bstl[ i ] , i - l );
        if( update( dp , v[ i ] , tdp ) )
          from2[ v[ i ] ] = v[ whol[ i ] ];
      }
      if( bstr[ i ] != -1 ){
        int tdp = bstr[ i ] + r - i - 1;
        // printf( "(%d,%d) from (%d,%d) get %d + %d\n" , v[ i ].X , v[ i ].Y ,
              // v[ whor[ i ] ].X , v[ whor[ i ] ].Y , bstr[ i ] , r - i - 1 );
        if( update( dp , v[ i ] , tdp ) )
          from2[ v[ i ] ] = v[ whor[ i ] ];
      }
    }
    for( int i = l ; i < r ; i ++ ){
      if( dp.count( v[ i ] ) ){
        int idxay = xay[ v[ i ].X + v[ i ].Y ];
        int idxmy = xmy[ v[ i ].X - v[ i ].Y ];
        int idx   =   x[ v[ i ].X ];
        vxay[ idxay ].push_back( v[ i ] );
        vxmy[ idxmy ].push_back( v[ i ] );
        vx[ idx ].push_back( v[ i ] );
      }
    }
    for( int i = l ; i < r ; i ++ ){
      go( v[ i ] );
      // if( pdp.count( v[ i ] ) )
        // printf( "pdp: (%d,%d) = %d\n" , v[ i ].X , v[ i ].Y , pdp[ v[ i ] ] );
      // if( dp.count( v[ i ] ) )
        // printf( "dp: (%d,%d) = %d\n" , v[ i ].X , v[ i ].Y , dp[ v[ i ] ] );
    }
  }
  find_ans();
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "queen.in" , "r" , stdin );
  freopen( "queen.out" , "w" , stdout );
#endif
  init();
  solve();
}
