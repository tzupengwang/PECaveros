#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
LL sqr( LL x ){
  return x * x;
}
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
bool in_cc(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){
// return p4 is in circumcircle of tri(p1,p2,p3)
	LL u11 = p1.X - p4.X;
	LL u21 = p2.X - p4.X;
	LL u31 = p3.X - p4.X;
	LL u12 = p1.Y - p4.Y;
	LL u22 = p2.Y - p4.Y;
	LL u32 = p3.Y - p4.Y;
	LL u13 = sqr(p1.X)-sqr(p4.X)+sqr(p1.Y)-sqr(p4.Y);
	LL u23 = sqr(p2.X)-sqr(p4.X)+sqr(p2.Y)-sqr(p4.Y);
	LL u33 = sqr(p3.X)-sqr(p4.X)+sqr(p3.Y)-sqr(p4.Y);
	LL det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 - u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
	return det > 0;
}
#define N 101010
int n;
Pt p[ N ][ 3 ];
vector<Pt> v;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ ){
      scan( p[ i ][ j ] );
      v.push_back( p[ i ][ j ] );
    }
}
void solve(){
  sort( v.begin() , v.end() );
  v.resize( unique( v.begin() , v.end() ) - v.begin() );
  for( auto pp : v )
    for( int i = 0 ; i < n ; i ++ )
      if( in_cc( p[ i ][ 0 ] , p[ i ][ 1 ] , p[ i ][ 2 ] , pp ) ){
        puts( "NO" );
        return;
      }
  puts( "YES" );
}
int main(){
  init();
  solve();
}
