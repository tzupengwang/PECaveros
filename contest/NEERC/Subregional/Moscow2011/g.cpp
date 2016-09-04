#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
const type eps = 1e-8;
#define D type
#define X first
#define Y second
#define O first
#define R second
bool equal( const type& t1 , const type& t2 ){
  return fabs( t1 - t2 ) < eps;
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
#define N 3030
int n , ptr;
type h[ N ] , r[ N ] , maxh , minh;
typedef pair<type,type> PII;
vector< PII > vv;
type cl[ N ] , cr[ N ];
Pt interCircle( Pt o1 , D r1 , Pt o2 , D r2 ){
  D d2 = ( o1 - o2 ) * ( o1 - o2 );
  D d = sqrt(d2);
	if( d < fabs( r1 - r2 ) + eps ) return { -1e9 , -1e9 };
  Pt u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  D A = sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
  Pt v = Pt( o1.Y-o2.Y , -o1.X + o2.X ) * A / (2*d2);
  return u+v;
}
void shrink(){
  for( int i = 0 ; i < n ; i ++ ){
    cl[ i ] = vv[ i ].first - vv[ i ].second;
    cr[ i ] = vv[ i ].first + vv[ i ].second;
    for( int j = 0 ; j < i ; j ++ ){
      type lmst = vv[ j ].first + vv[ j ].second;
      type rmst = vv[ i ].first - vv[ i ].second;
      if( lmst < rmst ) continue;
      Pt res = interCircle( { vv[ i ].first , 0 } , vv[ i ].second ,
                                    { vv[ j ].first , 0 } , vv[ j ].second );
      if( res.X < -1e8 ){
        if( vv[ i ].second < vv[ j ].second ){
          cl[ i ] = 1e9;
          cr[ i ] = -1e9;
        }
      }else
        cl[ i ] = max( cl[ i ] , res.X );
    }
    for( int j = i + 1 ; j < n ; j ++ ){
      type rmst = vv[ j ].first - vv[ j ].second;
      type lmst = vv[ i ].first + vv[ i ].second;
      if( lmst < rmst ) continue;
      Pt res = interCircle( { vv[ i ].first , 0 } , vv[ i ].second ,
                                    { vv[ j ].first , 0 } , vv[ j ].second );
      if( res.X < -1e8 ){
        if( vv[ i ].second < vv[ j ].second ){
          cl[ i ] = 1e9;
          cr[ i ] = -1e9;
        }
      }else
        cr[ i ] = min( cr[ i ] , res.X );
    }
  }
  // vector< PII > res;
  // for( size_t i = 0 ; i < vv.size() ; i ++ ){
    // if( cl[ i ] > cr[ i ] - eps ) continue;
    // cl[ (int)res.size() ] = cl[ i ];
    // cr[ (int)res.size() ] = cr[ i ];
    // res.push_back( vv[ i ] );
  // }
  // vv = res;
  // n = (int)vv.size();
}
void init(){
  scanf( "%d" , &n );
  minh = 1000000 , maxh = -1000000;
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%lf%lf" , &h[ i ] , &r[ i ] );
    h[ i ] *= 12;
    r[ i ] *= 7 * 24;
    minh = min( minh , h[ i ] - r[ i ] );
    maxh = max( maxh , h[ i ] + r[ i ] );
    vv.push_back( { h[ i ] , r[ i ] } );
  }
  sort( vv.begin() , vv.end() );
  minh = max( minh , 0.0 );
  shrink();
}
#define K 5000000
type stp;
const type pi = acos( -1.0 );
inline type ht( type x , int i ){
  type dst = fabs( vv[ i ].first - x );
  if( dst > vv[ i ].second - eps ) return 0.0;
  type th = sqrt( vv[ i ].second * vv[ i ].second - dst * dst );
  return th;
}
inline type f( type x ){
  type hst = 0.0 , nr = 0.0 , nx = 0.0;
  while( ptr + 1 < n ){
    if( cl[ ptr + 1 ] > x - eps )
      ptr ++;
    else break;
  }
  printf( "%.6f %d\n" , x , ptr );
  hst = ht( x , ptr );
  nr = vv[ ptr ].second;
  nx = x - vv[ ptr ].first;
  if( hst < eps ) return 0.0;
  type ret = 2.0 * pi * hst * sqrt( ( nr * nr ) / ( nr * nr - nx * nx ) );
  return ret;
}
inline type cal( type a , type b ){
  type ret1 = f( a );
  type ret2 = f( ( a + b ) * 0.5 );
  type ret3 = f( b );
  return ( b - a ) * ( ret1 + 4.0 * ret2 + ret3 ) / 6.0;
}
void solve(){
  type ans = 0;
  // type s = minh , t = maxh;
  // stp = ( t - s ) / K;
  // for( int i = 0 ; i < K ; i ++ ){
    // ans += cal( s , s + stp );
    // s += stp;
  // }
  for( int i = 0 ; i < n ; i ++ ){
    cl[ i ] = max( cl[ i ] , 0.0 );
    cr[ i ] = max( cr[ i ] , 0.0 );
    if( cl[ i ] > cr[ i ] - eps ) continue;
    ans += 2.0 * pi * vv[ i ].second * ( cr[ i ] - cl[ i ] );
  }
  printf( "%.9f\n" , ans / 144.0 );
}
int main(){
  init();
  solve();
}
