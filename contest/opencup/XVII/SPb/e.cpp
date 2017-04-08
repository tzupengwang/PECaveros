#include <bits/stdc++.h>
using namespace std;
#define N 514
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
LL c[ N ];
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
void build(){
  c[ 0 ] = 1;
  for( int i = 2 ; i < N ; i += 2 ){
    for( int j = 0 ; j < i ; j ++ )
      for( int k = j + 1 ; k < i ; k += 2 ){
        int lft = k - j - 1;
        int rgt = i - 2 - lft;
        c[ i ] += c[ lft ] * c[ rgt ];
      }
  }
}
int region( const Pt& a , const Pt& b , const Pt& p ){
  return ( ( b - a ) ^ ( p - a ) ) > 0; // left
}
int n;
vector<Pt> p;
LL k;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    Pt pi;
    scanf( "%lld%lld" , &pi.X , &pi.Y );
    p.push_back( pi );
  }
  scanf( "%lld" , &k );
}
void go( const vector<Pt>& pp , LL kk ){
  if( pp.empty() ) return;
  for( size_t i = 0 ; i < pp.size() ; i ++ ) // A
    for( size_t j = i + 1 ; j < pp.size() ; j ++ ){ // B
      vector<Pt> r[ 2 ];
      // A B 1 0
      for( size_t u = 0 ; u < pp.size() ; u ++ ){
        if( i == u or j == u ) continue;
        r[ region( pp[ i ] , pp[ j ] , pp[ u ] ) ].push_back( pp[ u ] );
      }
      if( (int)r[ 0 ].size() % 2 ) continue;
      if( (int)r[ 1 ].size() % 2 ) continue;
      LL ccc = c[ r[ 0 ].size() ] * c[ r[ 1 ].size() ];
      if( kk >= ccc ){
        kk -= ccc;
        continue;
      }
      printf( "%lld %lld\n" , pp[ i ].X , pp[ i ].Y );
      printf( "%lld %lld\n" , pp[ j ].X , pp[ j ].Y );
      go( r[ 1 ] , kk / (LL)c[ r[ 0 ].size() ] );
      go( r[ 0 ] , kk % (LL)c[ r[ 0 ].size() ] );
      return;
    }
}
void solve(){
  sort( p.begin() , p.end() );
  go( p , k );
}
int main(){
  build();
  init();
  solve();
}
