#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Ln;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const type pi = acos( -1.0 );
const type eps = 1e-7;
bool equal( const type& t1 , const type& t2 ){
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
bool operator==( const Pt& p1 , const Pt& p2 ){
  return equal( p1.X , p2.X ) &&
         equal( p1.Y , p2.Y );
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
inline type dist( const Pt& tp , const Ln& tl ){
  Pt on = tl.first +
          ( tl.second - tl.first ) * 
          ( ( tp - tl.first ) * ( tl.second - tl.first ) / norm2( tl.second - tl.first ) );
  return norm( on - tp );
}
struct Poly{
  int n;
#define N 111
  int r[ N ] , phi[ N ];
  type minr , maxr;
  type dr[ N ] , da[ N ];
  Pt p[ N ];
  void init(){
    scanf( "%d" , &n );
    for( int i = 0 ; i < n ; i ++ ){
      scanf( "%d%d" , &r[ i ] , &phi[ i ] );
      dr[ i ] = r[ i ];
      da[ i ] = phi[ i ];
      p[ i ] = { cos( da[ i ] / 180.0 * pi ) * dr[ i ] ,
                 sin( da[ i ] / 180.0 * pi ) * dr[ i ] };
    }
    dr[ n ] = dr[ 0 ];
    da[ n ] = da[ 0 ];
    p[ n ] = p[ 0 ];
    minr = maxr = dr[ 0 ];
    for( int i = 1 ; i < n ; i ++ ){
      minr = min( minr , dr[ i ] );
      maxr = max( maxr , dr[ i ] );
    }
    for( int i = 0 ; i < n ; i ++ ){
      type vl = ( ( make_pair( 0 , 0 ) - p[ i ] ) * ( p[ i + 1 ] - p[ i ] ) ) /
                norm2( p[ i + 1 ] - p[ i ] );
      if( vl < 0.0 || vl > 1.0 ) continue;
      minr = min( minr , dist( { 0 , 0 } , { p[ i ] , p[ i + 1 ] } ) );
    }
  }
} ib , ip , op;
inline Poly operator+( const Poly& np , const type& deg ){
  Poly tp;
  tp.n = np.n;
  for( int i = 0 ; i < tp.n ; i ++ ){
    tp.dr[ i ] = np.r[ i ];
    tp.da[ i ] = (type)np.phi[ i ] + deg;
    tp.p[ i ] = { cos( tp.da[ i ] / 180.0 * pi ) * tp.dr[ i ] ,
                  sin( tp.da[ i ] / 180.0 * pi ) * tp.dr[ i ] };
  }
  tp.dr[ tp.n ] = tp.dr[ 0 ];
  tp.da[ tp.n ] = tp.da[ 0 ];
  tp.p[ tp.n ] = tp.p[ 0 ];
  return tp;
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt( nan(""), nan("") );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
inline type reg( type ang ){
  while( ang < -pi ) ang += 2.0 * pi;
  while( ang > +pi ) ang -= 2.0 * pi;
  return ang;
}
inline type angl( const Pt& tp ){
  return atan2( tp.Y , tp.X );
}
inline bool in_poly( const Poly& p1 , const Pt& tp ){
  for( int i = 0 ; i < p1.n ; i ++ ){
    if( p1.p[ i ] == tp )
      return true;
    if( equal( ( ( tp - p1.p[ i ] ) ^ ( p1.p[ i + 1 ] - p1.p[ i ] ) ) , 0.0 ) )
      return true;
  }
  type sum = 0.0;
  for( int i = 0 ; i < p1.n ; i ++ )
    sum += reg( angl( p1.p[ i + 1 ] - tp ) - angl( p1.p[ i ] - tp ) );
  return fabs( sum ) > pi;
}
inline bool out_poly( const Poly& p1 , const Pt& tp ){
  for( int i = 0 ; i < p1.n ; i ++ ){
    if( p1.p[ i ] == tp )
      return true;
    if( equal( ( ( tp - p1.p[ i ] ) ^ ( p1.p[ i + 1 ] - p1.p[ i ] ) ) , 0.0 ) )
      return true;
  }
  type sum = 0.0;
  for( int i = 0 ; i < p1.n ; i ++ )
    sum += reg( angl( p1.p[ i + 1 ] - tp ) - angl( p1.p[ i ] - tp ) );
  return fabs( sum ) < pi;
}
// inline Pt to_Pt( type deg , type r ){
  // return { cos( deg / 180.0 * pi ) * r , sin( deg / 180.0 * pi ) * r };
// }
// inline type farfar( type qdeg , const vector< pair<type,type> >& vv , size_t& ptr ){
  // while( ptr + 1 < vv.size() &&
         // vv[ ptr + 1 ].first < qdeg ) ptr ++;
  // Pt jiou = interPnt( to_Pt( vv[ ptr ].first , vv[ ptr ].second ) ,
                      // to_Pt( vv[ ptr + 1 ].first , vv[ ptr + 1 ].second ) ,
                      // { 0 , 0 } ,
                      // to_Pt( qdeg , 1 ) );
  // return norm( jiou );
// }
// inline bool gogogo( const type& ndeg ){
  // op = ip + ndeg;
  // vector< pair< type , type > > vb , vi;
  // vector< type > vv;
  // for( int i = 0 ; i < ib.n ; i ++ ){
    // vb.push_back( { ib.da[ i ] , ib.dr[ i ] } );
    // vv.push_back( ib.da[ i ] );
  // }
  // for( int i = 0 ; i < op.n ; i ++ ){
    // vi.push_back( { op.da[ i ] , op.dr[ i ] } );
    // vv.push_back( op.da[ i ] );
  // }
  // sort( vb.begin() , vb.end() );
  // sort( vi.begin() , vi.end() );
  // size_t bsz = vb.size() , isz = vi.size();
  // for( size_t i = 0 ; i < bsz ; i ++ )
    // vb.push_back( vb[ i ] );
  // for( size_t i = 0 ; i < isz ; i ++ )
    // vi.push_back( vi[ i ] );
  // sort( vv.begin() , vv.end() );
  // size_t ptrb = 0 , ptri = 0;
  // for( size_t i = 0 ; i < vv.size() ; i ++ ){
    // type d1 = farfar( vv[ i ] , vb , ptrb );
    // type d2 = farfar( vv[ i ] , vi , ptri );
    // if( d1 < d2 - eps ) return false;
  // }
  // return true;
// }
inline bool gogogo( const type& ndeg ){
  op = ip + ndeg;
  for( int i = 0 ; i < ib.n ; i ++ )
    if( !out_poly( op , ib.p[ i ] ) )
      return false;
  for( int i = 0 ; i < op.n ; i ++ )
    if( !in_poly( ib , op.p[ i ] ) )
      return false;
  return true;
}
inline bool okay( const Poly& b , const Poly& p ){
  for( int i = 0 ; i < b.n ; i ++ )
    for( int j = 0 ; j < p.n ; j ++ ){
      // point of b with edge of p
      type dst = dist( { 0 , 0 } , { p.p[ j ] , p.p[ j + 1 ] } );
      if( dst > b.dr[ i ] + eps ) continue;
      type vv = ( make_pair( 0 , 0 ) - p.p[ j ] ) * ( p.p[ j + 1 ] - p.p[ j ] ) /
                norm2( p.p[ j + 1 ] - p.p[ j ] );
      Pt on = p.p[ j ] + ( p.p[ j + 1 ] - p.p[ j ] ) * vv;
      dst = sqrt( max( eps , b.dr[ i ] * b.dr[ i ] - dst * dst ) );
      Pt p1 = on + ( p.p[ j + 1 ] - p.p[ j ] ) * dst / norm( p.p[ j + 1 ] - p.p[ j ] );
      Pt p2 = on - ( p.p[ j + 1 ] - p.p[ j ] ) * dst / norm( p.p[ j + 1 ] - p.p[ j ] );
      type ang1 = angl( p1 ) , ang2 = angl( p2 );
      type oang = angl( b.p[ i ] );
      ang1 -= oang;
      ang2 -= oang;
      if( gogogo( ang1 / pi * 180.0 ) || gogogo( -ang1 / pi * 180.0 ) )
        return true;
      if( gogogo( ang2 / pi * 180.0 ) || gogogo( -ang2 / pi * 180.0 ) )
        return true;
    }
  return false;
}
inline bool okay(){
  if( ib.minr > ip.maxr - eps )
    return false;
#define K 19800
  for( int i = 0 ; i < K ; i ++ )
    if( gogogo( 360 * (type)i / K ) )
      return true;
  return okay( ib , ip ) || okay( ip , ib );
}
int n , r;
void init(){
  scanf( "%d%d" , &n , &r );
  ib.init();
}
void solve(){
  vector< int > ans;
  for( int i = 1 ; i <= n ; i ++ ){
    ip.init();
    if( okay() )
      ans.push_back( i );
  }
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "gtaw.in" , "r" , stdin );
  freopen( "gtaw.out" , "w" , stdout );
#endif
  init();
  solve();
}
