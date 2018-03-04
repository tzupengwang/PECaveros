#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 300
#define K 1024
int X , Y;
char buf[ K ];
int cmd , x , y , w , h;
int windows;
int xi[ N ] , yi[ N ] , wi[ N ] , hi[ N ];
bool closed[ N ];
int sgn( int _ ){
  return (_ > 0) - (_ < 0);
}
void not_fit( const char* command ){
  printf( "Command %d: %s - window does not fit\n" , cmd , command );
}
void no_window( const char* command ){
  printf( "Command %d: %s - no window at given position\n" , cmd , command );
}
void OPEN(){
  if( x < 0 or x + w > X or
      y < 0 or y + h > Y ){
    not_fit( "OPEN" );
    return;
  }
  for( int i = 0 ; i < windows ; i ++ ){
    if( closed[ i ] ) continue;
    int lx = max( x , xi[ i ] );
    int rx = min( x + w , xi[ i ] + wi[ i ] );
    int ly = max( y , yi[ i ] );
    int ry = min( y + h , yi[ i ] + hi[ i ] );
    if( (LL)max( 0 , rx - lx ) * (LL)max( 0 , ry - ly ) > 0 ){
      not_fit( "OPEN" );
      return;
    }
  }
  xi[ windows ] = x;
  yi[ windows ] = y;
  wi[ windows ] = w;
  hi[ windows ] = h;
  windows ++;
}
void CLOSE(){
  for( int i = 0 ; i < windows ; i ++ ){
    if( closed[ i ] ) continue;
    if( xi[ i ] <= x and x < xi[ i ] + wi[ i ] and
        yi[ i ] <= y and y < yi[ i ] + hi[ i ] ){
      closed[ i ] = true;
      return;
    }
  }
  no_window( "CLOSE" );
}
void go_resize( int cur ){
  if( xi[ cur ] < 0 or xi[ cur ] + w > X or
      yi[ cur ] < 0 or yi[ cur ] + h > Y ){
    not_fit( "RESIZE" );
    return;
  }
  for( int i = 0 ; i < windows ; i ++ ){
    if( closed[ i ] or i == cur ) continue;
    int lx = max( xi[ cur ] , xi[ i ] );
    int rx = min( xi[ cur ] + w , xi[ i ] + wi[ i ] );
    int ly = max( yi[ cur ] , yi[ i ] );
    int ry = min( yi[ cur ] + h , yi[ i ] + hi[ i ] );
    if( (LL)max( 0 , rx - lx ) * (LL)max( 0 , ry - ly ) > 0 ){
      not_fit( "RESIZE" );
      return;
    }
  }
  wi[ cur ] = w;
  hi[ cur ] = h;
}
void RESIZE(){
  for( int i = 0 ; i < windows ; i ++ ){
    if( closed[ i ] ) continue;
    if( xi[ i ] <= x and x < xi[ i ] + wi[ i ] and
        yi[ i ] <= y and y < yi[ i ] + hi[ i ] ){
      go_resize( i );
      return;
    }
  }
  no_window( "RESIZE" );
}
// move (dx, dy)
int moving[ N ] , stmp;
void go_move( int cur ){
  ++ stmp;
  moving[ cur ] = stmp;
  vector<int> cand = {cur};
  int dx = w , dy = h;
  int movedx = 0;
  int movedy = 0;
  while( true ){
    int atmstdx = abs( dx ) - movedx;
    int atmstdy = abs( dy ) - movedy;
    for( int i : cand ){
      if( dx > 0 ) atmstdx = min( atmstdx , X - (xi[i] + wi[i]) );
      if( dx < 0 ) atmstdx = min( atmstdx , xi[i] );
      if( dy > 0 ) atmstdy = min( atmstdy , Y - (yi[i] + hi[i]) );
      if( dy < 0 ) atmstdy = min( atmstdy , yi[i] );
      if( atmstdx == 0 and atmstdy == 0 ) break;
      for( int j = 0 ; j < windows ; j ++ ){
        if( closed[ j ] or moving[ j ] == stmp ) continue;
        if( dx ){
          int ly = max(yi[ i ], yi[ j ]);
          int ry = min(yi[ i ] + hi[ i ],
                       yi[ j ] + hi[ j ]);
          if( ly < ry ){
            if( dx > 0 ){
              if( xi[ i ] + wi[ i ] <= xi[ j ] )
                atmstdx = min( atmstdx , xi[ j ] - (xi[ i ] + wi[ i ]) );
            }else{
              if( xi[ i ] >= xi[ j ] + wi[ j ] )
                atmstdx = min( atmstdx , xi[ i ] - (xi[ j ] + wi[ j ]) );
            }
          }
        }else{
          int lx = max(xi[ i ], xi[ j ]);
          int rx = min(xi[ i ] + wi[ i ],
                       xi[ j ] + wi[ j ]);
          if( lx < rx ){
            if( dy > 0 ){
              if( yi[ i ] + hi[ i ] <= yi[ j ] )
                atmstdy = min( atmstdy , yi[ j ] - (yi[ i ] + hi[ i ]) );
            }else{
              if( yi[ j ] + hi[ j ] <= yi[ i ] )
                atmstdy = min( atmstdy , yi[ i ] - (yi[ j ] + hi[ j ]) );
            }
          }
        }
      }
      if( atmstdx == 0 and atmstdy == 0 ) break;
    }
    bool keep = (atmstdx > 0) or (atmstdy > 0);
    for( int i : cand ){
      xi[ i ] += atmstdx * sgn( dx );
      yi[ i ] += atmstdy * sgn( dy );
    }
    movedx += atmstdx;
    movedy += atmstdy;
    size_t csz = cand.size();
    for( size_t _ = 0 ; _ < csz ; _ ++ ){
      int i = cand[ _ ];
      for( int j = 0 ; j < windows ; j ++ ){
        if( closed[ j ] or moving[ j ] == stmp ) continue;
        if( dx ){
          int ly = max(yi[ i ], yi[ j ]);
          int ry = min(yi[ i ] + hi[ i ],
                       yi[ j ] + hi[ j ]);
          if( ly < ry ){
            if( dx > 0 ){
              if( xi[ i ] + wi[ i ] == xi[ j ] ){
                moving[ j ] = stmp;
                cand.push_back( j );
                keep = true;
              }
            }else{
              if( xi[ i ] == xi[ j ] + wi[ j ] ){
                moving[ j ] = stmp;
                cand.push_back( j );
                keep = true;
              }
            }
          }
        }else{
          int lx = max(xi[ i ], xi[ j ]);
          int rx = min(xi[ i ] + wi[ i ],
                       xi[ j ] + wi[ j ]);
          if( lx < rx ){
            if( dy > 0 ){
              if( yi[ i ] + hi[ i ] == yi[ j ] ){
                moving[ j ] = stmp;
                cand.push_back( j );
                keep = true;
              }
            }else{
              if( yi[ j ] + hi[ j ] == yi[ i ] ){
                moving[ j ] = stmp;
                cand.push_back( j );
                keep = true;
              }
            }
          }
        }
      }
    }
    if( not keep ) break;
  }
  if( movedx + movedy < abs(dx) + abs(dy) )
    printf( "Command %d: MOVE - moved %d instead of %d\n" , 
            cmd , movedx + movedy , abs(dx) + abs(dy) );
}
void MOVE(){
  for( int i = 0 ; i < windows ; i ++ ){
    if( closed[ i ] ) continue;
    if( xi[ i ] <= x and x < xi[ i ] + wi[ i ] and
        yi[ i ] <= y and y < yi[ i ] + hi[ i ] ){
      go_move( i );
      return;
    }
  }
  no_window( "MOVE" ); 
}
void print_info(){
  int nwindows = 0;
  for( int i = 0 ; i < windows ; i ++ )
    if( not closed[ i ] )
      nwindows ++;
  printf( "%d window(s):\n" , nwindows );
  for( int i = 0 ; i < windows ; i ++ )
    if( not closed[ i ] )
      printf( "%d %d %d %d\n" , xi[ i ] , yi[ i ] , wi[ i ] , hi[ i ] );
}
int main(){
  scanf( "%d%d" , &X , &Y );
  fgets( buf , K , stdin );
  while( fgets( buf , K , stdin ) ){
    ++ cmd;
    if( sscanf( buf , "OPEN %d %d %d %d" , &x , &y , &w , &h ) == 4 )
      OPEN();
    else if( sscanf( buf , "CLOSE %d %d" , &x , &y ) == 2 )
      CLOSE();
    else if( sscanf( buf , "RESIZE %d %d %d %d" , &x , &y , &w , &h ) == 4 )
      RESIZE();
    else if( sscanf( buf , "MOVE %d %d %d %d" , &x , &y , &w , &h ) == 4 )
      MOVE();
    else
      assert( false );
    //print_info();
    //puts( "======" );
  }
  print_info();
}
