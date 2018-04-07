#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
const double eps = 1e-9;
const double pi = acos( -1. );
#define X first
#define Y second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X , p1.Y + p2.Y};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X , p1.Y - p2.Y};
}
LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
LL operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
LL norm2( const Pt& pp ){
  return pp * pp;
}
double norm( const Pt& pp ){
  return sqrt( norm2( pp ) );
}
int ori( const Pt& o , const Pt& a , const Pt& b ){
  LL ret = (a - o) ^ (b - o);
  return (ret > 0) - (ret < 0);
}
bool banana( const Pt& p1 , const Pt& p2 , 
             const Pt& q1 , const Pt& q2 ){
  if( ((p2 - p1) ^ (q2 - q1)) == 0 ) return false;
  return (ori(p1, p2, q1) * ori(p1, p2, q2)) < 0 and
         (ori(q1, q2, p1) * ori(q1, q2, p2)) < 0;
}
int side( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  LL cr = ((p2 - p1) ^ (pp - p1));
  return (cr > 0) - (cr < 0);
}
bool between( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  return (p2 - p1) * (pp - p1) > 0 and
         (p1 - p2) * (pp - p2) > 0;
}
bool between2( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  return (p2 - p1) * (pp - p1) >= 0 and
         (p1 - p2) * (pp - p2) >= 0;
}
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
#define N 444
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    p[ i ].X <<= 1;
    p[ i ].Y <<= 1;
    p[ n + i ] = p[ i ];
  }
}
double ans;
double inter( const Pt& p1 , const Pt& p2 , const Pt& q1 , const Pt& q2 ){
  double f1 = (q2 - q1) ^ (p1 - q1);
  double f2 = (q2 - q1) ^ (q1 - p2);
  double f = (f1 + f2);
  double xx = p1.X * (f2 / f) + p2.X * (f1 / f);
  double yy = p1.Y * (f2 / f) + p2.Y * (f1 / f);
  xx -= p1.X;
  yy -= p1.Y;
  double nei = xx * (p2.X - p1.X) +
               yy * (p2.Y - p1.Y);
  return nei / norm2(p2 - p1);
}
double at( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  return (p3 - p1) * (p2 - p1) / (double)norm2( p1 - p2 );
}
void go( const Pt& p1 , const Pt& p2 ){
  double lft = -1e9 , rgt = 1e9;
  //printf( "%lld, %lld -> %lld, %lld\n" , p1.X , p1.Y , p2.X , p2.Y );
  for( int i = 0 ; i < n ; i ++ ){
    if( banana( p1 , p2 , p[ i ] , p[ i + 1 ] ) )
      return;
    int ss = side( p1 , p2 , p[ i ] );
    int ts = side( p1 , p2 , p[ i + 1 ] );
    if( ss != 0 and ts != 0 ){
      if( ss == ts ) continue;
      double cur = inter( p1 , p2 , p[ i ] , p[ i + 1 ] );
      if( cur < 0.5 ) lft = max( lft , cur );
      else rgt = min( rgt , cur );
      continue;
    }
    if( ss == 0 and ts == 0 )
      continue;
    if( ss == 0 ) continue;
    double tat = at( p1 , p2 , p[ i + 1 ] );

    int ns = side( p1 , p2 , p[ i + 2 ] );
    if( ns != 0 ){
      if( between( p1 , p2 , p[ i + 1 ] ) and ns != ss )
        return;
      if( ns != ss ){
        if( tat < 0.5 ) lft = max( lft , tat );
        else rgt = min( rgt , tat );
      }
      continue;
    }
    double nat = at( p1 , p2 , p[ i + 2 ] );

    int nns = side( p1 , p2 , p[ i + 3 ] );
    
    if( nns != ss ){
      if( between( p1 , p2 , p[ i + 1 ] ) or
          between( p1 , p2 , p[ i + 2 ] ) )
        return;
      if( tat < nat )
        lft = max( lft , tat );
      else
        rgt = min( rgt , tat );
      continue;
    }
    if( between2( p[ i + 1 ] , p[ i + 2 ] , p1 ) or
        between2( p[ i + 1 ] , p[ i + 2 ] , p2 ) or
        between2( p1 , p2 , p[ i + 1 ] ) or
        between2( p1 , p2 , p[ i + 2 ] ) ){
      if( ((p[ i + 1 ] - p[ i ]) ^
           (p[ i + 2 ] - p[ i ])) > 0 ){
        if( nat < tat ) swap( tat , nat );
        lft = max( lft , tat );
        rgt = min( rgt , nat );
      }
    }
    continue;
    if( max( tat , 0. ) < min( nat , 1. ) + eps ){
      lft = max( lft , tat );
      rgt = min( rgt , nat );
    }
  }

  //printf( "%.12f %.12f\n" , lft , rgt );

  if( rgt > +1e8 ) rgt = 1;
  if( lft < -1e8 ) lft = 0;

  ans = max( ans , norm( p1 - p2 ) * (rgt - lft) );
}
double ang( const Pt& p1 , const Pt& p2 ){
  double ret = acos( (p1 * p2) / norm( p1 ) / norm( p2 ) );
  if( (p1 ^ p2) < 0 ) return -ret;
  return ret;
}
bool in_poly( const Pt& pp ){
  for( int i = 0 ; i < n ; i ++ ){
    if( pp == p[ i ] )
      return true;
    if( between( p[ i ] , p[ i + 1 ] , pp ) )
      return true;
  }
  double sum = 0;
  for( int i = 0 ; i < n ; i ++ )
    sum += ang( p[ i ] - pp , p[ i + 1 ] - pp );
  return fabs( sum ) > pi;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < i + n ; j ++ ){
      if( j != i + 1 ){
        bool lft = false , rgt = false;
        for( int k = 0 ; k < n ; k ++ ){
          int ret = side( p[ i ] , p[ j ] , p[ k ] );
          if( ret < 0 ) lft = true;
          if( ret > 0 ) rgt = true;
        }
        if( not lft or
            not rgt )
          continue;
        Pt mid = (p[ i ] + p[ j ]);
        mid.X >>= 1;
        mid.Y >>= 1;
        if( not in_poly( mid ) )
          continue;
      }
      go( p[ i ] , p[ j ] );
    }
  printf( "%.12f\n" , ans * .5 );
}
int main(){
  init();
  solve();
}
