#include <bits/stdc++.h>
using namespace std;
#define N 202020
typedef long long LL;
typedef long long type;
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
int n;
LL randi(){
  return (LL)rand() * rand() % ( n + n + 1 ) - n;
}
void scan( Pt& tp ){
  //tp.X = randi();
  //tp.Y = randi();
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
vector<Pt> v;
Pt a[ 3 ];
int main(){
  //srand( time(0) );
  scanf( "%d" , &n );
  //n = 200000 
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scan( v[ i ] );
  vector<Pt> ch = convex_hull( v );
  LL bst = -1;
  int nn = (int)ch.size();
  //cout << nn << endl;
  for( int i = 0 ; i < nn ; i ++ )
    for( int j = i + 1 ; j < nn ; j ++ )
      for( int k = j + 1 ; k < nn ; k ++ ){
        LL area = abs( ( ch[ j ] - ch[ i ] ) ^ ( ch[ k ] - ch[ i ] ) );
        if( area > bst ){
          bst = area;
          a[ 0 ] = ch[ i ];
          a[ 1 ] = ch[ j ];
          a[ 2 ] = ch[ k ];
        }
      }
  for( int i = 0 ; i < 3 ; i ++ )
    printf( "%lld %lld\n" , a[ i ].X , a[ i ].Y );
}
