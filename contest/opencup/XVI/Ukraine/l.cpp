#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef LL type;
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
LL cross(Pt o, Pt a, Pt b){
  return (a-o) ^ (b-o);
}
vector<Pt> convex_hull(vector<Pt> pt){
  sort(pt.begin(), pt.end());
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
  stk.push_back(stk[0]);
  return stk;
}
int ori( const Pt& o , const Pt& a , const Pt& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) <= 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) <= 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) <= 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) <= 0;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 )<=0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 )<=0);
}
void scan( Pt& pt ){
  scanf( "%lld%lld" , &pt.X , &pt.Y );
}
#define N 514
int n , m , k , clr[ N ];
Pt u[ N ];
double cal( const vector<Pt>& vv ){
  vector<Pt> ch = convex_hull( vv );
  bool got[ 9 ] = {};
  int gt = 0;
  for( int i = 0 ; i < n and gt < k ; i ++ ){
    if( got[ clr[ i ] ] ) continue;
    int cc = 0;
    Pt op = u[ i ] + make_pair( 233332 , 1 );
    for( size_t j = 0 ; j + 1 < ch.size() ; j ++ )
      if( banana( u[ i ] , op , ch[ j ] , ch[ j + 1 ] ) )
        cc ++;
    if( cc % 2 ){
      got[ clr[ i ] ] = true;
      gt ++;
    }
  }
  if( gt >= k ){
    double slen = 0;
    for( size_t j = 0 ; j + 1 < ch.size() ; j ++ )
      slen += norm( ch[ j + 1 ] - ch[ j ] );
    return slen;
  }
  return -1;
}
int cal_mask( const vector<Pt>& vv ){
  int msk = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( ( msk >> clr[ i ] ) & 1 ) continue;
    int cc = 0;
    Pt op = u[ i ] + make_pair( 233332 , 1 );
    for( size_t j = 0 ; j + 1 < vv.size() ; j ++ )
      if( banana( u[ i ] , op , vv[ j ] , vv[ j + 1 ] ) )
        cc ++;
    if( cc % 2 )
      msk |= ( 1 << clr[ i ] );
  }
  return msk;
}
vector<Pt> vv;
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 0 ; i < n ; i ++ )
    scan( u[ i ] );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d" , &clr[ i ] );
    clr[ i ] --;
  }
  for( int i = 0 ; i < m ; i ++ ){
    Pt tp; scan( tp );
    vv.push_back( tp );
  }
}
const double inf = 1e20;
double ans;
#define M 44
double dp[ M ][ M ][ 1 << 6 ];
int tri[ M ][ M ][ M ];
void solve(){
  ans = cal( vv );
  if( ans < 0 ){
    puts( "-1" );
    return;
  }
  sort( vv.begin() , vv.end() );
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      for( int jj = 0 ; jj < m ; jj ++ )
        tri[ i ][ j ][ jj ] = cal_mask( { vv[ i ] , vv[ j ] ,
                                          vv[ jj ] , vv[ i ] } );       
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      for( int mm = 0 ; mm < ( 1 << k ) ; mm ++ )
        dp[ i ][ j ][ mm ] = inf;
  for( int i = 0 ; i < m ; i ++ )
    for( int j = i + 1 ; j < m ; j ++ )
      for( int jj = j + 1 ; jj < m ; jj ++ ){
        int nmsk = tri[ i ][ j ][ jj ];
        double cst = norm( vv[ i ] - vv[ j ] ) +
                     norm( vv[ j ] - vv[ jj ] ) +
                     norm( vv[ jj ] - vv[ i ] );
        dp[ i ][ j ][ nmsk ] = min( dp[ i ][ j ][ nmsk ] , cst );
        dp[ i ][ jj ][ nmsk ] = min( dp[ i ][ jj ][ nmsk ] , cst );
        dp[ j ][ jj ][ nmsk ] = min( dp[ j ][ jj ][ nmsk ] , cst );
      }
  for( int rep = 0 ; rep < m ; rep ++ ){
    for( int i = 0 ; i < m ; i ++ )
      for( int j = i + 1 ; j < m ; j ++ )
        for( int cur = 0 ; cur < ( 1 << k ) ; cur ++ ){
          if( dp[ i ][ j ][ cur ] > inf / 2 ) continue;
          for( int nj = i ; nj < m ; nj ++ ){
            int nmsk = cur | tri[ i ][ j ][ nj ];
            double ndp = dp[ i ][ j ][ cur ]
                          - norm( vv[ i ] - vv[ j ] )
                          + norm( vv[ i ] - vv[ nj ] ) 
                          + norm( vv[ j ] - vv[ nj ] );
            dp[ j ][ nj ][ nmsk ] = min( dp[ j ][ nj ][ nmsk ] , 
                                         ndp );
            dp[ i ][ nj ][ nmsk ] = min( dp[ i ][ nj ][ nmsk ] , 
                                         ndp );
          }
        }
  }
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      ans = min( ans , dp[ i ][ j ][ ( 1 << k ) - 1 ] );
  printf( "%.12f\n" , ans );
}
int main(){
  init();
  solve();
}
