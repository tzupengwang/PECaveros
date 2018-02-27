#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
const double eps = 1e-6;
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
void scan( Pt& tp ){
  cin >> tp.X >> tp.Y;
}
void print( const Pt& tp ){
  printf( "(%.6f, %.6f)" , tp.X , tp.Y );
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 , bool& res ){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return { 0 , 0 };
  }
  res = true;
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
#define N 333
int n;
Pt s , p[ N ];
void init(){
  scan( s );
  for( int i = 1 ; i <= n ; i ++ )
    scan( p[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    p[ i + n + n ] = p[ i + n ] = p[ i ];
}
double ans;
int _cs , gt[ N ][ N ][ 2 ] , stmp;
double dp[ N ][ N ][ 2 ];
Pt reflect( const Pt& p1 , const Pt& p2 , const Pt& pp , bool& ok ){
  if( ((p2 - p1) ^ (pp - p1)) < -eps )
    ok = false;
  Pt onto = p1 + (p2 - p1) * ((p2 - p1) * (pp - p1) / norm2(p2 - p1));
  return onto + onto - pp;
}
double cst[ N ][ N ][ 2 ][ 3 ];
int tg[ N ][ N ][ 2 ][ 3 ];
bool in( const Pt& p1 , const Pt& pp , const Pt& p2 ){
  return (pp - p1) * (p2 - p1) > -eps and
         (pp - p2) * (p1 - p2) > -eps;
}
double cost( Pt ss , Pt tt , Pt dir , int l , int r , int kd , int kd2 ){
  //return norm( dir );
  if( tg[ l ][ r ][ kd ][ kd2 ] == stmp ) return cst[ l ][ r ][ kd ][ kd2 ];
  tg[ l ][ r ][ kd ][ kd2 ] = stmp;
  double ret = 0;
  bool res;
  for( int i = r ; i >= l ; i -- ){
    res = true;
    Pt at = interPnt( ss , ss + dir , p[ i ] , p[ i + 1 ] , res );
    assert( res );
    if( !res ) continue;
    ret += norm( ss - at );
    {
      Pt p1 = p[ i ] , p2 = p[ i + 1 ];
      Pt pdir = (p2 - p1) * ((p2 - p1) * dir / norm2( p2 - p1 ));
      Pt dlt = pdir - dir;
      dir = dir + dlt * 2;
    }
    if( not in( p[ i ] , at , p[ i + 1 ] ) )
      ret += 1e9;
    ss = at;
  }
  if( not ( (tt - ss) * dir > - eps and fabs( (tt - ss) ^ dir ) < eps ) )
    ret += 1e9;
  ret += norm( ss - tt );
  return cst[ l ][ r ][ kd ][ kd2 ] = ret;
}
double DP( int l , int r , int kd ){
  if( l == r ) return norm( s - p[ l ] );
  if( gt[ l ][ r ][ kd ] == stmp ) return dp[ l ][ r ][ kd ];
  gt[ l ][ r ][ kd ] = stmp;
  dp[ l ][ r ][ kd ] = 1e9;
  Pt goal = (kd == 0 ? s : p[ l ] );
  Pt start = goal;
  bool ggwp = false;
  for( int i = l ; i <= r ; i ++ ){
    if( i < r ){
      dp[ l ][ r ][ kd ] =
        min( dp[ l ][ r ][ kd ] ,
             cost( p[ i + 1 ] , start , goal - p[ i + 1 ] , l , i - 1 , kd , 0 ) +
             DP( i + 1 , r , 1 ) );
    }
    goal = reflect( p[ i ] , p[ i + 1 ] , goal , ggwp );
    if( ggwp ) break;
    if( i + 1 < r ){
      dp[ l ][ r ][ kd ] =
        min( dp[ l ][ r ][ kd ] ,
             cost( p[ i + 2 ] , start , goal - p[ i + 2 ] , l , i , kd , 1 ) +
             DP( i + 2 , r , 1 ) );
    }
  }
  //printf( "%d %d %d : %.12f\n" , l , r , kd , dp[ l ][ r ][ kd ] );
  if( !ggwp ){
    dp[ l ][ r ][ kd ] =
      min( dp[ l ][ r ][ kd ] ,
           cost( s , start , goal - s , l , r , kd , 2 ) );
  }
  //printf( "%d %d %d : %.12f\n" , l , r , kd , dp[ l ][ r ][ kd ] );
  return dp[ l ][ r ][ kd ];
}
void solve(){
  ans = 1e9;
  ++ stmp;
  for( int i = 1 ; i <= n ; i ++ )
    ans = min( ans , DP( i , i + n - 1 , 0 ) );
  printf( "Case %d: %.2f\n" , ++ _cs , ans );
}
int main(){
  while( cin >> n ){
    init();
    solve();
  }
}
