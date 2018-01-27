#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define K 25
int read_dir(){
  char buf[ 16 ];
  scanf( "%s" , buf );
  return (buf[ 1 ] - 'x') * 2 + (buf[ 0 ] == '-');
}
int dx[]={1,-1,0,0,0,0};
int dy[]={0,0,1,-1,0,0};
int dz[]={0,0,0,0,1,-1};
int X , Y , Z;
int sX , sY , sZ , sdir;
int tX , tY , tZ , tdir;
void init(){
  cin >> Y >> Z;
  cin >> sX >> sY >> sZ;
  sdir = read_dir();
  sX -= dx[ sdir ];
  sY -= dy[ sdir ];
  sZ -= dz[ sdir ];
  cin >> tX >> tY >> tZ;
  tdir = read_dir();
  //printf( "sX = %d, sY = %d, sZ = %d, sdir = %d\n" , sX , sY , sZ , sdir );
  //printf( "tX = %d, tY = %d, tZ = %d, tdir = %d\n" , tX , tY , tZ , tdir );
}

bool wtf(){
  if( 1 <= sX and sX <= X and
      1 <= sY and sY <= Y and
      1 <= sZ and sZ <= Z )
    return true;
  int ttX = tX + dx[ tdir ];
  int ttY = tY + dy[ tdir ];
  int ttZ = tZ + dz[ tdir ];
  if( 1 <= ttX and ttX <= X and
      1 <= ttY and ttY <= Y and
      1 <= ttZ and ttZ <= Z )
    return true;
  return false;
}

int bnd , _cs;
bool gt;
bool used[ K ][ K ][ K ];
bool okay( int uX , int uY , int uZ ){
  if( uX < 1 or uX > X ) return false;
  if( uY < 1 or uY > Y ) return false;
  if( uZ < 1 or uZ > Z ) return false;
  if( used[ uX ][ uY ][ uZ ] ) return false;
  return true;
}

void go( int nX , int nY , int nZ , int ndir , int dep ){
  if( nX == tX and nY == tY and nZ == tZ and ndir == tdir ){
    gt = true;
    return;
  }
  int dd = abs(nX - tX) + abs(nY - tY) + abs(nZ - tZ);
  dd = (dd + 3) / 4;
  if( dep + dd >= bnd ) return;
  for( int ln = 1 ; ln <= 2 ; ln ++ ){
    for( int nxtdir = 0 ; nxtdir < 6 ; nxtdir ++ ){
      if( nxtdir / 2 == ndir / 2 ) continue;
      int hisln = 3 - ln;

      //printf( "trying %d %d\n" , ln , nxtdir );
      bool ok = true;
      {
        int nxtX = nX , nxtY = nY , nxtZ = nZ;
        for( int i = 0 ; i <= ln and ok ; i ++ ){
          nxtX += dx[ ndir ];
          nxtY += dy[ ndir ];
          nxtZ += dz[ ndir ];
          if( not okay( nxtX , nxtY , nxtZ ) )
            ok = false;
        }
        for( int i = 0 ; i < hisln and ok ; i ++ ){
          nxtX += dx[ nxtdir ];
          nxtY += dy[ nxtdir ];
          nxtZ += dz[ nxtdir ];
          if( not okay( nxtX , nxtY , nxtZ ) )
            ok = false;
        }
      }
      if( not ok ) continue;
      int lstX , lstY , lstZ;
      {
        int nxtX = nX , nxtY = nY , nxtZ = nZ;
        for( int i = 0 ; i <= ln and ok ; i ++ ){
          nxtX += dx[ ndir ];
          nxtY += dy[ ndir ];
          nxtZ += dz[ ndir ];
          used[ nxtX ][ nxtY ][ nxtZ ] = true;
        }
        for( int i = 0 ; i < hisln and ok ; i ++ ){
          nxtX += dx[ nxtdir ];
          nxtY += dy[ nxtdir ];
          nxtZ += dz[ nxtdir ];
          used[ nxtX ][ nxtY ][ nxtZ ] = true;
        }
        lstX = nxtX;
        lstY = nxtY;
        lstZ = nxtZ;
      }
      go( lstX , lstY , lstZ , nxtdir , dep + 1 );
      {
        int nxtX = nX , nxtY = nY , nxtZ = nZ;
        for( int i = 0 ; i <= ln and ok ; i ++ ){
          nxtX += dx[ ndir ];
          nxtY += dy[ ndir ];
          nxtZ += dz[ ndir ];
          used[ nxtX ][ nxtY ][ nxtZ ] = false;
        }
        for( int i = 0 ; i < hisln and ok ; i ++ ){
          nxtX += dx[ nxtdir ];
          nxtY += dy[ nxtdir ];
          nxtZ += dz[ nxtdir ];
          used[ nxtX ][ nxtY ][ nxtZ ] = false;
        }
      }
      if( gt ) return;
    }
  }
}
void solve(){
  printf( "Case %d: " , ++ _cs );
  if( wtf() ){
    puts( "Impossible" );
    return;
  }
  int atleast = abs(sX - tX) + abs(sY - tY) + abs(sZ - tZ);
  atleast = (atleast + 3) / 4;
  for( int _ = atleast + 1 ; _ <= 7 ; _ ++ ){
    bnd = _;
    gt = false;
    go( sX , sY , sZ , sdir , 0 );
    if( gt ){
      printf( "%d\n" , _ - 1 );
      return;
    }
  }
  puts( "Impossible" );
}
int main(){
  while( cin >> X and X ){
    init();
    solve();
  }
}
