#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 222
struct DJS{
  int p[ N * N * 2 ];
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    //printf( "Uni %d %d\n" , x , y );
    p[ f( x ) ] = f( y );
  }
} djs;
inline int id( int i , int j ){
  return i * N + j;
}
int n , m;
char buf[ N ];
bool black[ N ][ N ] , vst[ N ][ N ];
inline int dec( char ctmp ){
  if( '0' <= ctmp and ctmp <= '9' ) return ctmp - '0';
  return ctmp - 'a' + 10;
}
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , buf + 1 );
    for( int j = 1 ; j <= m * 4 ; j ++ ){
      black[ i ][ j ] = false;
      vst[ i ][ j ] = false;
    }
    for( int j = 1 ; j <= m ; j ++ ){
      int vl = dec( buf[ j ] );
      for( int k = 0 ; k < 4 ; k ++ )
        if( (vl >> k) & 1 )
          black[ i ][ j * 4 - k ] = true;
    }
  }
}
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
bool in( int ni , int nj ){
  return 1 <= ni and ni <= n and
         1 <= nj and nj <= m;
}
string ans;
int cand[ N * N * 2 ] , ct;
int tag[ N ][ N ] , stmp;
void add( int ni , int nj ){
  if( tag[ ni ][ nj ] == stmp ) return;
  //printf( "%d %d, id = %d\n" , ni , nj , id( ni , nj ) );
  tag[ ni ][ nj ] = stmp;
  djs.p[ id( ni , nj ) ] = id( ni , nj );
  cand[ ct ++ ] = id( ni , nj );
}
void go( int ni , int nj ){
  //for( int i = 0 ; i < 2 ; i ++ )
    //for( int j = 0 ; j < 2 ; j ++ )
      //add( ni + i , nj + j );
  vst[ ni ][ nj ] = true;
  for( int dir = 0 ; dir < 4 ; dir ++ ){
    int nxti = ni + di[ dir ];
    int nxtj = nj + dj[ dir ];
    if( not in( nxti , nxtj ) or
        not black[ nxti ][ nxtj ] ){
      if( dir == 0 ){
        add( ni , nj + 1 ); add( ni + 1 , nj + 1 );
        djs.uni( id( ni , nj + 1 ) , id( ni + 1 , nj + 1 ) );
      }
      if( dir == 1 ){
        add( ni , nj ); add( ni + 1 , nj );
        djs.uni( id( ni , nj ) , id( ni + 1 , nj ) );
      }
      if( dir == 2 ){
        add( ni + 1 , nj ); add( ni + 1 , nj + 1 );
        djs.uni( id( ni + 1 , nj ) , id( ni + 1 , nj + 1 ) );
      }
      if( dir == 3 ){
        add( ni , nj ); add( ni , nj + 1 );
        djs.uni( id( ni , nj ) , id( ni , nj + 1 ) );
      }
      continue;
    }
    if( not in( nxti , nxtj ) or
        not black[ nxti ][ nxtj ] )
      continue;
    if( vst[ nxti ][ nxtj ] )
      continue;
    go( nxti , nxtj );
  }
}
char cans[] = "GWAKJSD";
int _cs;
void solve(){
  ans = "";
  m *= 4;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      if( not vst[ i ][ j ] and black[ i ][ j ] ){
        ++ stmp;
        ct = 0;
        go( i , j );
        int cnt = 0;
        for( int k = 0 ; k < ct ; k ++ )
          if( djs.f( cand[ k ] ) == cand[ k ] )
            cnt ++;
        ans += cans[ cnt ];
      }
  sort( ans.begin() , ans.end() );
  printf( "Case %d: %s\n" , ++ _cs , ans.c_str() );
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 and n ) {
    init();
    solve();
  }
}
