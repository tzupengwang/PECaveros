#include <bits/stdc++.h>
using namespace std;
#define N 22
int d , asked;
int dn[]={1,0,-1,0};
int dm[]={0,1,0,-1};
int gar;
#ifdef eddy
int canright[ N ][ N ];
int candown[ N ][ N ];
int cn = 1 , cm = 1;
#endif
inline int invdir( int dir ){
  return dir ^ 2;
}
vector<int> his;
#ifdef eddy
inline bool run( int cdir ){
  bool ok = false;
  if( cdir == 0 )
    ok = candown[ cn + 1 ][ cm ];
  if( cdir == 2 )
    ok = candown[ cn ][ cm ];
  if( cdir == 1 )
    ok = canright[ cn ][ cm ];
  if( cdir == 3 )
    ok = canright[ cn ][ cm - 1 ];
  if( ok ){
    cn += dn[ cdir ];
    cm += dm[ cdir ];
  }
  //cerr << cn << " " << cm << endl;
  return ok;
}
#endif
int h , w;
char cdir[] = "NESW";
inline int walk( int dir ){
  char buf[ 128 ];
  ++ asked;
#ifdef eddy
  his.push_back( dir );
  if( asked <= d ) return -1;
  if( run( his[ asked - d - 1 ] ) )
    sprintf( buf , "yes" );
  else
    sprintf( buf , "no" );
  if( cn == h and cm == w )
    sprintf( buf , "success" );
#else 
  printf( "%c\n" , cdir[ dir ] );
  fflush( stdout );
  if( asked <= d ) return -1;
  scanf( "%s" , buf );
#endif
  if( buf[ 0 ] == 's' ){
    cerr << asked << endl;
    cerr << "AC!\n";
    exit(0);
  }
  if( gar ){
    gar --;
    return -1;
  }
  if( buf[ 0 ] == 'y' ) return 1;
  return 0;
}
bool in( int xn , int xm ){
  return 1 <= xn and xn <= h and
         1 <= xm and xm <= w;
}
bool gt[ N ][ N ];
int nown , nowm;
inline int dist( int xn , int xm ){
  return abs( xn - h ) + abs( xm - w );
}
bool cmp( int dir1 , int dir2 ){
  int nxtn1 = nown + dn[ dir1 ];
  int nxtm1 = nowm + dm[ dir1 ];
  int nxtn2 = nown + dn[ dir2 ];
  int nxtm2 = nowm + dm[ dir2 ];
  return dist( nxtn1 , nxtm1 ) <
         dist( nxtn2 , nxtm2 );
}
void gogo( int xn , int xm , int fdir , int sdir , int lst ){
  //cerr << "DFS at " << xn << " " << xm << endl;
  gt[ xn ][ xm ] = true;
  int ndir[ 4 ] = { 0 , 1 , 2 , 3 };
  nown = xn;
  nowm = xm;
  sort( ndir + 1 , ndir + 4 , cmp );
  for( int _ = 0 ; _ < 4 ; _ ++ ){
    //int dir = ( sdir + _ ) & 3;
    int dir = ( sdir + ndir[ _ ] ) & 3;
    int nxtn = xn + dn[ dir ];
    int nxtm = xm + dm[ dir ];
    if( not in( nxtn , nxtm ) ) continue;
    if( gt[ nxtn ][ nxtm ] ) continue;
    if( _ == 0 ){
      if( lst )
        gogo( nxtn , nxtm , fdir , sdir , lst - 1 );
      continue;
    }
    int ok = 0 , cnt = 0;
    while( true ){
      cnt ++;
      int ret = walk( dir );
      if( ret == 1 ) ok ++;
      if( ret == 0 ) break;
    }
    gar += cnt - ok - 1;
    if( ok == 0 ) continue;
    gogo( nxtn , nxtm , invdir( dir ) , dir , ok - 1 );
  }
  walk( fdir );
  if( d ) gar ++;
}
void go( int xn , int xm ){
  //cerr << "DFS at " << xn << " " << xm << endl;
  gt[ xn ][ xm ] = true;
  for( int dir = 0 ; dir < 4 ; dir ++ ){
    int nxtn = xn + dn[ dir ];
    int nxtm = xm + dm[ dir ];
    if( not in( nxtn , nxtm ) ) continue;
    if( gt[ nxtn ][ nxtm ] ) continue;
    int ok = 0 , cnt = 0;
    while( true ){
      int ret = walk( dir );
      cnt ++;
      if( ret == 1 ) ok ++;
      if( ret == 0 ) break;
    }
    //cerr << "At " << xn << " " << xm << " trying " << nxtn << " " << nxtm << " ok = " << ok << endl;
    gar += cnt - ok - 1;
    if( ok == 0 ) continue;
    gogo( nxtn , nxtm , invdir( dir ) , dir , ok - 1 );
  }
}
int main(){
  srand( 514 * 1021 );
  scanf( "%d%d%d" , &h , &w , &d );
#ifdef eddy
  int n = h , m = w;
  cerr << "Can right\n";
  for( int i = n ; i >= 1 ; i -- )
    for( int j = 1 ; j < m ; j ++ )
      cin >> canright[ i ][ j ];
  cerr << "Can Down\n";
  for( int i = n ; i >= 2 ; i -- )
    for( int j = 1 ; j <= m ; j ++ )
      cin >> candown[ i ][ j ];
#endif
  go( 1 , 1 );
  cerr << "WA\n";
}
