#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define x1 x1fjkl
#define y1 y1fjkl
#define x2 x2fjkl
#define y2 y2fjkl
#define N 111
LL Ceil( LL x , LL y ){
  LL ret = x / y;
  if( ret * y < x ) ret ++;
  return ret;
}
LL Floor( LL x , LL y ){
  return x / y;
}
LL n , x[ N ] , y[ N ];
// (x1 - x2) ( y1 (2 x1 + x2) + y2 (2 x2 + x1) ) / -6
LL liG( LL xx ){ // test (xx, 0)
  LL sum = 0;
  for( int i = 0 ; i < n ; i ++ ){
    LL x1 = x[ i     ] - xx , y1 = y[ i     ];
    LL x2 = x[ i + 1 ] - xx , y2 = y[ i + 1 ];
    LL tmp = (x1 - x2) * (y1 * (x1 + x1 + x2) + y2 * (x2 + x2 + x1));
    sum += tmp;
  }
  return sum;
}
void unstable(){
  puts( "unstable" );
  exit(0);
}
const LL inf9 = 1e9;
const LL inf = inf9 * inf9;
void go( LL lx , LL rx , LL nx , LL ny ){
  LL lb = 0 , rb = inf;
  {
    LL T = -liG( rx ); // should /= 6
    if( nx > rx ){
      if( T >= 0 ) unstable();
      else rb = min( rb , Ceil( abs(T) , (6LL * abs(nx - rx)) ) );
    }else if( nx == rx ){
      if( T > 0 ) unstable();
    }else{
      if( T >= 0 )
        lb = max( lb , Floor( T , 6LL * abs(nx - rx) ) );
    }
  }
  {
    LL T = -liG( lx ); // should /= 6
    if( nx > lx ){
      if( T <= 0 )
        lb = max( lb , Floor( abs(T) , 6LL * abs(nx - lx) ) );
    }else if( nx == lx ){
      if( T < 0 ) unstable();
    }else{
      if( T <= 0 ) unstable();
      else rb = min( rb , Ceil( abs(T) , (6LL * abs(nx - lx)) ) );
    }
  }
  if( lb > rb ) unstable();
  else if( rb == inf ) printf( "%lld .. inf\n" , lb );
  else printf( "%lld .. %lld\n" , lb , rb );
}
int main(){
  vector<LL> cx;
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> x[ i ] >> y[ i ];
    if( y[ i ] == 0 )
      cx.push_back( x[ i ] );
  }
  x[ n ] = x[ 0 ];
  y[ n ] = y[ 0 ];
  LL area = 0;
  for( int i = 0 ; i < n ; i ++ )
    area += x[ i ] * y[ i + 1 ] - x[ i + 1 ] * y[ i ];
  if( area > 0 ){
    reverse( x + 1 , x + n );
    reverse( y + 1 , y + n );
  }
  sort( cx.begin() , cx.end() );
  go( cx[ 0 ] , cx.back() , x[ 0 ] , y[ 0 ] );
}
