#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const type eps = 1e-9;
const type pi = acos( -1.0 );
bool equal( type t1 , type t2 ){
  return t1 - eps < t2 && t2 < t1 + eps;
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
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
void print( const Pt& tp ){
  printf( "(%.6f,%.6f)" , tp.X , tp.Y );
}
struct Mec{
  // return pair of center and r^2
  static const int N = 101010;
  int n;
  Pt p[ N ], cen;
  double r2;  
  void init( int _n , Pt _p[] ){
    n = _n;
    memcpy( p , _p , sizeof(Pt) * n );
  }
  double sqr(double a){ return a*a; }
  Pt center(Pt p0, Pt p1, Pt p2) {
    Pt a = p1-p0;
    Pt b = p2-p0;
    double c1=norm2( a ) * 0.5;
    double c2=norm2( b ) * 0.5;
    double d = a ^ b;
    double x = p0.X + (c1 * b.Y - c2 * a.Y) / d;
    double y = p0.Y + (a.X * c2 - b.X * c1) / d;
    return Pt(x,y);
  }
  pair<Pt,double> solve(){
    random_shuffle(p,p+n);
    r2=0;
    for (int i=0; i<n; i++){
      if (norm2(cen-p[i]) <= r2) continue;
      cen = p[i];
      r2 = 0;
      for (int j=0; j<i; j++){
        if (norm2(cen-p[j]) <= r2) continue;
        cen = Pt((p[i].X+p[j].X)*0.5, (p[i].Y+p[j].Y)*0.5);
        r2 = norm2(cen-p[j]);
        for (int k=0; k<j; k++){
          if (norm2(cen-p[k]) <= r2) continue;
          cen = center(p[i],p[j],p[k]);
          r2 = norm2(cen-p[k]);
        }
      }
    }
    return {cen,sqrt(r2)};
  }
} mec;
#define N 101010
int n , k;
Pt tp[ N ];
vector< pair< Pt , int > > xy , yx;
int px[ N ] , py[ N ];
bool init(){
  if( scanf( "%d%d" , &n , &k ) != 2 )
    return false;
  xy.clear(); yx.clear();
  for( int i = 0 ; i < n ; i ++ ){
    scan( tp[ i ] );
    xy.push_back( { tp[ i ] , i } );
    yx.push_back( { { tp[ i ].Y , tp[ i ].X } , i } );
  }
  sort( xy.begin() , xy.end() );
  sort( yx.begin() , yx.end() );
  for( int i = 0 ; i < n ; i ++ ){
    px[ xy[ i ].second ] = i;
    py[ yx[ i ].second ] = i;
  }
  return true;
}
type ans , ang[ N ] , dst[ N ];
Pt cand[ N ];
pair<double,int> vv[ N + N + N + N ];
inline type reg( type deg ){
  while( deg <= -pi ) deg += pi + pi;
  while( deg >  +pi ) deg -= pi + pi;
  return deg;
}
inline bool okay( const Pt& cen , int ct , type r ){
  int vsz = 0;
  for( int i = 0 ; i < ct ; i ++ ){
    if( dst[ i ] > r + r + eps ) continue;
    type dst2 = sqrt( max( 4 * r * r - dst[ i ] * dst[ i ] , eps ) );
    type cosvl = ( dst[ i ] * dst[ i ] + 4 * r * r - dst2 * dst2 ) /
                 ( 4 * dst[ i ] * r );
    if( cosvl > +1.0 - eps ) cosvl = +1.0 - eps;
    if( cosvl < -1.0 + eps ) cosvl = -1.0 + eps;
    type deg = acos( cosvl );
    type angl = reg( ang[ i ] - deg );
    type angr = reg( ang[ i ] + deg );
    if( angl < angr ){
      vv[ vsz ++ ] = { angl - eps , +1 };
      vv[ vsz ++ ] = { angr + eps , -1 };
    }else{
      vv[ vsz ++ ] = {    0 - eps , +1 };
      vv[ vsz ++ ] = { angr + eps , -1 };
      vv[ vsz ++ ] = { angl - eps , +1 };
    }
  }
  sort( vv , vv + vsz );
  int sum = 0;
  for( int i = 0 ; i < vsz ; i ++ ){
    sum += vv[ i ].second;
    if( sum >= k - 1 ) return true;
  }
  return false;
}
pair<Pt,int> all[ N ];
void _solve(){
  srand( 514514 );
  for( int i = 0 ; i < n ; i ++ )
    all[ i ] = { tp[ i ] , i };
  random_shuffle( all , all + n );
  for( int i = 0 ; i < n ; i ++ ){
    int id = all[ i ].second , ct = 0;
    for( int j = px[ id ] - 1 ; j >= 0 ; j -- ){
      if( all[ i ].first.X - xy[ j ].first.X > ans + ans ) break;
      if( norm( xy[ j ].first - all[ i ].first ) > ans + ans ) continue;
      cand[ ct ++ ] = xy[ j ].first;
    }
    for( int j = px[ id ] + 1 ; j < n ; j ++ ){
      if( xy[ j ].first.X - all[ i ].first.X > ans + ans ) break;
      if( norm( xy[ j ].first - all[ i ].first ) > ans + ans ) continue;
      cand[ ct ++ ] = xy[ j ].first;
    }
    for( int j = py[ id ] - 1 ; j >= 0 ; j -- ){
      if( all[ i ].first.Y - yx[ j ].first.X > ans + ans ) break;
      if( norm( Pt( yx[ j ].first.Y , yx[ j ].first.X ) - all[ i ].first )
          > ans + ans ) continue;
      cand[ ct ++ ] = { yx[ j ].first.Y , yx[ j ].first.X };
    }
    for( int j = py[ id ] + 1 ; j < n ; j ++ ){
      if( yx[ j ].first.X - all[ i ].first.Y > ans + ans ) break;
      if( norm( Pt( yx[ j ].first.Y , yx[ j ].first.X ) - all[ i ].first )
          > ans + ans ) continue;
      cand[ ct ++ ] = { yx[ j ].first.Y , yx[ j ].first.X };
    }
    sort( cand , cand + ct );
    int sz = 0;
    for( int j = 0 ; j < ct ; j ++ ){
      if( sz > 0 && equal( cand[ j ].X , cand[ sz - 1 ].X ) &&
                    equal( cand[ j ].Y , cand[ sz - 1 ].Y ) )
        continue;
      cand[ sz ++ ] = cand[ j ];
    }
    ct = sz;
    for( int j = 0 ; j < ct ; j ++ ){
      Pt dlt = cand[ j ] - all[ i ].first;
      ang[ j ] = atan2( dlt.Y , dlt.X );
      dst[ j ] = norm( dlt );
    }
    if( ct < k - 1 ) continue;
    type bl = 0.0 , br = ans;
    for( int j = 0 ; j < 30 ; j ++ ){
      type mid = ( bl + br ) * 0.5;
      if( okay( all[ i ].first , ct , mid ) ) br = mid;
      else bl = mid;
    }
    ans = br;
  }
}
void solve(){
  mec.init( n , tp );
  Circle cir = mec.solve();
  ans = cir.R;
  _solve();
  printf( "%.9f\n" , ans );
}
int main(){
  while( init() )
    solve();
}
