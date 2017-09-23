#include <bits/stdc++.h>
using namespace std;
#define N 111
#define X first
#define Y second
int n;
vector< pair<int,int> > v;
bool ok[ N ][ N ][ N ];
int fr[ N ][ N ][ N ];
int fi[ N ][ N ][ N ];
int fj[ N ][ N ][ N ];
tuple<int,int,int> lst[ N ] , st[ N ];
tuple<int,int,int> cst[ N ][ N ];
map< pair<int,int> , int > idx;
bool okk[ N ][ N ];
bool oks[ N ] , okt[ N ];
int main(){
#ifdef ONLINE_JUDGE
  freopen( "division.in" , "r" , stdin );
  freopen( "division.out" , "w" , stdout );
#endif
  cin >> n;
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ ){
    cin >> v[ i ].X >> v[ i ].Y;
    idx[ v[ i ] ] = i + 1;
  }
  assert( (int)idx.size() == n );
  sort( v.begin() , v.end() );
  for( int i = 0 ; i < n ; i ++ ){
    int up = 0 , on = 0 , dn = 0;
    for( int j = 0 ; j < n ; j ++ ){
      if( v[ j ].X < v[ i ].X )
        continue;
      if( v[ j ].Y > v[ i ].Y ) up ++;
      else if( v[ j ].Y < v[ i ].Y ) dn ++;
      else on ++;
    }
    if( on > 1 ) continue;
    okt[ i ] = true;
    lst[ i ] = make_tuple( up , on , dn );
  }
  for( int i = 0 ; i < n ; i ++ ){
    int up = 0 , on = 0 , dn = 0;
    for( int j = 0 ; j < n ; j ++ ){
      if( v[ j ].X >= v[ i ].X )
        continue;
      if( v[ j ].Y > v[ i ].Y ) up ++;
      else if( v[ j ].Y < v[ i ].Y ) dn ++;
      else on ++;
    }
    if( on > 0 ) continue;
    oks[ i ] = true;
    st[ i ] = make_tuple( up , on , dn );
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i ; j < n ; j ++ ){
      if( v[ j ].X == v[ i ].X ) continue;
      int up = 0 , on = 0 , dn = 0;
      int dx = v[ j ].X - v[ i ].X;
      int dy = v[ j ].Y - v[ i ].Y;
      // yy = ( x - v[ i ].X ) / dx * dy
      for( int k = 0 ; k < n ; k ++ ){
        if( v[ k ].X < v[ i ].X or
            v[ k ].X >= v[ j ].X ) continue;
        int yy = ( v[ k ].X - v[ i ].X ) * dy + v[ i ].Y * dx;
        int y2 = v[ k ].Y * dx;
        if( y2 > yy ) up ++;
        else if( y2 < yy ) dn ++;
        else on ++;
      }
      if( on > 1 ) continue;
      okk[ i ][ j ] = true;
      cst[ i ][ j ] = make_tuple( up , on , dn );
    }
  int ans = n + n , ai = 0 , aj = 0 , ak = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( not oks[ i ] ) continue;
    ok[ i ][ get<0>( st[ i ] ) ][ get<1>( st[ i ] ) ] = true;
    fr[ i ][ get<0>( st[ i ] ) ][ get<1>( st[ i ] ) ] = -1;
    fi[ i ][ get<0>( st[ i ] ) ][ get<1>( st[ i ] ) ] = -1;
    fj[ i ][ get<0>( st[ i ] ) ][ get<1>( st[ i ] ) ] = -1;
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= n ; j ++ )
      for( int k = 0 ; k <= n ; k ++ ){
        if( not ok[ i ][ j ][ k ] ) continue;
        for( int ii = i + 1 ; ii < n ; ii ++ ){
          if( v[ ii ].X == v[ i ].X )
            continue;
          if( not okk[ i ][ ii ] )
            continue;
          int nj = j + get<0>( cst[ i ][ ii ] );
          int nk = k + get<1>( cst[ i ][ ii ] );
          if( ok[ ii ][ nj ][ nk ] ) continue;
          ok[ ii ][ nj ][ nk ] = true;
          fr[ ii ][ nj ][ nk ] = i;
          fi[ ii ][ nj ][ nk ] = j;
          fj[ ii ][ nj ][ nk ] = k;
        }
        if( not okt[ i ] ) continue;
        int upp = j + get<0>( lst[ i ] );
        int onn = k + get<1>( lst[ i ] );
        int dnn = n - upp - onn;
        if( max( upp , max( onn , dnn ) ) -
            min( upp , min( onn , dnn ) ) < ans ){
          ans = max( upp , max( onn , dnn ) ) -
                min( upp , min( onn , dnn ) );
          ai = i;
          aj = j;
          ak = k;
        }
      }
  vector<int> va;
  while( ai >= 0 ){
    va.push_back( idx[ v[ ai ] ] );
    int ni = fr[ ai ][ aj ][ ak ];
    int nj = fi[ ai ][ aj ][ ak ];
    int nk = fj[ ai ][ aj ][ ak ];
    ai = ni;
    aj = nj;
    ak = nk;
  }
  reverse( va.begin() , va.end() );
  if( va.empty() ) va.push_back( 1 );
  printf( "%d\n" , (int)va.size() );
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
