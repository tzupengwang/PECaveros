#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef double type;
typedef pair<int,int> PII;
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
void scan( PII& tp ){
  scanf( "%d%d" , &tp.X , &tp.Y );
}
int n[ 2 ];
vector< PII > p[ 2 ];
vector< pair<int,Pt> > fz[ 2 ];
void init(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%d" , &n[ i ] );
    p[ i ].resize( n[ i ] );
    for( int j = 0 ; j < n[ i ] ; j ++ )
      scan( p[ i ][ j ] );
  }
}
void evaluate( int xn , const vector< PII >& pp ,
               vector< pair<int,Pt> >& fzz ){
  vector< pair<int , Pt> > vv;
  vector< int > zz;
  for( int i = 1 ; i < xn ; i ++ ){
    if( pp[ i ].Y == pp[ i - 1 ].Y ) continue;
    type a = (type)( pp[ i ].X - pp[ i - 1 ].X ) /
             (type)( pp[ i ].Y - pp[ i - 1 ].Y );
    type b = pp[ i ].X - a * pp[ i ].Y;
    // printf( "%.6f %.6f\n" , a , b );
    vv.push_back( { pp[ i - 1 ].Y , { -a , -b } } );
    vv.push_back( { pp[ i     ].Y , { +a , +b } } );
    zz.push_back( pp[ i ].Y );
  }
  sort( vv.begin() , vv.end() );
  sort( zz.begin() , zz.end() );
  zz.resize( unique( zz.begin() , zz.end() ) - zz.begin() );
  size_t ptr = 0;
  Pt tp = { 0 , 0 };
  for( size_t i = 1 ; i < zz.size() ; i ++ ){
    while( ptr < vv.size() && vv[ ptr ].first < zz[ i ] )
      tp = tp + vv[ ptr ++ ].second;
    fzz.push_back( { zz[ i ] , tp } );
  }
}
inline Pt cal( size_t& ptr , const vector<pair<int,Pt>>& fzz , int tz ){
  while( ptr + 1 < fzz.size() &&
         fzz[ ptr ].first < tz ) ptr ++;
  return fzz[ ptr ].second;
}
void solve(){
  vector<int> zz;
  int mxy[ 2 ] = { 0 , 0 };
  for( int i = 0 ; i < 2 ; i ++ ){
    evaluate( n[ i ] , p[ i ] , fz[ i ] );
    for( int j = 0 ; j < n[ i ] ; j ++ ){
      zz.push_back( p[ i ][ j ].Y );
      mxy[ i ] = max( mxy[ i ] , p[ i ][ j ].Y );
    }
  }
  if( mxy[ 0 ] != mxy[ 1 ] ){
    puts( "Invalid plan" );
    exit( 0 );
  }
  sort( zz.begin() , zz.end() );
  zz.resize( unique( zz.begin() , zz.end() ) - zz.begin() );
  type ans = 0.0;
  size_t p1 = 0 , p2 = 0;
  for( size_t i = 1 ; i < zz.size() ; i ++ ){
    Pt f_1 = cal( p1 , fz[ 0 ] , zz[ i ] );
    Pt f_2 = cal( p2 , fz[ 1 ] , zz[ i ] );
    // printf( "(%d,%d) : %.6fx+%.6f %.6fx+%.6f\n" , zz[ i - 1 ] , zz[ i ] ,
                // f_1.X , f_1.Y , f_2.X , f_2.Y );
    type alpha = f_1.X;
    type beta  = f_1.Y;
    type gamma = f_2.X;
    type delta = f_2.Y;
    type a     = zz[ i - 1 ];
    type b     = zz[ i     ];
    ans += alpha * gamma * ( b * b * b - a * a * a ) / 3.0 +
           ( alpha * delta + beta * gamma ) * ( b * b - a * a ) / 2.0 +
           beta * delta * ( b - a );
  }
  printf( "%.9f\n" , ans );
}
int main(){
  freopen( "lonely.in" , "r" , stdin );
  freopen( "lonely.out" , "w" , stdout );
  init();
  solve();
}
