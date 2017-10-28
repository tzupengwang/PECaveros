#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double type;
typedef pair<LL,LL> Pt;
typedef pair<double,double> Pdt;
typedef pair<Pdt,Pdt> Line;
const double eps = 1e-7;
const LL inf = 2000000000;
#define X first
#define Y second
#define FI first
#define SE second
#define PB push_back
Pdt operator+( const Pdt& p1 , const Pdt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pdt operator-( const Pdt& p1 , const Pdt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pdt operator*( const Pdt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pdt operator/( const Pdt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pdt& p1 , const Pdt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pdt& p1 , const Pdt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pdt& tp ){
  return tp * tp;
}
double norm( const Pdt& tp ){
  return sqrt( norm2( tp ) );
}
Pdt perp( const Pdt& tp ){
  return { tp.Y , -tp.X };
}
#define N 222
inline void scan( Pt& pp ){
  scanf( "%lld%lld" , &pp.X , &pp.Y );
}
Pdt interPnt( Line l1, Line l2, bool &res ){
  Pdt p1, p2, q1, q2;
  tie(p1, p2) = l1;
  tie(q1, q2) = l2;
  double f1 = (p2 - p1) ^ (q1 - p1);
  double f2 = (p2 - p1) ^ (p1 - q2);
  double f = (f1 + f2);
  if( fabs(f) < eps)
  { res = false; return {0, 0}; }
  res = true;
  return q1 * (f2 / f) + q2 * (f1 / f);
}
bool isin( Line l0, Line l1, Line l2 ){
  // Check inter(l1, l2) in l0
  bool res;
  Pdt p = interPnt(l1, l2, res);
  return ( (l0.SE - l0.FI) ^ (p - l0.FI) ) > eps;
}
/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F) ^ (p - l.F) > 0
 */
/* --^-- Line.FI --^-- Line.SE --^-- */
vector<Line> halfPlaneInter( vector<Line> lines ){
  int sz = lines.size();
  vector<double> ata(sz), ord(sz);
  for( int i=0; i<sz; i++) {
    ord[i] = i;
    Pdt d = lines[i].SE - lines[i].FI;
    ata[i] = atan2(d.Y, d.X);
  }
  sort( ord.begin(), ord.end(), [&](int i, int j) {
    if( fabs(ata[i] - ata[j]) < eps )
      return ( (lines[i].SE - lines[i].FI) ^
               (lines[j].SE - lines[i].FI) ) < 0;
    return ata[i] < ata[j];
  });
  vector<Line> fin;
  for (int i=0; i<sz; i++)
    if (!i or fabs(ata[ord[i]] - ata[ord[i-1]]) > eps)
      fin.PB(lines[ord[i]]);
  deque<Line> dq;
  for (int i=0; i<(int)(fin.size()); i++) {
    while((int)(dq.size()) >= 2 and 
        not isin(fin[i], dq[(int)(dq.size())-2],
                         dq[(int)(dq.size())-1])) 
      dq.pop_back();
    while((int)(dq.size()) >= 2 and 
        not isin(fin[i], dq[0], dq[1]))
      dq.pop_front();
    dq.push_back(fin[i]);
  }
  while( (int)(dq.size()) >= 3 and
      not isin(dq[0], dq[(int)(dq.size())-2],
                      dq[(int)(dq.size())-1]))
    dq.pop_back();
  while( (int)(dq.size()) >= 3 and
      not isin(dq[(int)(dq.size())-1], dq[0], dq[1])) 
    dq.pop_front();
  vector<Line> res(dq.begin(),dq.end());
  return res;
}
Pdt interPnt( Pdt p1, Pdt p2, Pdt q1, Pdt q2 , bool& res){
  double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
  double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
  double f = ( f1 + f2 );
  if( fabs( f ) < eps ){
    res = false;
    return Pdt( 0 , 0 );
  }
  res = true;
    return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
int n;
Pt l , r , p[ N ];
void init(){
  scan( l );
  scan( r );
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
inline LL sqr( LL x ){
  return x * x;
}
inline double sqr( double x ){
  return x * x;
}
int ans;
//inline LL nd_r( const Pt& pp , const Pt& oo ){
  //LL dd = sqr( pp.X - oo.X ) + sqr( pp.Y - oo.Y );
  ////LL pos = max( 1LL , (LL)( sqrtl( dd ) - 1 ) );
  ////while( pos * pos <= dd ) pos ++;
  ////return pos;
  //LL bl = 1 , br = inf , ba = br;
  //while( bl <= br ){
    //LL bmid = (bl + br) >> 1;
    //if( bmid * bmid > dd ) ba = bmid , br = bmid - 1;
    //else bl = bmid + 1;
  //}
  //return ba;
//}
inline LL nd_r( const Pdt& pp , const Pdt& oo ){
  double dd = sqr( pp.X - oo.X ) + sqr( pp.Y - oo.Y );
  LL pos = max( 1LL , (LL)( sqrtl( dd ) - 1 ) );
  while( pos * pos <= dd ) pos ++;
  return pos;
  //LL bl = 1 , br = inf , ba = br;
  //while( bl <= br ){
    //LL bmid = (bl + br) >> 1;
    //if( bmid * bmid > dd ) ba = bmid , br = bmid - 1;
    //else bl = bmid + 1;
  //}
  //return ba;
}
inline int find_best( const Pdt& pp ){
  int bst = inf;
  for( int i = 0 ; i < n ; i ++ )
    bst = min( bst , (int)nd_r( { p[ i ].X , p[ i ].Y } , pp ) );
  return bst;
}
//inline int find_best( const Pt& pp ){
  //int bst = inf;
  //for( int i = 0 ; i < n ; i ++ )
    //bst = min( bst , (int)nd_r( p[ i ] , pp ) );
  //return bst;
//}
vector<Pdt> cand;
Pdt bdr[ 5 ];
void add( const Pdt& pp ){
  double px = pp.X , py = pp.Y;
  for( int dx = -1 ; dx <= 1 ; dx ++ )
    for( int dy = -1 ; dy <= 1 ; dy ++ ){
      double curx = px + dx;
      double cury = py + dy;
      if( curx < l.X or curx > r.X or
          cury < l.Y or cury > r.Y )
        continue;
      cand.push_back( { curx , cury } );
    }
}
inline int cal(){
  cand.clear();
  bdr[ 0 ] = { l.X , l.Y };
  bdr[ 1 ] = { r.X , l.Y };
  bdr[ 2 ] = { r.X , r.Y };
  bdr[ 3 ] = { l.X , r.Y };
  bdr[ 4 ] = { l.X , l.Y };
  add( { l.X , l.Y } );
  add( { l.X , r.Y } );
  add( { r.X , l.Y } );
  add( { r.X , r.Y } );
  add( { ( l.X + r.X ) / 2 , ( l.Y + r.Y ) / 2 } );
  for( int i = 0 ; i < n ; i ++ ){
    /* --^-- Line.FI --^-- Line.SE --^-- */
    vector<Line> vv;
    for( int j = 0 ; j < 4 ; j ++ )
      vv.push_back( { bdr[ j ] , bdr[ j + 1 ] } );
    for( int j = 0 ; j < n ; j ++ ){
      if( i == j ) continue;
      Pdt p1 = p[ i ] , p2 = p[ j ];
      Pdt mid = ( p1 + p2 ) * 0.5;
      Pdt dir = perp( p1 - p2 );
      vv.push_back( { mid , mid + dir } );
    }
    vv = halfPlaneInter( vv );
    if( vv.empty() ) continue;
    vv.push_back( vv[ 0 ] );
    for( size_t j = 0 ; j + 1 < vv.size() ; j ++ ){
      bool tmp;
      Pdt ret = interPnt( vv[ j ].X , vv[ j ].Y , 
                          vv[ j + 1 ].X , vv[ j + 1 ].Y , tmp );
      if( not tmp ) continue;
      add( ret );
    }
  }
  //for( int i = 0 ; i < n ; i ++ )
    //for( int j = i + 1 ; j < n ; j ++ ){
      //Pdt p1( p[ i ].X , p[ i ].Y );
      //Pdt p2( p[ j ].X , p[ j ].Y );
      //Pdt mid = (p1 + p2) * 0.5;
      //add( mid );
      //Pdt dir = perp( p2 - p1 );
      //dir = mid + dir;
      //for( int ii = 0 ; ii < 4 ; ii ++ ){
        //for( int jj = ii + 1 ; jj < 4 ; jj ++ ){
          //bool tmp;
          //Pdt ret = interPnt( mid , dir , bdr[ ii ] , bdr[ jj ] , tmp);
          //if( not tmp ) continue;      
          //add( ret );
        //}
      //}
      //for( int ii = 0 ; ii < 4 ; ii ++ ){
        //for( int jj = ii + 1 ; jj < 4 ; jj ++ ){
          //bool tmp;
          //Pdt ret = interPnt( p1 , p2 , bdr[ ii ] , bdr[ jj ] , tmp);
          //if( not tmp ) continue;      
          //add( ret );
        //}
      //}
    //}
  //sort( cand.begin() , cand.end() );
  //cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
  int tans = 0;
  for( auto i : cand )
    tans = max( tans , find_best( i ) );
  //cerr << tans << endl;;
  return tans;
}
int _cs;
void solve(){
  ans = inf;
  for( int i = 0 ; i < n ; i ++ ){
    LL tans = 0;
    tans = max( tans , nd_r( { l.X , l.Y } , p[ i ] ) );
    tans = max( tans , nd_r( { l.X , r.Y } , p[ i ] ) );
    tans = max( tans , nd_r( { r.X , l.Y } , p[ i ] ) );
    tans = max( tans , nd_r( { r.X , r.Y } , p[ i ] ) );
    ans = min( ans , (int)tans );
  }
  ans = min( ans , (int)cal() );
  printf( "Case #%d: %d\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
