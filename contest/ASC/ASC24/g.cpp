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
vector< int > S[ N ];
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
map< pair<int,int> , int > dp;
map< pair<int,int> , pair<int,int> > from;
map< int , int > xay , xmy , x;
vector< int > vxay[ N ] , vxmy[ N ] , vx[ N ];
int ixay , ixmy , ix;
int bstl[ N ] , whol[ N ] , bstr[ N ] , whor[ N ];
int ans;
PII bst;
inline void update( const pair<int,int>& tp , int tdp ){
  if( dp.count( tp ) == 0 ||
      tdp < dp[ tp ] )
    dp[ tp ] = tdp;
}
inline void go( const pair<int,int>& tp ){
  if( dp[ tp ] > ans ){
    ans = dp[ tp ];
    bst = tp;
  }
}
void gogo( pair<int,int>& tp ){
  if( tp.first == 0 && tp.second == 0 ) return;
  PII bk = from[ tp ];
  if( bk.Y != tp.Y ){
    gogo( bk );
    printf( "%d\n" , id[ tp ] );
  }else{
    gogo( bk );
    if( bk.X < tp.X ){
      vector< int > vx , vy;
      int id = yy[ tp.Y ];
      for( int xx : s[ id ] )
        if( xx < bk.X )
          vx.push_back( xx );
        else if( xx != bk.X && xx < tp.X )
          vx.push_back( xx );
      sort( vx.begin() , vx.end() );
      reverse( vx.begin() , vx.end() );
      sort( vy.begin() , vy.end() );
      for( int x : vx )
        printf( "%d\n" )
    }else{

    }
  }
}
inline void find_ans(){
  printf( "%d\n" , ans );
  gogo( bst );
}
void solve(){
  dp[ { 0 , 0 } ] = 0;
  xay[ 0 ] = ixay ++;
  xmy[ 0 ] = ixmy ++;
  x[ 0 ] = ix ++;
  vxay[ 0 ].push_back( { 0 , 0 } );
  vxmy[ 0 ].push_back( { 0 , 0 } );
  vx[ 0 ].push_back( { 0 , 0 } );
  for( int l = 1 , r = 1 ; l < n ; l = r ){
    while( r < n && v[ l ].Y == v[ r ].Y ) r ++;
    for( int i = l ; i < r ; i ++ ){
      if( xay.count[ v[ i ].X + v[ i ].Y ] == 0 )
        xay[ v[ i ].X + v[ i ].Y ] = ixay ++;
      if( xmy.count[ v[ i ].X - v[ i ].Y ] == 0 )
        xmy[ v[ i ].X - v[ i ].Y ] = ixmy ++;
      if( x.count[ v[ i ].X ] == 0 )
        x[ v[ i ].X ] = ix ++;
      int idxay = xay[ v[ i ].X + v[ i ].Y ];
      int idxmy = xmy[ v[ i ].X - v[ i ].Y ];
      int idx   =   x[ v[ i ].X ];
      if( vxay[ idxay ].size() ){
        update( v[ i ] , dp[ vxay[ idxay ].back() ] + 1 );
        from[ v[ i ] ] = vxay[ idxay.back() ];
      }
      if( vxmy[ idxmy ].size() ){
        update( v[ i ] , dp[ vxmy[ idxmy ].back() ] + 1 );
        from[ v[ i ] ] = vxmy[ idxmy.back() ];
      }
      if( vx[ idx ].size() ){
        update( v[ i ] , dp[ vx[ idx ].back() ] + 1 );
        from[ v[ i ] ] = vx[ idx.back() ];
      }
      vxay[ idxay ].push_back( v[ i ] );
      vxmy[ idxmy ].push_back( v[ i ] );
      vx[ idx ].push_back( v[ i ] );
    }
    for( int i = l ; i < r ; i ++ ){
      if( i == l ){
        bstl[ i ] = -1;
        whol[ i ] = -1;
      }else{
        bstl[ i ] = bstl[ i - 1 ];
        whol[ i ] = whol[ i - 1 ];
        if( dp[ v[ i - 1 ] ] > bstl[ i ] ){
          bstl[ i ] = dp[ v[ i - 1 ] ];
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
        if( dp[ v[ i + 1 ] ] > bstr[ i ] ){
          bstr[ i ] = dp[ v[ i + 1 ] ];
          whor[ i ] = i + 1;
        }
      }
    }
    for( int i = l ; i < r ; i ++ ){
      if( bstl[ i ] != -1 ){
        int tdp = bstl[ i ] + i - l;
        update( v[ i ] , tdp );
      }
      if( bstr[ i ] != -1 ){
        int tdp = bstr[ i ] + r - i - 1;
        update( v[ i ] , tdp );
      }
    }
    for( int i = l ; i < r ; i ++ )
      go( v[ i ] );
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
