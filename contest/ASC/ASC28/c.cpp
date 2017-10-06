#include <bits/stdc++.h>
using namespace std;
#define N 333
typedef int type;
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
  scanf( "%d%d" , &tp.X , &tp.Y );
}
int n;
Pt p[ N ];
set< vector<int> > S;
bool between( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  int tmp = ( p2 - p1 ) * ( p3 - p1 );
  if( tmp < 0 ) return false;
  return tmp <= norm2( p3 - p1 );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "cottages.in" , "r" , stdin );
  freopen( "cottages.out" , "w" , stdout );
#endif
  scanf( "%d" , &n );
  //n = 300;
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    //p[ i ].X = rand() % 10000;
    //p[ i ].Y = rand() % 10000;
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ ){
      bool ok = true;
      Pt dlt = p[ j ] - p[ i ];
      for( int k = 0 ; k < n ; k ++ ){
        if( i == k or j == k ) continue;
        if( ( dlt ^ ( p[ k ] - p[ i ] ) ) == 0 and
            between( p[ i ] , p[ k ] , p[ j ] ) ){
          ok = false;
          break;
        }
      }
      if( not ok ) continue;
      vector<int> lft , rgt;
      for( int k = 0 ; k < n ; k ++ ){
        if( k == i ){
          lft.push_back( i );
          continue;
        }
        if( k == j ){
          rgt.push_back( j );
          continue;
        }
        int vl = dlt ^ ( p[ k ] - p[ i ] );
        if( vl == 0 ){
          if( ( dlt * ( p[ k ] - p[ i ] ) ) > 0 )
            rgt.push_back( k );
          else
            lft.push_back( k );
        }else{
          if( vl > 0 )
            lft.push_back( k );
          else
            rgt.push_back( k );
        }
      }
      S.insert( lft );
      S.insert( rgt );
    }
  cout << S.size() << endl;
}
