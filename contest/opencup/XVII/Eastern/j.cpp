#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
const double pi = acos( -1.0 );
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
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
void print( const Pt& tp ){
  printf( "(%.4f, %.4f)" , tp.X , tp.Y );
}
double cross(Pt o, Pt a, Pt b){
  return (a-o) ^ (b-o);
}
vector<Pt> convex_hull(vector<Pt> pt){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Pt> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}
Pt rotate( const Pt& tp , double ang ){
  assert( ang > -pi - eps and ang < +pi + eps );
  return { tp.X * cos( ang ) - tp.Y * sin( ang ) ,
           tp.X * sin( ang ) + tp.Y * cos( ang ) };
}
vector<Pt> norm( const vector<Pt>& intv ){
  vector<Pt> ret;
  for( auto i : intv )
    if( i.second - i.first > eps )
      ret.push_back( i );
  return ret;
}
vector<Pt> Union( const vector<Pt>& me , const vector<Pt>& he ){
  vector< pair<double,int> > x;
  for( auto i : me ){
    x.push_back( { i.first  , +1 } );
    x.push_back( { i.second , -1 } );
  }
  for( auto i : he ){
    x.push_back( { i.first  , +1 } );
    x.push_back( { i.second , -1 } );
  }
  sort( x.begin() , x.end() );
  vector<double> tmp;
  int ss = 0;
  for( auto i : x ){
    int ps = ss;
    ss += i.second;
    if( ps == 0 and ss == 1 )
      tmp.push_back( i.first );
    if( ps == 1 and ss == 0 )
      tmp.push_back( i.first );
  }
  vector<Pt> ret;
  for( size_t i = 0 ; i + 1 < tmp.size() ; i += 2 )
    ret.push_back( { tmp[ i ] , tmp[ i + 1 ] } );
  return norm( ret );
}
vector<Pt> Inter( const vector<Pt>& me , const vector<Pt>& he ){
  vector<Pt> ret;
  size_t ptr = 0;
  for( auto i : me ){
    while( ptr < he.size() and he[ ptr ].second < i.first ) ptr ++;
    if( ptr >= he.size() ) break;
    while( ptr < he.size() and he[ ptr ].second < i.second + eps ){
      ret.push_back( { max( i.first , he[ ptr ].first ) ,
                       min( i.second , he[ ptr ].second ) } );
      if( he[ ptr ].second < i.second + eps )
        ptr ++;
    }
    if( ptr < he.size() )
      ret.push_back( { max( i.first , he[ ptr ].first ) ,
                       min( i.second , he[ ptr ].second ) } );
  }
  return norm( ret );
}
vector<Pt> comp( const vector<Pt>& intv ){
  vector<Pt> ret;
  if( intv.empty() )
    return { { -pi , pi } };
  ret.push_back( { -pi , intv[ 0 ].first } );
  for( size_t i = 1 ; i < intv.size() ; i ++ )
    ret.push_back( { intv[ i - 1 ].second ,
                     intv[ i ].first } );
  ret.push_back( { intv.back().second , pi } );
  return norm( intv );
}
double angle( const Pt& tp ){
  return atan2( tp.Y , tp.X );
}
vector<Pt> valid( Pt tl , Pt tr , const Pt& pp ){
  double d1 = norm( tl );
  double d2 = norm( tr );
  double dp = norm( pp );
  double a1 = angle( tl );
  double a2 = angle( tr );
  if( d1 > d2 ){
    swap( a1 , a2 );
    swap( d1 , d2 );
    swap( tl , tr );
  }
  if( d1 > dp - eps ) return { { -pi , pi } };
  if( d2 < dp - eps ) return { { -pi , a1 } , { a2 , pi } };
  double vv = ( tl * ( tl - tr ) ) / norm( tl - tr );
  double dd = sqrt( d1 * d1 - vv * vv );
  Pt to = perp( tl - tr );
  if( ( to * tl ) < 0 ) to = to * -1;
  Pt on = to * ( dd / norm( to ) );
  double dlt = sqrt( dp * dp - dd * dd );
  Pt op = tl - tr;
  Pt border1 = on + ( op * ( dlt / norm( op ) ) );
  Pt border2 = on - ( op * ( dlt / norm( op ) ) );
  double ba1 = angle( border1 );
  double ba2 = angle( border2 );
  if( ba1 > ba2 )
    swap( ba1 , ba2 );
  if( ba2 - ba1 < pi ){
    a1 = max( a1 , ba1 );
    a2 = min( a2 , ba2 );
    return { { -pi , a1 } , { a2 , pi } };
  }
  a1 = min( a1 , ba1 );
  a2 = max( a2 , ba2 );
  return { { a1 , a2 } };
}
int n , l;
vector<Pt> v;
void init(){
  scanf( "%d%d" , &n , &l );
  v.clear();
  for( int i = 0 ; i < n ; i ++ ){
    Pt tmp;
    scan( tmp );
    if( norm( tmp ) < sqrt( 3 ) * l / 2 + eps )
      continue;
    else
      v.push_back( tmp );
  }
  v = convex_hull( v );
}
void solve(){
  vector<Pt> ok = { { -pi , pi } };
  int sz = (int)v.size();
  for( int i = 0 ; i < sz and not ok.empty() ; i ++ ){
    Pt pp[ 3 ];
    pp[ 0 ] = { l , 0 };
    pp[ 1 ] = { 3. * l / 2. , sqrt( 3 ) * l / 2. };
    pp[ 2 ] = { l / 2. , sqrt( 3 ) * l / 2. };
    for( int rot = 0 ; rot < 6 ; rot ++ ){
      for( int k = 0 ; k < 2 ; k ++ ){
        vector<Pt> tint = valid( pp[ k ] , pp[ k + 1 ] , v[ i ] );
        ok = Inter( ok , tint );
      }
      for( int j = 0 ; j < 3 ; j ++ )
        pp[ j ] = rotate( pp[ j ] , pi / 3. );
    }
    /*****************************************/
    for( int rot = 0 ; rot < 6 ; rot ++ ){
      vector<Pt> tint = comp( valid( v[ i ] , v[ ( i + 1 ) % sz ] , pp[ 0 ] ) );
      ok = Inter( ok , tint );
      pp[ 0 ] = rotate( pp[ 0 ] , pi / 3. );
    }
  }
  if( ok.size() )
    puts( "Cast" );
  else
    puts( "Change" );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
