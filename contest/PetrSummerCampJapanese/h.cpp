#include <bits/stdc++.h>
using namespace std;
#define N 55
int n , m , en , em , sn , sm;
char c[ N ][ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    for( int j = 1 ; j <= m ; j ++ ){
      if( c[ i ][ j ] == '>' )
        en = i , em = j;
      if( c[ i ][ j ] == 'A' )
        sn = i , sm = j;
    }
  }
}
int ans;
bool got;
int dn[]={1,0,0,-1};
int dm[]={0,1,-1,0};
bool tag[ N ][ N ];
void go( int xn , int xm , int pt , int pdir ){
  if( pt >= ans ) return;
  if( xn == en && xm == em ){
    got = true;
    ans = pt;
    return;
  }
  if( tag[ xn ][ xm ] ) return;
  tag[ xn ][ xm ] = true;
  for( int i = 0 ; i < 4 ; i ++ ){
    if( pdir != -1 && pdir + i == 3 ) continue;
    if( pdir == i ) continue;
    if( pt >= ans ){
      tag[ xn ][ xm ] = false;
      return;
    }
    int in = xn - dn[ i ];
    int im = xm - dm[ i ];
    if( c[ in ][ im ] == '^' ) continue;
    if( c[ in ][ im ] == 'A' ) continue;
    if( c[ in ][ im ] == '>' ) continue;
    int npt = pt + 1;
    if( c[ in ][ im ] == '#' ) npt --;
    char sv = c[ in ][ im ];
    c[ in ][ im ] = '#';
    int nxtn = xn , nxtm = xm;
    bool can = true;
    while( true ){
      if( c[ nxtn ][ nxtm ] == '^' ){
        can = false;
        break;
      }
      if( c[ nxtn ][ nxtm ] == '>' ){
        if( npt < ans ){
          ans = npt;
          got = true;
        }
        can = false;
        break;
      }
      if( npt >= ans ) break;
      int nxtnxtn = nxtn + dn[ i ];
      int nxtnxtm = nxtm + dm[ i ];
      if( c[ nxtnxtn ][ nxtnxtm ] != 'A' &&
          c[ nxtnxtn ][ nxtnxtm ] != '>' &&
          c[ nxtnxtn ][ nxtnxtm ] != '^' ){
        int nnpt = npt + 1;
        if( c[ nxtnxtn ][ nxtnxtm ] == '#' ) nnpt --;
        char svv = c[ nxtnxtn ][ nxtnxtm ];
        c[ nxtnxtn ][ nxtnxtm ] = '#';
        go( nxtn , nxtm , nnpt , i );
        c[ nxtnxtn ][ nxtnxtm ] = svv;
      }
      if( c[ nxtnxtn ][ nxtnxtm ] == '#' )
        break;
      nxtn = nxtnxtn;
      nxtm = nxtnxtm;
    }
    if( can ){
      go( nxtn , nxtm , npt , i );
    }
    c[ in ][ im ] = sv;
  }
  tag[ xn ][ xm ] = false;
}
void solve(){
  got = false;
  for( int i = 0 ; i < 10 ; i ++ ){
    ans = i + 1;
    go( sn , sm , 0 , -1 );
    if( got ){
      printf( "%d\n" , i );
      return;
    }
  }
  printf( "%d\n" , 10 );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
