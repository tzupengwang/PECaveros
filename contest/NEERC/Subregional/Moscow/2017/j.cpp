#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long double type;
#define double long double
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
const double eps = 1e-12;
#define PB push_back
#define FI first
#define SE second
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
void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
  //scanf( "%lf%lf" , &pp.X , &pp.Y );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
Pt interPnt( Line l1, Line l2, bool &res ){
  Pt p1, p2, q1, q2;
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
  Pt p = interPnt(l1, l2, res);
  return ( (l0.SE - l0.FI) ^ (p - l0.FI) ) > eps;
}
/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F) ^ (p - l.F) > 0
 */
/* --^-- Line.FI --^-- Line.SE --^-- */
double halfPlaneInter( vector<Line> lines ){
  int sz = lines.size();
  vector<double> ata(sz), ord(sz);
  for( int i=0; i<sz; i++) {
    ord[i] = i;
    Pt d = lines[i].SE - lines[i].FI;
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

  if( res.size() < 3u ) return 0;
  vector<Pt> vv;
  for( size_t i = 0 ; i < res.size() ; i ++ ){
    bool _res;
    vv.push_back( interPnt( res[ i ] , res[ (i + 1) % res.size() ], _res ) );
  }
  double ret = 0;
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    ret += vv[ i ] ^ vv[ (i + 1) % vv.size() ];
  return fabs( ret );
}
typedef vector< Pt > tri;
void scan( tri& tt ){
  tt.resize( 3 );
  for( int i = 0 ; i < 3 ; i ++ )
    scan( tt[ i ] );
}
void reorder( tri& tt ){
  if( ( ( tt[ 1 ] - tt[ 0 ] ) ^ ( tt[ 2 ] - tt[ 0 ] ) ) < 0 )
    swap( tt[ 1 ] , tt[ 2 ] );
}
#define N 101010
int n;
double w , h;
tri t[ N ];
void init(){
  cin >> n >> w >> h;
  //scanf( "%d%lf%lf" , &n , &w , &h );
  //n = 10000;
  //w = 10000;
  //h = 10000;
  for( int i = 0 ; i < n ; i ++ ){
    scan( t[ i ] );
    //t[ i ].resize( 3 );
    //t[ i ][ 0 ] = { 0 , n - i };
    //t[ i ][ 1 ] = { w , i };
    //t[ i ][ 2 ] = { w , i + 1 };
    reorder( t[ i ] );
  }
}
bool between( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  if( fabs( (p3 - p1) ^ (p2 - p1) ) > eps ) return false;
  return ( (p2 - p1) * (p3 - p1) ) > -eps and
         ( (p2 - p3) * (p1 - p3) ) > -eps;
}
void check( Pt pa ){
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < 3 ; j ++ ){
      if( between( t[ i ][ j ] , pa , t[ i ][ (j + 1) % 3 ] ) )
        assert( false and "between" );
      if( fabs( (pa - t[ i ][ j ]) ^ (t[ i ][ (j + 1) % 3 ] - t[ i ][ j ]) ) < eps )
        break;
    }
    int sgn = 0;
    bool ok = false;
    for( int j = 0 ; j < 3 ; j ++ ){
      double tmp = (pa - t[ i ][ j ]) ^ (pa - t[ i ][ (j + 1) % 3 ]);
      int nsgn = (tmp > eps) - (tmp < -eps);
      if( sgn and nsgn and sgn != nsgn )
        ok = true;
      if( nsgn ) sgn = nsgn;
    }
    assert( ok );
  }
}
#define K 45
void go( double lx , double rx , double ly , double ry , int xx , int yy ){
  if( xx == K and yy == K ){
    Pt ans = { (lx + rx) * .5 , (ly + ry) * .5 };
    //check( ans );
    cout << fixed << setprecision( 9 );
    cout << ans.X << " " << ans.Y << endl;
    //printf( "%.9f %.9f\n" , ans.X , ans.Y );
    exit(0);
  }
  if( xx == yy ){
    double mx = (lx + rx) * .5;
    double lft = 0 , rgt = 0;
    {
      vector<Line> vv;
      vv.resize( 7 );
      vv[ 0 ] = { { lx , ly } , { mx , ly } };
      vv[ 1 ] = { { mx , ly } , { mx , ry } };
      vv[ 2 ] = { { mx , ry } , { lx , ry } };
      vv[ 3 ] = { { lx , ry } , { lx , ly } };
      for( int i = 0 ; i < n ; i ++ ){
        vv[ 4 ] = { t[ i ][ 0 ] , t[ i ][ 1 ] };
        vv[ 5 ] = { t[ i ][ 1 ] , t[ i ][ 2 ] };
        vv[ 6 ] = { t[ i ][ 2 ] , t[ i ][ 0 ] };
        lft += halfPlaneInter( vv );
      }
    }
    {
      vector<Line> vv;
      vv.resize( 7 );
      vv[ 0 ] = { { mx , ly } , { rx , ly } };
      vv[ 1 ] = { { rx , ly } , { rx , ry } };
      vv[ 2 ] = { { rx , ry } , { mx , ry } };
      vv[ 3 ] = { { mx , ry } , { mx , ly } };
      for( int i = 0 ; i < n ; i ++ ){
        vv[ 4 ] = { t[ i ][ 0 ] , t[ i ][ 1 ] };
        vv[ 5 ] = { t[ i ][ 1 ] , t[ i ][ 2 ] };
        vv[ 6 ] = { t[ i ][ 2 ] , t[ i ][ 0 ] };
        rgt += halfPlaneInter( vv );
      }  
    }
    if( lft < rgt )
      go( lx , mx , ly , ry , xx + 1 , yy );
    else
      go( mx , rx , ly , ry , xx + 1 , yy );
  }else{
    double my = (ly + ry) * .5;
    double lft = 0 , rgt = 0;
    {
      vector<Line> vv;
      vv.resize( 7 );
      vv[ 0 ] = { { lx , ly } , { rx , ly } };
      vv[ 1 ] = { { rx , ly } , { rx , my } };
      vv[ 2 ] = { { rx , my } , { lx , my } };
      vv[ 3 ] = { { lx , my } , { lx , ly } };
      for( int i = 0 ; i < n ; i ++ ){
        vv[ 4 ] = { t[ i ][ 0 ] , t[ i ][ 1 ] };
        vv[ 5 ] = { t[ i ][ 1 ] , t[ i ][ 2 ] };
        vv[ 6 ] = { t[ i ][ 2 ] , t[ i ][ 0 ] };
        lft += halfPlaneInter( vv );
      }
    }
    {
      vector<Line> vv;
      vv.resize( 7 );
      vv[ 0 ] = { { lx , my } , { rx , my } };
      vv[ 1 ] = { { rx , my } , { rx , ry } };
      vv[ 2 ] = { { rx , ry } , { lx , ry } };
      vv[ 3 ] = { { lx , ry } , { lx , my } };
      for( int i = 0 ; i < n ; i ++ ){
        vv[ 4 ] = { t[ i ][ 0 ] , t[ i ][ 1 ] };
        vv[ 5 ] = { t[ i ][ 1 ] , t[ i ][ 2 ] };
        vv[ 6 ] = { t[ i ][ 2 ] , t[ i ][ 0 ] };
        rgt += halfPlaneInter( vv );
      }  
    }
    if( lft < rgt )
      go( lx , rx , ly , my , xx , yy + 1 );
    else
      go( lx , rx , my , ry , xx , yy + 1 );
  }
}
void solve(){
  go( 0 , w , 0 , h , 0 , 0 );
}
int main(){
  init();
  solve();
}
