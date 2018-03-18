#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
#define N 101010
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
void scan( Pt& p ){
  scanf( "%lld%lld" , &p.X , &p.Y );
}
LL n , s;
Pt p[ N ];
void init(){
  scanf( "%lld%lld" , &n , &s );
  s *= 2;
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  sort( p , p + n );
}
LL ans = -1;
void upd( LL area ){
  if( ans == -1 ){
    ans = area;
    return;
  }
  if( abs( area - s ) < abs( ans - s ) or
      ( abs( area - s ) == abs( ans - s ) and
        area < ans ) )
    ans = area;
}
LL dp[ N ];
void solve(){
  {
    vector< Pt > lower,  upper;
    LL ls = 0 , us = 0 , bns = 0;
    for( int l = 0 , r = 0 ; l < n ; l = r ){
      while( r < n and p[ l ].X == p[ r ].X ) r ++;
      for( int i = l ; i < r ; i ++ ){
        Pt cur = p[ i ];
        while( lower.size() > 1u ){
          Pt p1 = lower[ lower.size() - 2u ];
          Pt p2 = lower[ lower.size() - 1u ];
          if( ((p2 - p1) ^ (cur - p1)) <= 0 ){
            ls -= p1 ^ p2;
            lower.pop_back();
          }else
            break;
        }
        if( lower.size() )
          ls += lower.back() ^ cur;
        lower.push_back( cur );
      }
      for( int i = r - 1 ; i >= l ; i -- ){
        Pt cur = p[ i ];
        while( upper.size() > 1u ){
          Pt p1 = upper[ upper.size() - 2u ];
          Pt p2 = upper[ upper.size() - 1u ];
          if( ((p2 - p1) ^ (cur - p1)) >= 0 ){
            us -= p2 ^ p1;
            upper.pop_back();
          }else
            break;
        }
        if( upper.size() )
          us += cur ^ upper.back();
        upper.push_back( cur );
      }
      if( l == 0 ) bns = (upper[ 0 ] ^ lower[ 0 ]);
      LL area = ls + us + (lower.back() ^ upper.back()) + bns;
      assert( area >= 0 );
      dp[ r ] = area;
    }
    upd( dp[ n ] );
  }
  for( int i = 0 ; i < n ; i ++ )
    p[ i ].X = -p[ i ].X;
  sort( p , p + n );
  {
    vector< Pt > lower,  upper;
    LL ls = 0 , us = 0 , bns = 0;
    for( int l = 0 , r = 0 ; l < n ; l = r ){
      while( r < n and p[ l ].X == p[ r ].X ) r ++;
      for( int i = l ; i < r ; i ++ ){
        Pt cur = p[ i ];
        while( lower.size() > 1u ){
          Pt p1 = lower[ lower.size() - 2u ];
          Pt p2 = lower[ lower.size() - 1u ];
          if( ((p2 - p1) ^ (cur - p1)) <= 0 ){
            ls -= p1 ^ p2;
            lower.pop_back();
          }else
            break;
        }
        if( lower.size() )
          ls += lower.back() ^ cur;
        lower.push_back( cur );
      }
      for( int i = r - 1 ; i >= l ; i -- ){
        Pt cur = p[ i ];
        while( upper.size() > 1u ){
          Pt p1 = upper[ upper.size() - 2u ];
          Pt p2 = upper[ upper.size() - 1u ];
          if( ((p2 - p1) ^ (cur - p1)) >= 0 ){
            us -= p2 ^ p1;
            upper.pop_back();
          }else
            break;
        }
        if( upper.size() )
          us += cur ^ upper.back();
        upper.push_back( cur );
      }
      if( l == 0 ) bns = (upper[ 0 ] ^ lower[ 0 ]);
      LL area = ls + us + (lower.back() ^ upper.back()) + bns;
      assert( area >= 0 );
      LL res = n - r;
      upd( abs( area - dp[ res ] ) );
    }
  }
  printf( "%lld.%lld\n" , ans / 2 , (ans % 2) * 5 );
}
int main(){
  init();
  solve();
}
