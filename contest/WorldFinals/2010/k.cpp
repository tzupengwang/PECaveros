#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define double long double
struct Pt{
  LL X , Y , Z;
  bool read(){
    if(cin >> X >> Y >> Z)
      return true;
    return false;
  }
  void print(){
    //fprintf( stderr , "%.2f %.2f %.2f\n" , X , Y , Z );
  }
  bool operator<( const Pt& pp ) const{
    return tie(X ,Y, Z ) < tie(pp.X, pp.Y, pp.Z);
  }
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z};
}
Pt operator*( const Pt& pp , LL tk ){
  return {pp.X * tk ,
          pp.Y * tk ,
          pp.Z * tk };
}
LL operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return {p1.Y * p2.Z - p1.Z * p2.Y,
          p1.Z * p2.X - p1.X * p2.Z,
          p1.X * p2.Y - p1.Y * p2.X};
}
LL norm2( const Pt& pp ){
  return pp * pp;
}
double norm( const Pt& pp ){
  return sqrtl( pp * pp );
}
Pt a , b , c , d , e , f;
double cenx, ceny, cenz;
LL volume( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  return abs( (p1 ^ p2) * p3 );
}
void find_center(){
  Pt cend = (a + b + c + d); // /4
  Pt cene = (a + b + c + e); // /4
  LL vold = volume( b - a , c - a , d - a );
  LL vole = volume( b - a , c - a , e - a );
  Pt cen = cend * vold + cene * vole;
  LL dcen = 4 * (vold + vole);
  cenx = cen.X / (double)dcen;
  ceny = cen.Y / (double)dcen;
  cenz = cen.Z / (double)dcen;
  cerr << cenx << " " << ceny << " " << cenz << endl;
}
double min_ans , max_ans;
bool got;

Pt p0;
bool out( const Pt& p1 , const Pt& p2 , const Pt& far ){
  Pt ver = far ^ (p2 - p1);
  double dst = 0.;
  dst += (cenx - p0.X - p1.X) * ver.X;
  dst += (ceny - p0.Y - p1.Y) * ver.Y;
  dst += (cenz - p0.Z - p1.Z) * ver.Z;
  double len = 0.;
  len += (double)ver.X * ver.X;
  len += (double)ver.Y * ver.Y;
  len += (double)ver.Z * ver.Z;
  dst /= sqrtl( len );
  return dst < 0.2;
}

void cal( Pt p1 , Pt p2 , Pt p3 , Pt goal , Pt o1 , Pt o2 ){
  p0 = p1;
  p2 = p2 - p1;
  p3 = p3 - p1;
  goal = goal - p1;
  o1 = o1 - p1;
  o2 = o2 - p1;
  p1 = {0, 0};
  Pt far = p2 ^ p3;

  double cur = (goal * far) / norm( far );
  
  if( norm( far ) == 0 ) return;
  for( Pt pp : {goal, o1, o2} )
    if( pp * far < 0 )
      return;

  Pt other;
  bool got_other = false;
  for( Pt pp : {o1, o2} )
    if( far * pp == 0 ){
      other = pp;
      got_other = true;
    }
  //cerr << cur << endl;
  if( not got_other ){
    if( out( p1 , p2 , far ) ) return;
    if( out( p2 , p3 , far ) ) return;
    if( out( p3 , p1 , far ) ) return;
  }else{
    bool in1 = ((other - p1) ^ (other - p2)) *
               ((other - p1) ^ (other - p3)) <= 0;
    bool in2 = ((other - p2) ^ (other - p1)) *
               ((other - p2) ^ (other - p3)) <= 0;
    bool in3 = ((other - p3) ^ (other - p1)) *
               ((other - p3) ^ (other - p2)) <= 0;
    if( in1 and in2 and in3 ){
      if( out( p1 , p2 , far ) ) return;
      if( out( p2 , p3 , far ) ) return;
      if( out( p3 , p1 , far ) ) return;
    }else if( in1 ){
      if( out( p1 , p2 , far ) ) return;
      if( out( p2 , other , far ) ) return;
      if( out( other , p3 , far ) ) return;
      if( out( p3 , p1 , far ) ) return;
    }else if( in2 ){
      if( out( p2 , p3 , far ) ) return;
      if( out( p3 , other , far ) ) return;
      if( out( other , p1 , far ) ) return;
      if( out( p1 , p2 , far ) ) return;
    }else if( in3 ){
      if( out( p3 , p1 , far ) ) return;
      if( out( p1 , other , far ) ) return;
      if( out( other , p2 , far ) ) return;
      if( out( p2 , p3 , far ) ) return;
    }
  }


  if( not got ){
    min_ans = max_ans = cur;
    got = true;
  }else{
    min_ans = min( min_ans , cur );
    max_ans = max( max_ans , cur );
  }
}
int _cs;
void solve(){
  got = false;
  find_center();
  Pt p[ 5 ] = {a, b, c, d, e};
  int id[ 5 ] = {0, 1, 2, 3, 4};
  do cal( p[ id[ 0 ] ] , p[ id[ 1 ] ] , p[ id[ 2 ] ] , f , p[ id[ 3 ] ] , p[ id[ 4 ] ] );
  while( next_permutation( id , id + 5 ) );
  printf( "Case %d: " , ++ _cs );
  cout << fixed << setprecision( 5 );
  cout << min_ans << " ";
  cout << max_ans << "\n";
}
int main(){
  while( a.read() ){
    b.read();
    c.read();
    d.read();
    e.read();
    f.read();
    solve();
  }
}
