#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
const type eps = 1e-9;
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
#define N 101010
int n , m;
Pt p[ N ];
vector< int > tar[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    tar[ i ].clear();
  p[ n ] = p[ 0 ];
  scanf( "%d" , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int id , dst;
    scanf( "%d%d" , &id , &dst );
    tar[ id ].push_back( dst );
  }
  for( int i = 0 ; i < n ; i ++ ){
    sort( tar[ i ].begin() , tar[ i ].end() );
    reverse( tar[ i ].begin() , tar[ i ].end() );
  }
}
vector< pair< Pt , int > > vv;
void solve(){
  vv.clear();
  vv.push_back( { p[ 0 ] , 0 } );
  for( int i = n - 1 ; i >= 1 ; i -- ){
    for( auto x : tar[ i ] ){
      Pt ret = p[ i ] +
        ( p[ i + 1 ] - p[ i ] ) * ( x / norm( p[ i + 1 ] - p[ i ] ) );
      vv.push_back( { ret , 1 } );
    }
    vv.push_back( { p[ i ] , 0 } );
  }
  type ans = 0.0;
  for( auto x : tar[ 0 ] )
    ans += x;
  vector< pair< Pt , type > > uu;
  uu.push_back( { vv[ 0 ].first , 0 } );
  for( size_t i = 1 ; i < vv.size() ; i ++ ){
    //if( (int)uu.size() < 2 ){
      //type dd = norm( uu.back().first - vv[ i ].first );
      //if( vv[ i ].second ) ans += dd;
      //uu.push_back( { vv[ i ].first , dd } );
      //continue;
    //}
    int _sz = (int)uu.size();
    while( _sz > 1 && ( ( uu[ _sz - 1 ].first - uu[ _sz - 2 ].first ) ^
                        ( vv[ i ].first - uu[ _sz - 1 ].first ) ) < eps )
      uu.pop_back() , _sz --;
    type dd = norm( uu.back().first - vv[ i ].first );
    uu.push_back( { vv[ i ].first , uu.back().second + dd } );
    if( vv[ i ].second )
      ans += uu.back().second;
  } 
  printf( "%.1f\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
