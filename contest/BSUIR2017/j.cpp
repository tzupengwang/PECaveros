#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int inf = 100000;
typedef LL type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
bool operator==( const Pt& p1 , const Pt& p2 ){
  return p1.X == p2.X and p1.Y == p2.Y;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
inline int ask( const Pt& p1 , const Pt& p2 ){
  printf( "Q %lld %lld %lld %lld\n" ,
          p1.X , p1.Y , p2.X , p2.Y );
  fflush( stdout );
  char ret[ 9 ]; scanf( "%s" , ret );
  if( ret[ 0 ] == 'X' ) return 0;
  if( ret[ 0 ] == '+' ) return 1;
  if( ret[ 0 ] == '-' ) return -1;
  assert( false );
  return -2;
}
void answer( const vector<Pt>& pp ){
  printf( "A" );
  for( auto i : pp )
    printf( " %lld %lld" , i.X , i.Y );
  puts( "" );
  fflush( stdout );
  exit(0);
}
int lx , rx , ly , ry;
bool gt[ 4 ];
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 ,bool& res){
	LL f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	LL f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	LL f = ( f1 + f2 );
  if( f == 0 ){
    res = false;
    return p1;
  }
  res = true;
  LL tmpx = ( q1.X * f2 + q2.X * f1 ) / f;
  LL tmpy = ( q1.Y * f2 + q2.Y * f1 ) / f;
  if( tmpy * f < ( q1.Y * f2 + q2.Y * f1 ) )
    tmpy ++;
  return { tmpx , tmpy };
}
void gogo( int ord1 , int ord2 ){
  Pt dlt = { 1 , 0 };
  Pt p1 , p2;
  if( ord1 == 0 ){
    p1 = { lx , ly };
    p2 = { rx , ry };
  }else{
    p1 = { lx , ry };
    p2 = { rx , ly };
  }
  if( ask( p1 + dlt , p2 + dlt ) != 0 ){
    dlt.X = -dlt.X;
    dlt.Y = -dlt.Y;
  }
  int ba1 = 0 , ba2 = 1 , ba3 = 1;
  int ba4 = 2 , ba5 = 2;
  {
    int bl = 1 , br = 2e5;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( ask( p1 + dlt * bmid , p2 + dlt * bmid ) == 0 )
        ba1 = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    int bl = 1 , br = 2e5;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( ask( p1 + dlt * bmid , p2 + dlt * ( bmid - 1 ) ) == 0 )
        ba2 = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    int bl = 1 , br = 2e5;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( ask( p1 + dlt * ( bmid - 1 ) , p2 + dlt * bmid ) == 0 )
        ba3 = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    int bl = 2 , br = 2e5;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( ask( p1 + dlt * bmid , p2 + dlt * ( bmid - 2 ) ) == 0 )
        ba4 = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    int bl = 2 , br = 2e5;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( ask( p1 + dlt * ( bmid - 2 ) , p2 + dlt * bmid ) == 0 )
        ba5 = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  for( int i = lx ; i <= rx ; i ++ ){
    bool res = true;
    Pt ret1 = interPnt( { i , 0 } , { i , 1 } ,
                        p1 + dlt * ba1 ,
                        p2 + dlt * ba1 , res );
    if( not res ) continue;
    Pt ret2 = interPnt( { i , 0 } , { i , 1 } ,
                        p1 + dlt * ba2 ,
                        p2 + dlt * ( ba2 - 1 ) , res );
    if( not res ) continue;
    if( !( ret1 == ret2 ) ) continue;
    Pt ret3 = interPnt( { i , 0 } , { i , 1 } ,
                        p1 + dlt * ( ba3 - 1 ) ,
                        p2 + dlt * ba3 , res );
    if( not res ) continue;
    if( !( ret1 == ret3 ) ) continue;
    Pt ret4 = interPnt( { i , 0 } , { i , 1 } ,
                        p1 + dlt * ( ba4 - 0 ) ,
                        p2 + dlt * ( ba4 - 2 ), res );
    if( not res ) continue;
    if( !( ret1 == ret4 ) ) continue;
    Pt ret5 = interPnt( { i , 0 } , { i , 1 } ,
                        p1 + dlt * ( ba5 - 2 ) ,
                        p2 + dlt * ( ba5 - 0 ) , res );
    if( not res ) continue;
    if( !( ret1 == ret5 ) ) continue;
    if( ret1 == p1 ) continue;
    if( ret1 == p2 ) continue;
    answer( { p1 , p2 , ret1 } );
  }
  assert( false );
}
Pt find_ans( const Pt& o , const Pt& p1 , const Pt& dlt1 , LL dl1 , int tar1 ){
  Pt to = o - dlt1;
  LL bl = 0 , br = dl1 , ba = 0;
  while( bl <= br ){
    LL bmid = (bl + br) >> 1;
    Pt tmp = p1 + dlt1 * bmid;
    if( ask( to , tmp ) == tar1 )
      ba = bmid + 1 , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  return p1 + dlt1 * ba;
}
void go( const Pt& o , const Pt& p1 , const Pt& dlt1 , LL dl1 , int tar1 ,
                       const Pt& p2 , const Pt& dlt2 , LL dl2 , int tar2 ){
  vector<Pt> ans;
  ans.push_back( o );
  ans.push_back( find_ans( o , p1 , dlt1 , dl1 , tar1 ) );
  ans.push_back( find_ans( o , p2 , dlt2 , dl2 , tar2 ) );
  answer( ans );
  exit(0);
}
void gogogo(){
  fprintf( stderr , "lx = %d, rx = %d, ly = %d, ry = %d\n" ,
           lx , rx , ly , ry );
  {
    if( ask( { lx , ly } , { lx + 1 , ly - 1 } ) == 0 )
      gt[ 0 ] = true;
  }
  {
    if( ask( { rx , ly } , { rx + 1 , ly + 1 } ) == 0 )
      gt[ 1 ] = true;
  }
  {
    if( ask( { rx , ry } , { rx + 1 , ry - 1 } ) == 0 )
      gt[ 2 ] = true;
  }
  {
    if( ask( { lx , ry } , { lx + 1 , ry + 1 } ) == 0 )
      gt[ 3 ] = true;
  }
  if( gt[ 0 ] and gt[ 2 ] )
    gogo( 0 , 2 );
  if( gt[ 1 ] and gt[ 3 ] )
    gogo( 1 , 3 );
  if( gt[ 0 ] )
    go( { lx , ly } , { rx , ly } , { 0 , 1 } , ry - ly , -1
                    , { lx , ry } , { 1 , 0 } , rx - lx , +1 );
  if( gt[ 1 ] )
    go( { rx , ly } , { rx , ry } , { -1 , 0 } , rx - lx , -1
                    , { lx , ly } , { 0 , 1 } , ry - ly , +1 );
  if( gt[ 2 ] )
    go( { rx , ry } , { lx , ry } , { 0 , -1 } , ry - ly , -1
                    , { rx , ly } , { -1 , 0 } , rx - lx , +1 );
  if( gt[ 3 ] )
    go( { lx , ry } , { rx , ry } , { 0 , -1 } , ry - ly , +1
                    , { lx , ly } , { 1 , 0 } , rx - lx , -1 );
  assert( false );
}
int main(){
  {
    lx = -inf;
    int bl = -inf , br = inf;
    while( bl <= br ){
      int bmid = (bl + br) / 2;
      if( ask( { bmid , 0 } , { bmid , 1 } ) > 0 )
        lx = bmid + 1 , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    rx = inf;
    int bl = -inf , br = inf;
    while( bl <= br ){
      int bmid = (bl + br) / 2;
      if( ask( { bmid , 0 } , { bmid , 1 } ) < 0 )
        rx = bmid - 1 , br = bmid - 1;
      else
        bl = bmid + 1;
    }
  }
  {
    ly = -inf;
    int bl = -inf , br = inf;
    while( bl <= br ){
      int bmid = (bl + br) / 2;
      if( ask( { 0 , bmid } , { 1 , bmid } ) < 0 )
        ly = bmid + 1 , bl = bmid + 1;
      else
        br = bmid - 1;
    }
  }
  {
    ry = inf;
    int bl = -inf , br = inf;
    while( bl <= br ){
      int bmid = (bl + br) / 2;
      if( ask( { 0 , bmid } , { 1 , bmid } ) > 0 )
        ry = bmid - 1 , br = bmid - 1;
      else
        bl = bmid + 1;
    }
  }
  gogogo();
}
