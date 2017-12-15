#include <bits/stdc++.h>
using namespace std;
#define N 52
int n , m;
char c[ N ][ N ];
bool ok[ N ][ N ][ N ][ N ];
int dir[ N ][ N ][ N ][ N ];
int dp[ N ][ N ][ N ][ N ];
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
char dc[6]="RLDU";
int si , sj , ti , tj;
inline bool in( int xi , int xj ){
  return 1 <= xi and xi <= n and
         1 <= xj and xj <= m;
}
int dp2[ N ][ N ];
pair<int,int> bk2[ N ][ N ];
bool gt2[ N ][ N ];
vector<string> vans;
string tmp;
void go( int xi , int xj , int yi , int yj ){
  if( xi == yi and xj == yj ) return;
  for( int d = 0 ; d < 4 ; d ++ ){
    int nxti = xi + di[ d ];
    int nxtj = xj + dj[ d ];
    if( nxti == yi and nxtj == yj ){
      tmp += dc[ d ];
      return;
    }
  }
  int nd = dir[ xi ][ xj ][ yi ][ yj ];
  tmp += dc[ nd ];
  int nxi = xi + di[ nd ];
  int nxj = xj + dj[ nd ];
  int nyi = yi + di[ nd ^ 1 ];
  int nyj = yj + dj[ nd ^ 1 ];
  go( nxi , nxj , nyi , nyj );
  tmp += dc[ nd ];
}
void build( int xi , int xj , int yi , int yj ){
  tmp = "";
  go( xi , xj , yi , yj );
  vans.push_back( tmp );
}
void solve(){
  queue< pair<int,int> > Q;
  gt2[ si ][ sj ] = true;
  Q.push( { si , sj } );
  while( Q.size() ){
    int xi , xj;
    tie( xi , xj ) = Q.front(); Q.pop();
    for( int ni = 1 ; ni <= n ; ni ++ )
      for( int nj = 1 ; nj <= m ; nj ++ ){
        if( not ok[ xi ][ xj ][ ni ][ nj ] ) continue;
        if( gt2[ ni ][ nj ] ) continue;
        gt2[ ni ][ nj ] = true;
        dp2[ ni ][ nj ] = dp2[ xi ][ xj ] + 1;
        bk2[ ni ][ nj ] = { xi , xj };
        Q.push( { ni , nj } );
      }
  }
  if( not gt2[ ti ][ tj ] ){
    puts( "-1" );
    exit(0);
  }
  while( ti != si or tj != sj ){
    build( bk2[ ti ][ tj ].first , bk2[ ti ][ tj ].second , 
           ti , tj );
    tie( ti , tj ) = bk2[ ti ][ tj ];
  }
  reverse( vans.begin() , vans.end() );
  printf( "%d\n" , (int)vans.size() );
  for( auto i : vans )
    printf( "%s\n" , i.c_str() );
}
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    for( int j = 1 ; j <= m ; j ++ )
      if( c[ i ][ j ] == 'S' )
        si = i , sj = j;
      else if( c[ i ][ j ] == 'F' )
        ti = i , tj = j;
  }
  queue< pair< pair<int,int> , pair<int,int > > > Q;
  for( int i = 1 ; i <= n ;  i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      if( c[ i ][ j ] == '#' ) continue;
      ok[ i ][ j ][ i ][ j ] = true;
      dir[ i ][ j ][ i ][ j ] = -1;
      dp[ i ][ j ][ i ][ j ] = 0;
      Q.push( { { i , j } , { i , j } } );
    }
  for( int i = 1 ; i <= n ;  i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      if( c[ i ][ j ] == '#' ) continue;
      for( int d = 0 ; d < 4 ; d ++ ){
        int nxti = i + di[ d ];
        int nxtj = j + dj[ d ];
        if( not in( nxti , nxtj ) ) continue;
        if( c[ nxti ][ nxtj ] == '#' ) continue;
        ok[ i ][ j ][ nxti ][ nxtj ] = true;
        dir[ i ][ j ][ nxti ][ nxtj ] = d;
        dp[ i ][ j ][ nxti ][ nxtj ] = 1;
        Q.push( { { i , j } , { nxti , nxtj } } );
      }
    }
  while( Q.size() ){
    int xi , xj , yi , yj;
    tie( xi , xj ) = Q.front().first;
    tie( yi , yj ) = Q.front().second;
    Q.pop();
    int ndp = dp[ xi ][ xj ][ yi ][ yj ] + 2;
    if( ndp > 100 ) continue;
    for( int d = 0 ; d < 4 ; d ++ ){
      int invd = d ^ 1;
      int nxi = xi + di[ invd ];
      int nxj = xj + dj[ invd ];
      int nyi = yi + di[ d ];
      int nyj = yj + dj[ d ];
      if( not in( nxi , nxj ) or c[ nxi ][ nxj ] == '#' ) continue;
      if( not in( nyi , nyj ) or c[ nyi ][ nyj ] == '#' ) continue;
      if( ok[ nxi ][ nxj ][ nyi ][ nyj ] ) continue;
      ok[ nxi ][ nxj ][ nyi ][ nyj ] = true;
      dir[ nxi ][ nxj ][ nyi ][ nyj ] = d;
      dp[ nxi ][ nxj ][ nyi ][ nyj ] = ndp;
      Q.push( { { nxi , nxj } , { nyi , nyj } } );
    }
  }
  solve();
}
