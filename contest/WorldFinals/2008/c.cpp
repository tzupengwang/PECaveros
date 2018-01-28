#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define double long double
const double eps = 1e-8;
const double pi = acosl( -1. );
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt, pair<type,int> > Cir;
#define X first
#define Y second
#define O first
#define R second.first
#define D second.second
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
}
void print( const Pt& pp ){
  printf( "(%.6f, %.6f)" , pp.X , pp.Y );
}
void print( const Line& tl ){
  print( tl.first ); putchar( ' ' );
  print( tl.second ); putchar( '\n' );
}
void scan( Cir& cc ){
  scan( cc.O );
  cin >> cc.R;
  string _dir; cin >> _dir;
  if( _dir == "CC" ) cc.D = -1;
  else cc.D = 1;
}
int ori( const Pt& o , const Pt& a , const Pt& b ){
  double ret = ( a - o ) ^ ( b - o );
  return (ret > 0) - (ret < 0);
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( fabs( ( p2 - p1 ) ^ ( q2 - q1 ) ) < eps ){ // parallel
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) < 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) < 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) < 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) < 0;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0);
}
vector<Line> go( const Cir& c1 , const Cir& c2 , int sign1 ){
  assert( sign1 == 1 or sign1 == -1 );
  // 1 for whi, -1 for nei
  vector<Line> ret;
  double d_sq = norm2( c1.O - c2.O );
  if( d_sq < eps ) return ret;
  double d = sqrt( d_sq );
  Pt v = ( c2.O - c1.O ) / d;
  double c = ( c1.R - sign1 * c2.R ) / d;
  if( c * c > 1 ) return ret;
  double h = sqrt( max( (double)0.0 , 1.0 - c * c ) );
  for( int sign2 = 1 ; sign2 >= -1 ; sign2 -= 2 ){
    Pt n;
    n.X = v.X * c - sign2 * h * v.Y;
    n.Y = v.Y * c + sign2 * h * v.X;
    Pt p1 = c1.O + n * c1.R;
    Pt p2 = c2.O + n * ( c2.R * sign1 );
    if( fabs( p1.X - p2.X ) < eps and
        fabs( p1.Y - p2.Y ) < eps )
      p2 = p1 + perp( c2.O - c1.O );
    ret.push_back( { p1 , p2 } );
  }
  return ret;
}
Pt nearest( const Cir& cc , const Line& tl ){
  double vv = ((tl.second - tl.first) * (cc.O - tl.first)) / norm2( tl.second - tl.first );
  vv = max( (double)0. , vv );
  vv = min( (double)1. , vv );
  return tl.first + (tl.second - tl.first) * vv;
}
#define N 22
int n , s , t;
Cir c[ N ];
double d;
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scan( c[ i ] );
  cin >> s >> t >> d;
}
double ans;
Line buf[ N ];
int used;
double ang( const Pt& pp ){
  return atan2( pp.Y , pp.X );
}
double on_cir( const Cir& cc , const Pt& pre , const Pt& now ){
  double fr = ang( pre - cc.O );
  double to = ang( now - cc.O );
  if( cc.D == -1 ){
    if( to < fr - eps ) to += pi + pi;
    return cc.R * max( (double)0. , (to - fr) );
  }else{
    if( fr < to - eps ) fr += pi + pi;
    return cc.R * max( (double)0. , (fr - to) );
  }
}

bool dir_gg( const Cir& cc , const Pt& p1 , const Pt& p2 ){
  double vl = (p1 - cc.O) ^ (p2 - p1);
  if( vl > 0 and cc.D == +1 ) return true;
  if( vl < 0 and cc.D == -1 ) return true;
  return false;
}

void go( int cur , int dep , double tans , Pt pre ){
  if( ans > 0 and tans > ans - eps ) return;
  if( cur == t ){
    //printf( "%.12f\n" , tans );
    //for( int i = 0 ; i < dep ; i ++ )
      //print( buf[ i ] );
    ans = tans;
    return;
  }
  int res = ((1 << n) - 1) ^ used;
  while( res ){
    int i = __lg( res & (-res) );
    res ^= (1 << i);
    {
      int ndir = (c[ cur ].D == c[ i ].D ? 1 : -1);
      vector<Line> tang = go( c[ cur ] , c[ i ] , ndir );
      for( auto ln : tang ){
        double dd = norm( ln.second - ln.first );
        if( dd > d - eps ) continue;
        if( dir_gg( c[ cur ] , nearest( c[ cur ] , ln ) ,
                               nearest( c[ i ] , ln ) ) )
          continue;
        if( dir_gg( c[ i ] , nearest( c[ cur ] , ln ) ,
                             nearest( c[ i ] , ln ) ) )
          continue;
        bool ok = true;
        for( int j = 0 ; j < dep and ok ; j ++ )
          if( banana( buf[ j ].first , buf[ j ].second ,
                      ln.first , ln.second ) )
            ok = false;
        for( int j = 0 ; j < n and ok ; j ++ ){
          if( j == cur or j == i ) continue;
          Pt tmp = nearest( c[ j ] , ln );
          if( norm( tmp - c[ j ].O ) < c[ j ].R + eps )
            ok = false;
        }
        if( not ok ) continue;
        double nans = tans;
        if( cur != s )
          nans += on_cir( c[ cur ] , pre , nearest( c[ cur ] , ln ) );
        nans += dd;
        used ^= (1 << i);
        buf[ dep ] = ln;
        go( i , dep + 1 , nans , nearest( c[ i ] , ln ) );
        used ^= (1 << i);
      }
    }
  }
}
int _cs;
void solve(){
  used = 0;
  ans = -1;
  used |= (1 << s);
  go( s , 0 , 0 , {0, 0} );
  printf( "Case %d: " , ++ _cs );
  if( ans < 0 )
    puts( "Cannot reach destination shaft" );
  else{
    long long fans = (ans * 1000 + 5);
    fans /= 10;
    printf( "length = %lld" , fans / 100 );
    fans %= 100;
    if( fans ){
      putchar( '.' );
      if( fans % 10 == 0 )
        printf( "%lld" , fans / 10 );
      else
        printf( "%02lld" , fans );
    }
    puts( "" );
  }
}
int main(){
  while( cin >> n and n ){
    init();
    solve();
  }
}
