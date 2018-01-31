#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
typedef long long LL;
typedef long double type;
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
type norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { -tp.Y , tp.X };
}
type cross(Pt o, Pt a, Pt b){
  return (a-o) ^ (b-o);
}
vector<Pt> convex_hull(vector<Pt> pt){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Pt> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) < eps)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) < eps)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	type f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	type f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	type f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt( nan(""), nan("") );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
}
int n;
vector<Pt> v;
#define N 101010
void init(){
  cin >> n;
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scan( v[ i ] );
  v = convex_hull( v );
}
type ans;
vector<Pt> vans;
bool gt;
void upd( const vector<Line>& vv ){
  vector<Pt> tv;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    Pt ret = interPnt( vv[ i ].first , vv[ i ].second , 
                       vv[ (i + 1) % vv.size() ].first ,
                       vv[ (i + 1) % vv.size() ].second );
    tv.push_back( ret );
  }
  type suma = 0;
  for( size_t i = 0 ; i < tv.size() ; i ++ )
    suma += tv[ i ] ^ tv[ (i + 1) % tv.size() ];
  suma = fabs( suma );
  if( !gt or suma < ans ){
    gt = true;
    ans = suma;
    vans.swap( tv );
  }
}
void solve(){
  size_t i1 = 0 , i2 = 0 , i3 = 0;
  for( size_t i = 0 ; i < v.size() ; i ++ ){
    Pt p1 = v[ i ];
    Pt p2 = v[ (i + 1) % v.size() ];
    vector<Line> vv;
    vv.push_back( {p1, p2} );
    Pt dir = (p2 - p1);
    i1 = max(i1, i + 1);
    while( (dir * v[ (i1 + 1) % v.size() ]) >
           (dir * v[ i1 % v.size() ]) - eps )
      i1 ++;
    dir = perp( dir );
    vv.push_back( {v[i1 % v.size()], v[i1 % v.size()] + dir} );
    i2 = max(i1 , i2);
    while( (dir * v[ (i2 + 1) % v.size() ]) >
           (dir * v[ i2 % v.size() ]) - eps )
      i2 ++;
    dir = perp( dir );
    vv.push_back( {v[i2 % v.size()], v[i2 % v.size()] + dir} );
    i3 = max(i2, i3);
    while( (dir * v[ (i3 + 1) % v.size() ]) >
           (dir * v[ i3 % v.size() ]) - eps )
      i3 ++;
    dir = perp( dir );
    vv.push_back( {v[i3 % v.size()], v[i3 % v.size()] + dir} );
    upd( vv );
  }
  for( auto i : vans )
    printf( "%.8f %.8f\n" , (double)i.X , (double)i.Y );
}
int main(){
  init();
  solve();
}
