#include <bits/stdc++.h>
using namespace std;
typedef double type;
const type eps = 1e-7;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define PB push_back
#define X first
#define Y second
#define O first
#define R second
#define FI first
#define SE second
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
vector<Line> halfPlaneInter( vector<Line> lines ){
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
  return res;
}
void print( const Pt& tp ){
  printf( "(%.6f,%.6f)" , tp.X , tp.Y );
}
bool scan( Pt &tp ){
  return ( scanf( "%lf%lf" , &tp.X , &tp.Y ) == 2 );
}
double cal( const vector<Line>& vv ){
  if( vv.size() < 3 ) return 0.;
  vector<Pt> tp;
  bool res = true;
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    tp.push_back( interPnt( vv[ i ] , vv[ (i + 1) % vv.size() ] , res ) );
  double area = 0.0;
  for( size_t i = 0 ; i < tp.size() ; i ++ )
    area += ( tp[ i ] ^ tp[ (i + 1) % tp.size() ] );
  return fabs( area ) * 0.5;
}
Pt p[ 4 ];
int main(){
  while( scan( p[ 0 ] ) ){
    for( int i = 1 ; i < 4 ; i ++ )
      scan( p[ i ] );
    double tot = 5 * 5 * 5 - 1 * 1 * 1;
    double vl = 5 * ( 5 * 5 * 4 );
    { // 1
      vector<Line> vv;
      for( int i = 0 ; i < 4 ; i ++ )
        vv.push_back( { p[ i ] , p[ ( i + 1 ) % 4 ] } );
      vv.push_back( { { 1 , -0.5 } , { -1 , -0.5 } } );
      vector<Line> res = halfPlaneInter( vv );
      double area = cal( res );
      //printf( "1 : %.12f\n" , area );
      vl += area * 5 * 1;
    }
    { // 3
      vector<Line> vv;
      for( int i = 0 ; i < 4 ; i ++ )
        vv.push_back( { p[ i ] , p[ ( i + 1 ) % 4 ] } );
      vv.push_back( { { 0.5 , 1 } , { 0.5 , -1 } } );
      vector<Line> res = halfPlaneInter( vv );
      double area = cal( res );
      //printf( "3 : %.12f\n" , area );
      vl += area * 5 * 3;
    }
    { // 6
      vector<Line> vv;
      for( int i = 0 ; i < 4 ; i ++ )
        vv.push_back( { p[ i ] , p[ ( i + 1 ) % 4 ] } );
      vv.push_back( { { -1 , 0.5 } , { 1 , 0.5 } } );
      vector<Line> res = halfPlaneInter( vv );
      double area = cal( res );
      //printf( "6 : %.12f\n" , area );
      vl += area * 5 * 6;
    }
    { // 4
      vector<Line> vv;
      for( int i = 0 ; i < 4 ; i ++ )
        vv.push_back( { p[ i ] , p[ ( i + 1 ) % 4 ] } );
      vv.push_back( { { -0.5 , -1 } , { -0.5 , 1 } } );
      vector<Line> res = halfPlaneInter( vv );
      double area = cal( res );
      //printf( "4 : %.12f\n" , area );
      vl += area * 5 * 4;
    }
    vl /= tot;
    printf( "%.12f\n" , vl );
  }
}
