#include <bits/stdc++.h>
using namespace std;
#define N 55
#define INF 1000000000
int n , m;
char c[ N ][ N ];
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
bool in( int xn , int xm ){
  return 0 <= xn and xn < n and 
         0 <= xm and xm < m;
}
bool init(){
  cin >> n >> m;
  if( n == 0 and m == 0 )
    return false;
  for( int i = 0 ; i < n ; i ++ )
    cin >> c[ i ];
  return true;
}
int dp[ N ][ N ][ 4 ];
int cst[ N ][ N ][ 4 ][ 4 ];
bool pos( int ni , int nj ){
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ )
      if( c[ ni + i ][ nj + j ] == '*' )
        return false;
  return true;
}
int ddi[ 4 ][ 2 ] = { { -1 , -1 } , { +0 , +1 } , { +2 , +2 } , { +0 , +1 } };
int ddj[ 4 ][ 2 ] = { { +0 , +1 } , { -1 , -1 } , { +0 , +1 } , { +2 , +2 } };
int vst[ N ][ N ] , stmp , dst[ N ][ N ];
int cost( int ni , int nj , pair<int,int> ss , pair<int,int> tt ){
  if( ss == tt ) return 0;
  ++ stmp;
  queue< pair<int,int> > Q;
  vst[ ss.first ][ ss.second ] = stmp;
  dst[ ss.first ][ ss.second ] = 0;
  Q.push( ss );
  while( Q.size() ){
    int curn , curm; tie( curn , curm ) = Q.front(); Q.pop();
    for( int dir = 0 ; dir < 4 ; dir ++ ){
      int nxtn = curn + dn[ dir ];
      int nxtm = curm + dm[ dir ];
      if( not in( nxtn , nxtm ) or
          c[ nxtn ][ nxtm ] == '*' )
        continue;
      if( ni <= nxtn and nxtn < ni + 2 and
          nj <= nxtm and nxtm < nj + 2 )
        continue;
      if( vst[ nxtn ][ nxtm ] == stmp )
        continue;
      vst[ nxtn ][ nxtm ] = stmp;
      dst[ nxtn ][ nxtm ] = dst[ curn ][ curm ] + 1;
      if( make_pair( nxtn , nxtm ) == tt )
        return dst[ nxtn ][ nxtm ];
      Q.push( { nxtn , nxtm } );
    }
  }
  return INF;
}
void gogo( int ni , int nj , int nk ){
  for( int i = 0 ; i < 4 ; i ++ )
    cst[ ni ][ nj ][ nk ][ i ] = INF;
  if( not pos( ni , nj ) )
    return;
  vector< pair<int,int> > from;
  for( int k = 0 ; k < 2 ; k ++ ){
    int doti = ni + ddi[ nk ][ k ];
    int dotj = nj + ddj[ nk ][ k ];
    if( in( doti , dotj ) and
        c[ doti ][ dotj ] != '*' )
      from.push_back( { doti , dotj } );
  }
  if( from.size() < 2u )
    return;
  for( int i = 0 ; i < 4 ; i ++ ){
    if( nk == i )
      continue;
    vector< pair<int,int> > to;
    for( int k = 0 ; k < 2 ; k ++ ){
      int doti = ni + ddi[ i ][ k ];
      int dotj = nj + ddj[ i ][ k ];
      if( in( doti , dotj ) and
          c[ doti ][ dotj ] != '*' )
        to.push_back( { doti , dotj } );
    }
    if( to.size() < 2u )
      continue;
    int bst = INF;
    for( int _rr = 0 ; _rr < 2 ; _rr ++ ){
      int tcst = cost( ni , nj , from[ 0 ] , to[ 0 ] ) +
                 cost( ni , nj , from[ 1 ] , to[ 1 ] );
      bst = min( bst , tcst );
      reverse( to.begin() , to.end() );
    }
    cst[ ni ][ nj ][ nk ][ i ] = bst;
  }
}
int vvv[ N ][ N ][ 4 ] , vstmp;
void solve(){
  for( int i = 0 ; i + 1 < n ; i ++ )
    for( int j = 0 ; j + 1 < m ; j ++ )
      for( int k = 0 ; k < 4 ; k ++ ){
        dp[ i ][ j ][ k ] = INF;
        //for( int u = 0 ; u < 4 ; i ++ )
          //cst[ i ][ j ][ k ][ u ] = INF;
      }
  for( int i = 0 ; i + 1 < n ; i ++ )
    for( int j = 0 ; j + 1 < m ; j ++ )
      for( int k = 0 ; k < 4 ; k ++ )
        gogo( i , j , k );
  vector< pair<int,int> > from;
  int xn = -1 , xm = -1;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( c[ i ][ j ] == 'X' and xn == -1 )
        xn = i , xm = j;
      if( c[ i ][ j ] == '.' )
        from.push_back( { i , j } );
    }
  if( xn == 0 and xm == 0 ){
    puts( "0" );
    return;
  }
  for( int k = 0 ; k < 4 ; k ++ ){
    vector< pair<int,int> > to;
    for( int u = 0 ; u < 2 ; u ++ ){
      int doti = xn + ddi[ k ][ u ];
      int dotj = xm + ddj[ k ][ u ];
      if( in( doti , dotj ) and
          c[ doti ][ dotj ] != '*' )
        to.push_back( { doti , dotj } );
    }
    if( to.size() < 2u )
      continue;
    int bst = INF;
    for( int _rr = 0 ; _rr < 2 ; _rr ++ ){
      //printf( "%d %d -> %d %d : %d\n" , from[ 0 ].first , from[ 0 ].second ,
              //to[ 0 ].first , to[ 0 ].second , cost( xn , xm , from[ 0 ] , to[ 0 ] ) );
      //printf( "%d %d -> %d %d : %d\n" , from[ 1 ].first , from[ 1 ].second ,
              //to[ 1 ].first , to[ 1 ].second , cost( xn , xm , from[ 1 ] , to[ 1 ] ) );
      int tcst = cost( xn , xm , from[ 0 ] , to[ 0 ] ) +
                 cost( xn , xm , from[ 1 ] , to[ 1 ] );
      bst = min( bst , tcst );
      reverse( to.begin() , to.end() );
    }
    dp[ xn ][ xm ][ k ] = bst;
  }
  ++ vstmp;
  typedef pair<int, pair< pair<int,int>, int >> data;
  priority_queue< data , vector<data> , greater<data> > heap;
  for( int i = 0 ; i < 4 ; i ++ )
    if( dp[ xn ][ xm ][ i ] < INF ){
      heap.push( { dp[ xn ][ xm ][ i ] , { { xn , xm } , i } } );
      //printf( "%d %d %d : %d\n" , xn , xm , i , dp[ xn ][ xm ][ i ] );
    }
  while( heap.size() ){
    data td = heap.top(); heap.pop();
    int dd = td.first;
    int curn = td.second.first.first;
    int curm = td.second.first.second;
    int nk = td.second.second;
    if( vvv[ curn ][ curm ][ nk ] == vstmp )
      continue;
    vvv[ curn ][ curm ][ nk ] = vstmp;
    dp[ curn ][ curm ][ nk ] = dd;
    for( int i = 0 ; i < 4 ; i ++ ){
      if( vvv[ curn ][ curm ][ i ] == vstmp )
        continue;
      int tdp = dd + cst[ curn ][ curm ][ nk ][ i ];
      if( tdp >= INF )
        continue;
      heap.push( { tdp , { { curn , curm } , i } } );
    }
    int ton = curn , tom = curm , tok;
    int tdp = dp[ curn ][ curm ][ nk ] + 1;
    if( nk == 0 ) ton -- , tok = 2;
    if( nk == 1 ) tom -- , tok = 3;
    if( nk == 2 ) ton ++ , tok = 0;
    if( nk == 3 ) tom ++ , tok = 1;
    if( ton < 0 or ton + 1 >= n or
        tom < 0 or tom + 1 >= m )
      continue;
    if( vvv[ ton ][ tom ][ tok ] == vstmp )
      continue;
    heap.push( { tdp , { { ton , tom } , tok } } );
  }
  int ans = INF;
  for( int i = 2 ; i <= 3 ; i ++ ){
    if( vvv[ 0 ][ 0 ][ i ] != vstmp )
      continue;
    ans = min( ans , dp[ 0 ][ 0 ][ i ] );
  }
  if( ans >= INF ) ans = -1;
  printf( "%d\n" , ans );
}
int main(){
  while( init() )
    solve();
}
