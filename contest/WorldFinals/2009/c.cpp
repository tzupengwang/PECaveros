#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define double long double
const double pi = acosl( -1. );
const double nn = sqrt( 50. );
const double eps = 1e-9;
int sgn( double x ){
  return x > -eps ? 1 : -1; 
}
bool equal( double x , double y ){
  return x - eps < y and y < x + eps;
}
double myacos( double vl ){
  return acosl( max( -1.L , min( 1.L , vl ) ) );
}
int sgnx[ 8 ] , sgny[ 8 ] , sgnz[ 8 ];
struct Pt{
  double X , Y , Z;
  int read(){
    double theta , phi;
    cin >> theta >> phi;
    if( theta < -.5 )
      return -1;
    theta = (theta / 180.) * pi;
    phi = (phi / 180.) * pi;
    X = cos( theta ) * sin( phi );
    Y = sin( theta ) * sin( phi );
    Z = cos( phi );
    double sum = fabs( X ) + fabs( Y ) + fabs( Z );
    sum = nn / sum;
    X = sum * X;
    Y = sum * Y;
    Z = sum * Z;
    int sx = sgn( X );
    int sy = sgn( Y );
    int sz = sgn( Z );
    for( int i = 0 ; i < 8 ; i ++ )
      if( sgnx[ i ] == sx and
          sgny[ i ] == sy and
          sgnz[ i ] == sz )
        return i;
    return -1;
  }
  void print() const{
    //printf( "(%.6f, %.6f, %.6f)\n" , X , Y , Z );
  }
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z};
}
Pt operator*( const Pt& pp , double tk ){
  return {pp.X * tk, pp.Y * tk, pp.Z * tk};
}
Pt operator/( const Pt& pp , double tk ){
  return {pp.X / tk, pp.Y / tk, pp.Z / tk};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
double norm2( const Pt& pp ){
  return pp * pp;
}
bool equal( const Pt& p1 , const Pt& p2 ){
  return equal( p1.X , p2.X ) and
         equal( p1.Y , p2.Y ) and
         equal( p1.Z , p2.Z );
}
Pt reflect( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  Pt zen = p1 + (p2 - p1) * (((p3 - p1) * (p2 - p1)) / norm2( p2 - p1 ));
  return zen + zen - p3;
}
int e[ 8 ][ 3 ];
Pt p1 , p2 , q1 , q2 , sumop[ 8 ];
int at1 , at2 , _cs;
double ans;
Pt o[ 6 ] , w[ 8 ][ 3 ];
void go( const Pt& n0 , const Pt& n1 , const Pt& n2 ,
         const Pt& o0 , const Pt& o1 , const Pt& o2 ,
         const Pt& orip , Pt& resp ){
  double theta0 = myacos( (orip - o0) * (o1 - o0) / norm( orip - o0 ) / norm( o1 - o0 ) );
  double dst = norm( orip - o0 );
  Pt dir = n2 - n1;
  double bl = 0 , br = 1;
  for( int i = 0 ; i < 50 ; i ++ ){
    double bmid = (bl + br) * .5;
    Pt at = n1 + dir * bmid;
    double tt = myacos( (at - n0) * (n1 - n0) / norm( at - n0 ) / norm( n1 - n0 ) );
    if( tt > theta0 ) br = bmid;
    else bl = bmid;
  }
  Pt at = n1 + dir * bl;
  at = at - n0;
  at = at * (dst / norm(at));
  resp = n0 + at;
}
int test( int now ,
          const Pt& n0 , const Pt& n1 , const Pt& n2 ,
          const Pt& o0 , const Pt& o1 , const Pt& o2 ){
  int ret = 0;
  if( at1 == now ){
    go( n0 , n1 , n2 , o0 , o1 , o2 , p1 , q1 );
    ret |= (1 << 0);
  }
  if( at2 == now ){
    go( n0 , n1 , n2 , o0 , o1 , o2 , p2 , q2 );
    ret |= (1 << 1);
  }
  return ret;
}
void dfs( int now , int msk ,
          const Pt& n0 , const Pt& n1 , const Pt& n2 ,
          const Pt& o0 , const Pt& o1 , const Pt& o2 , int got ){
  got |= test( now , n0 , n1 , n2 , o0 , o1 , o2 );
  if( got == 3 ){
    double tans = norm( q1 - q2 );
    ans = min( ans , tans );
    return;
  }
  for( int i = 0 ; i < 3 ; i ++ ){
    int nxt = e[ now ][ i ];
    if( (msk >> nxt) & 1 ) continue;
    int nmsk = msk | (1 << nxt);
    for( int j = 0 ; j < 3 ; j ++ ){
      if( equal( o0 + o1 , sumop[ nxt ] - w[ nxt ][ j ] ) ){
        dfs( nxt , nmsk , n0 , n1 , reflect( n0 , n1 , n2 ) ,
                          o0 , o1 , w[ nxt ][ j ] , got );
        break;
      }
      if( equal( o0 + o2 , sumop[ nxt ] - w[ nxt ][ j ] ) ){
        dfs( nxt , nmsk , n0 , reflect( n0 , n2 , n1 ) , n2 ,
                          o0 , w[ nxt ][ j ] , o2 , got );
        break;
      }
      if( equal( o1 + o2 , sumop[ nxt ] - w[ nxt ][ j ] ) ){
        dfs( nxt , nmsk , reflect( n1 , n2 , n0 ) , n1 , n2 ,
                          w[ nxt ][ j ] , o1 , o2 , got );
        break;
      }
    }
  }
}
void solve(){
  ans = 1e9;
  for( int i = 0 ; i < 8 ; i ++ )
    dfs( i , (1 << i) , w[ i ][ 0 ] , w[ i ][ 1 ] , w[ i ][ 2 ] ,
                        w[ i ][ 0 ] , w[ i ][ 1 ] , w[ i ][ 2 ] , 0 );
                        //o[ 0 ] , o[ 1 ] , o[ 4 ] ,
                        //o[ 0 ] , o[ 1 ] , o[ 4 ] , 0 );
  printf( "Case %d: " , ++ _cs );
  cout << fixed << setprecision( 3 ) << ans << "\n";
}
int main(){
  o[ 0 ] = { +nn , 0 , 0 };
  o[ 1 ] = { 0 , +nn , 0 };
  o[ 2 ] = { -nn , 0 , 0 };
  o[ 3 ] = { 0 , -nn , 0 };
  o[ 4 ] = { 0 , 0 , -nn };
  o[ 5 ] = { 0 , 0 , +nn };


  for( int i = 0 ; i < 4 ; i ++ ){
    sgnz[ i ] = -1;
    sgnz[ i + 4 ] = +1;
  }
  for( int i = 0 ; i < 8 ; i ++ ){
    if( (i & 3) == 0 or (i & 3) == 3 )
      sgnx[ i ] = +1;
    else
      sgnx[ i ] = -1;
    if( (i & 3) == 0 or (i & 3) == 1 )
      sgny[ i ] = +1;
    else
      sgny[ i ] = -1;
  }
  for( int i = 0 ; i < 4 ; i ++ ){
    e[ i ][ 0 ] = (i + 3) & 3;
    e[ i ][ 1 ] = (i + 1) & 3;
    e[ i ][ 2 ] = i + 4;
    e[ i + 4 ][ 0 ] = i;
    e[ i + 4 ][ 1 ] = 4 + ((i + 1) & 3);
    e[ i + 4 ][ 2 ] = 4 + ((i + 3) & 3);
  }
  for( int i = 0 ; i < 4 ; i ++ ){
    sumop[ i     ] = o[ i ] + o[ (i + 1) & 3 ] + o[ 4 ];
    w[ i ][ 0 ] = o[ i ];
    w[ i ][ 1 ] = o[ (i + 1) & 3 ];
    w[ i ][ 2 ] = o[ 4 ];
    sumop[ i + 4 ] = o[ i ] + o[ (i + 1) & 3 ] + o[ 5 ];
    w[ i + 4 ][ 0 ] = o[ i ];
    w[ i + 4 ][ 1 ] = o[ (i + 1) & 3 ];
    w[ i + 4 ][ 2 ] = o[ 5 ];
  }
  while( true ){
    if( ( at1 = p1.read()) == -1 ) break;
    if( ( at2 = p2.read()) == -1 ) break;
    solve();
  }
}
