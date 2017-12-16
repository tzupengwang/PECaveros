#include <bits/stdc++.h>
using namespace std;
typedef long double type;
const type eps = 1e-9;
const type pi = acosl( -1. );
bool equal( type x , type y ){
  return x - eps < y and y < x + eps;
}
struct Pt3{
  type X , Y , Z;
  int id;
  Pt3( type x = 0 , type y = 0 , type z = 0 ){
    X = x; Y = y; Z = z;
  }
  void print(){
    printf( "%.6LF %.6LF %.6LF\n" , X , Y , Z );
  }
};
typedef Pt3 Pt;
Pt3 operator^( const Pt3& p1 , const Pt3& p2 ){
  return Pt3( p1.Y * p2.Z - p1.Z * p2.Y ,
              p1.Z * p2.X - p1.X * p2.Z ,
              p1.X * p2.Y - p1.Y * p2.X );
}
Pt3 operator-( const Pt3& p1 , const Pt3& p2 ){
  return Pt3( p1.X - p2.X , p1.Y - p2.Y , p1.Z - p2.Z );
}
type operator*( const Pt3& p1 , const Pt3& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
type norm2( const Pt3& p1 ){
  return p1 * p1;
}
#define N 333
int s , sla[ N ] , slo[ N ];;
inline Pt3 read( int id ){
  int lo , la;
  cin >> lo >> la;
  slo[ id ] = lo;
  sla[ id ] = la;
  if( s == -1 )
    s = id;
  else if( make_pair( la , lo ) < make_pair( sla[ s ] , slo[ s ] ) )
    s = id;
  type phi = (lo * pi / 180.0);
  type theta = (la * pi / 180.0);
  return Pt3( cosl( phi ) * cosl( theta ) ,
              cosl( phi ) * sinl( theta ) ,
              sinl( phi ) );
}
int n;
Pt3 p[ N ];
void init(){
  cin >> n;
  s = -1;
  for( int i = 0 ; i < n ; i ++ ){
    p[ i ] = read( i );
    p[ i ].id = i;
  }
}
bool gg(){
  Pt hf = p[ 0 ] ^ p[ 1 ];
  for( int i = 2 ; i < n ; i ++ )
    if( not equal( hf * p[ i ] , 0.0 ) )
      return false;
  return true;
}
void no(){
  puts( "inconclusive" );
}
bool used[ N ];
void go(){
  vector<int> vv;
  vv.push_back( s );
  for( int i = 0 ; i < n ; i ++ )
    used[ i ] = false;
  used[ s ] = true;
  while( true ){
    int cand = -1;
    if( vv.size() > 2u ) cand = vv[ 0 ];
    for( int i = 0 ; i < n ; i ++ ){
      if( used[ i ] ) continue;
      if( cand == -1 ) cand = i;
      else{
        Pt chf = p[ vv.back() ] ^ p[ cand ];
        if( (chf * p[ i ]) < -eps )
          cand = i;
        else if( equal( chf * p[ i ] , 0.0 ) and
                 norm2( p[ i ] - p[ vv.back() ] ) >
                 norm2( p[ cand ] - p[ vv.back() ] ) )
          cand = i;
      }
    }
    if( cand == -1 ){
      no();
      return;
    }
    if( cand == vv[ 0 ] ) break;
    Pt hf = p[ vv.back() ] ^ p[ cand ];
    vv.push_back( cand );
    used[ cand ] = true;
    for( int i = 0 ; i < n ; i ++ ){
      if( used[ i ] ) continue;
      if( equal( hf * p[ i ] , 0.0 ) )
        used[ i ] = true;
    }
  }
  if( (int)vv.size() == n ){
    no();
    return;
  }
  sort( vv.begin() , vv.end() );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    printf( "%d%c" , vv[ i ] , " \n"[ i + 1 == vv.size() ] );
}
void solve(){
  go();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
