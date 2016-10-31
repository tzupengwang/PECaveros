#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
typedef pair< LL , LL > Pt;
typedef pair< Pt , LL > Cir;
#define X first.first
#define Y first.second
#define R second
void scan( Cir& tc ){
  scanf( "%lld%lld%lld" , &tc.X , &tc.Y , &tc.R );
}
int n;
Cir c[ N ];
bool cmp( Cir c1 , Cir c2 ){
  LL lx1 = c1.X - c1.R;
  LL lx2 = c2.X - c2.R;
  if( lx1 != lx2 ) return lx1 < lx2;
  if( c1.Y != c2.Y ) return c1.Y < c2.Y;
  return c1.R > c2.R;
}
const double pi = acos( -1.0 );
inline double area( const Cir& tc ){
  return pi * tc.R * tc.R;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( c[ i ] );
  sort( c , c + n , cmp );
}
double ans;
inline LL sqr( LL x ){
  return x * x;
}
bool gg( int id1 , int id2 ){
  if( c[ id1 ].R > c[ id2 ].R ) return false;
  LL dst = sqr( c[ id1 ].X - c[ id2 ].X ) +
           sqr( c[ id1 ].Y - c[ id2 ].Y );
  return dst <= sqr( c[ id2 ].R - c[ id1 ].R );
}
void solve(){
  set< pair< LL , int > > cand;
  for( int i = 0 ; i < n ; i ++ ){
    bool bye = false;
    // up
    if( cand.size() ){
      auto it = cand.lower_bound( { c[ i ].Y , i } );
      while( it != cand.end() ){
        int who = it->second;
        if( c[ who ].X + c[ who ].R <= c[ i ].X - c[ i ].R ){
          cand.erase( it );
          it = cand.lower_bound( { c[ i ].Y , i } );
          continue;
        }
        if( gg( i , who ) ) bye = true;
        break;
      }
    }
    // down
    if( cand.size() ){
      auto it = cand.lower_bound( { c[ i ].Y , i } );
      while( it != cand.begin() ){
        it --;
        int who = it->second;
        if( c[ who ].X + c[ who ].R <= c[ i ].X - c[ i ].R ){
          cand.erase( it );
          it = cand.lower_bound( { c[ i ].Y , i } );
          continue;
        }
        if( gg( i , who ) ) bye = true;
        break;
      }
    }
    if( !bye ){
      ans += area( c[ i ] );
      cand.insert( { c[ i ].Y , i } );
    }
  }
  printf( "%.12f\n" , ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "circles.in" , "r" , stdin );
  freopen( "circles.out" , "w" , stdout );
#endif
  init();
  solve();
}
