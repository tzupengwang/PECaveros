#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
typedef double type;
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
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2, bool& res){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return Pt( nan(""), nan("") );
  }
  res = true;
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
#define N 111
int n;
double x[ N ] , h[ N ] , b[ N ];
Pt get_l( int id ){
  return { x[ id ] - b[ id ] * .5 , 0 };
}
Pt get_c( int id ){
  return { x[ id ] , h[ id ] };
}
Pt get_r( int id ){
  return { x[ id ] + b[ id ] * .5 , 0 };
}
void init(){
  for( int i = 0 ; i < n ; i ++ )
    cin >> x[ i ] >> h[ i ] >> b[ i ];
}
vector<double> cand , mx;
Pt lp[ N ] , cp[ N ] , rp[ N ];
void upd( const Pt& p1 , const Pt& p2 , double xx , double& mxy ){
  if( xx < p1.X or xx > p2.X ) return;
  double cy = p1.Y + (p2.Y - p1.Y) * (xx - p1.X) / (p2.X - p1.X);
  mxy = max( mxy , cy );
}
int _cs;
void solve(){
  cand.clear();
  mx.clear();
  for( int i = 0 ; i < n ; i ++ ){
    lp[ i ] = get_l( i );
    cp[ i ] = get_c( i );
    rp[ i ] = get_r( i );
  }
  for( int i = 0 ; i < n ; i ++ ){
    cand.push_back( x[ i ] - b[ i ] * .5 );
    cand.push_back( x[ i ] + b[ i ] * .5 );
    cand.push_back( x[ i ] );
    for( int j = i + 1 ; j < n ; j ++ ){
      {
        bool res;
        Pt ret = interPnt( lp[ i ] , cp[ i ] , lp[ j ] , cp[ j ] , res );
        if( res )
          cand.push_back( ret.X );
      }
      {
        bool res;
        Pt ret = interPnt( lp[ i ] , cp[ i ] , rp[ j ] , cp[ j ] , res );
        if( res )
          cand.push_back( ret.X );
      }
      {
        bool res;
        Pt ret = interPnt( rp[ i ] , cp[ i ] , lp[ j ] , cp[ j ] , res );
        if( res )
          cand.push_back( ret.X );
      }
      {
        bool res;
        Pt ret = interPnt( rp[ i ] , cp[ i ] , rp[ j ] , cp[ j ] , res );
        if( res )
          cand.push_back( ret.X );
      }
    }
  }
  sort( cand.begin() , cand.end() );
  for( size_t i = 0 ; i < cand.size() ; i ++ ){
    double tmx = 0;
    for( int j = 0 ; j < n ; j ++ ){
      upd( lp[ j ] , cp[ j ] , cand[ i ] , tmx );
      upd( cp[ j ] , rp[ j ] , cand[ i ] , tmx );
    }
    mx.push_back( tmx );
  }
  double ans = 0;
  for( size_t i = 1 ; i < cand.size() ; i ++ )
    if( mx[ i ] > eps or mx[ i - 1 ] > eps ){
      ans += norm( Pt( cand[ i - 1 ] , mx[ i - 1 ] ) -
                   Pt( cand[ i ] , mx[ i ] ) );
    }
  printf( "Case %d: %lld\n\n" , ++ _cs , (long long)(ans + .5) );
}
int main(){
  while( cin >> n and n ){
    init();
    solve();
  }
}
