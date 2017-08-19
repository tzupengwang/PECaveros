#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define FI first
#define SE second
#define X first
#define Y second
#define O first
#define R second
#define PB push_back
const double eps = 1e-9;
bool equal( double x , double y ){
  return x - eps < y and y < x + eps;
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
double area( const vector<Line>& ret ){
  if( ret.size() < 3 ) return 0.0;
  double ar = 0;
  vector<Pt> vv;
  for( size_t i = 0 ; i < ret.size() ; i ++ ){
    bool res;
    vv.push_back( interPnt( ret[ i ] , ret[ ( i + 1 ) % ret.size() ] , res ) );
  }
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    ar += ( vv[ i ] ^ vv[ ( i + 1 ) % vv.size() ] );
  return fabs( ar ) * 0.5;
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
double cross(Pt o, Pt a, Pt b){
  return (a-o) ^ (b-o);
}
double convex_hull(vector<Pt> pt){
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
  double ret = 0;
  for( size_t i = 0 ; i < stk.size() ; i ++ )
    ret += ( stk[ i ] ^ stk[ ( i + 1 ) % stk.size() ] );
  return fabs( ret ) * 0.5;
}
void scan( Pt& tp ){
  cin >> tp.X >> tp.Y;
}
#define N 20
int n;
bool ok[ N ][ N ];
Pt s[ N ] , t[ N ] , v[ N ];
void init(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    scan( s[ i ] );
    scan( t[ i ] );
    double vv; cin >> vv;
    if( vv > 0 ){
      v[ i ] = perp( t[ i ] - s[ i ] );
      v[ i ] = ( v[ i ] / norm( v[ i ] ) ) * fabs( vv );
    }else{
      v[ i ] = perp( s[ i ] - t[ i ] );
      v[ i ] = ( v[ i ] / norm( v[ i ] ) ) * fabs( vv );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      if( not equal( ( t[ i ] - s[ i ] ) ^ ( t[ j ] - s[ j ] ) , 0.0 ) )
        ok[ i ][ j ] = true;
}
double cal( double nt ){
  vector<Pt> vv;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ ){
      if( not ok[ i ][ j ] ) continue;
      //if( equal( ( t[ i ] - s[ i ] ) ^ ( t[ j ] - s[ j ] ) , 0.0 ) )
        //continue;
      bool res;
      Pt tmp = interPnt( { s[ i ] + v[ i ] * nt , t[ i ] + v[ i ] * nt } ,
                         { s[ j ] + v[ j ] * nt , t[ j ] + v[ j ] * nt } , res );
      if( !res ) continue;
      vv.push_back( tmp );
    }
  return convex_hull(vv);
}
#define XX 100000
void solve(){
  double ans = 0. , pre = 0;
  double T; cin >> T;
  double per = T / XX;
  double pa = cal( 0 );
  for( int i = 0 ; i < XX ; i ++ ){
    double cur = pre + per;
    double na = cal( cur );

    ans += ( pa + na ) * per / 2;

    pa = na;
  
    pre = cur;
  }
  //cout << cal( 0 ) << endl;
  //cout << cal( T ) << endl;
  ans /= T;
  printf( "%.12f\n" , ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "convex.in" , "r" , stdin );
  freopen( "convex.out" , "w" , stdout );
#endif
  init();
  solve();
}
