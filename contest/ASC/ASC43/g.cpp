#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
struct chip{
  LL maxx , maxy;
  deque< Pt > v;
  chip(){
    maxx = maxy = 0;
    v.clear();
  }
  chip operator+( const chip& c ){
    chip ac;
    for( size_t i = 0 ; i + 1 < v.size() ; i ++ )
      ac.v.push_back( v[ i ] );
    Pt bs = v.back() - c.v[ 1 ];
    for( size_t i = 1 ; i < c.v.size() ; i ++ )
      ac.v.push_back( bs + c.v[ i ] );
    for( auto i : ac.v ){
      ac.maxx = max( ac.maxx , i.X );
      ac.maxy = max( ac.maxy , i.Y );
    }
    return ac;
  }
  chip operator|( const chip& c ){
    chip ac;
    ac.v.push_back( { 0 , 0 } );
    ac.v.push_back( { 1 , 0 } );
    Pt lst;
    for( size_t i = 1 ; i + 1 < v.size() ; i ++ ){
      ac.v.push_back( v[ i ] + make_pair( 2 + c.maxy , 0 ) );
      lst.X = ac.v.back().X;
    }
    for( size_t i = 1 ; i + 1 < c.v.size() ; i ++ ){
      Pt tp = { c.v[ i ].Y , c.v[ i ].X };
      ac.v.push_back( tp + make_pair( 1 , maxy + 1 ) );
      lst.Y = ac.v.back().Y;
    }
    ac.v.push_back( lst );
    ac.v.push_back( lst + make_pair( 0 , 1 ) );
    for( auto i : ac.v ){
      ac.maxx = max( ac.maxx , i.X );
      ac.maxy = max( ac.maxy , i.Y );
    }
    return ac;
  }
  void print(){
    printf( "%d\n" , (int)v.size() );
    LL mnx = v[ 0 ].X , mny = v[ 0 ].Y;
    for( auto i : v ){
      mnx = min( mnx , i.X );
      mny = min( mny , i.Y );
    }
    for( auto i : v )
      printf( "%lld %lld\n" , i.X - mnx - 1000000000 ,
                              i.Y - mny - 1000000000 );
  }
};
#define N 111
int n;
chip c[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    char cmd[ 9 ]; int xi , yi;
    scanf( "%s%d%d" , cmd , &xi , &yi );
    if( cmd[ 0 ] == '+' ) c[ i ] = c[ xi ] + c[ yi ];
    if( cmd[ 0 ] == '|' ) c[ i ] = c[ xi ] | c[ yi ];
  }
  c[ n ].print();
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "grid.in" , "r" , stdin );
  freopen( "grid.out" , "w" , stdout );
#endif
  c[ 0 ].v = { { 0 , 0 } , { 1 , 0 } , { 1 , 1 } };
  c[ 0 ].maxx = c[ 0 ].maxy = 1;
  while( scanf( "%d" , &n ) == 1 && n != -1 )
    solve();
}
