#include <bits/stdc++.h>
using namespace std;
//#define double long double
typedef double type;
#define D type
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const double eps = 1e-12;
const double pi = acos( -1 );
bool equal( double x , double y ){
  return x - eps < y and y < x + eps;
}
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
void scan( Pt& tp ){
  cin >> tp.X >> tp.Y;
  //scanf( "%lf%lf" , &tp.X , &tp.Y );
}
#define N 111
int n , r;
Circle c[ N ];
bool gg;
double ans;
void init(){
  gg = false;
  Pt tmp;
  for( int i = 0 , ri ; i < n ; i ++ ){
    scan( tmp );
    scanf( "%d" , &ri );
    if( ri > r )
      gg = true;
    else
      c[ i ] = { tmp , r - ri + 1e-7 };
  }
  ans = 0;
}
bool CCinter( Circle& a , Circle& b , Pt& p1 , Pt& p2 ){
  Pt o1 = a.O , o2 = b.O;
  D r1 = a.R , r2 = b.R;
  D d2 = ( o1 - o2 ) * ( o1 - o2 );
  D d = sqrt(d2);
  if( d > r1 + r2 ) return false;
  Pt u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  D A = sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
  Pt v = Pt( o1.Y-o2.Y , -o1.X + o2.X ) * A / (2*d2);
  p1 = u + v; p2 = u - v;
  return true;
}
void cal(){
  vector<Circle> useful;
  for( int i = 0 ; i < n ; i ++ ){
    bool keep = true;
    for( int j = 0 ; j < n and keep ; j ++ ){
      if( equal( c[ i ].R , c[ j ].R ) ){
        if( equal( c[ i ].O.X , c[ j ].O.X ) and
            equal( c[ i ].O.Y , c[ j ].O.Y ) ){
          if( i < j )
            keep = false;
        }
      }else if( c[ i ].R > c[ j ].R ){
        if( norm( c[ i ].O - c[ j ].O ) < c[ i ].R - c[ j ].R + eps )
          keep = false;
      }
    }
    if( keep )
      useful.push_back( c[ i ] );
  }
  int tot = (int)useful.size();
  if( (int)useful.size() == 1 ){
    ans = 2 * pi * ( r + useful[ 0 ].R );
    return;
  }
  bool got = false;
  for( int i = 0 ; i < tot ; i ++ ){
    vector< pair<double,int> > vv;
    for( int j = 0 ; j < tot ; j ++ ){
      if( i == j ) continue;
      if( norm( useful[ i ].O - useful[ j ].O ) >
          useful[ i ].R + useful[ j ].R ){
        ans = 0.;
        return;
      }
      Pt aa , bb;
      CCinter( useful[i], useful[j], aa, bb);
      D A = atan2(aa.Y - useful[i].O.Y, aa.X - useful[i].O.X);
      D B = atan2(bb.Y - useful[i].O.Y, bb.X - useful[i].O.X);
      if( B > A ) A += pi + pi;
      for( int jj = -1 ; jj <= 1 ; jj ++ ){
        vv.push_back( { B + jj * ( 2 * pi ) - eps , +1 } );
        vv.push_back( { A + jj * ( 2 * pi ) + eps , -1 } );
      }
    }
    sort( vv.begin() , vv.end() );
    int gt = 0;
    for( size_t j = 0 ; j < vv.size() ; j ++ ){
      if( j and gt + 1 == tot ){
        //puts( "in" );
        got = true;
        double bl = max( -pi , vv[ j - 1 ].first );
        double br = min( +pi , vv[ j     ].first );
        if( bl < br )
          ans += ( br - bl ) * useful[ i ].R;
      }
      gt += vv[ j ].second;
    }
  }
  if( not got ){
    ans = 0;
    return;
  }
  ans += 2 * pi * r;
}
void solve(){
  if( !gg ) cal();
  //printf( "%.12LF\n" , ans );
  if( equal( ans , 0.0 ) )
    puts( "0.0" );
  else
    printf( "%.12f\n" , ans );
}
int main(){
  while( scanf( "%d%d" , &n , &r ) == 2 && n ){
    init();
    solve();
  }
}
