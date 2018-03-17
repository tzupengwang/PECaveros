#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MXN 101
typedef bitset<101> Int;
Int linkto[ MXN ];
inline int popcount(const Int& val){
  return val.count();
}
inline int lowbit(const Int& val){
  return val._Find_first();
}
/* candi should be sorted from big deg. to small deg. */
int ans , stk[ MXN ] , cans[ MXN ];
void maxclique(int elem_num, Int candi){
  if(elem_num > ans){
    ans = elem_num;
    for( int i = 0 ; i < elem_num ; i ++ )
      cans[ i ] = stk[ i ];
  }
  int potential = elem_num + popcount(candi);
  if(potential <= ans) return;
  /*  Since Maximum Clique must contain >= 1 node not in Neighbor(pivot),
   *  Otherwise pivot can be added into the Clique.
   */
  int pivot = lowbit(candi);
  Int smaller_candi = candi & (~linkto[pivot]);

  //while(candi.count() && potential > ans){
    //int next = lowbit(candi);

    //candi[ next ] = 0;
    //potential --;

    //stk[ elem_num ] = next;

    //maxclique(elem_num + 1, candi & linkto[next]);
  //}
  while(smaller_candi.count() && potential > ans){
    int next = lowbit(smaller_candi);

    candi[next] = !candi[next];
    smaller_candi[ next ] = !smaller_candi[ next ];
    potential --;

    if(next == pivot || (smaller_candi & linkto[next]).count() ){
      stk[elem_num] = next;
      maxclique(elem_num + 1, candi & linkto[next]);
    }
  }
}
#define N 111
LL n , d , x[ N ] , y[ N ];
LL sqr( LL _ ){ return _ * _; }
inline LL dist( int id1 , int id2 ){
  return sqr( x[id1] - x[id2] ) +
    sqr( y[id1] - y[id2] );
}
int deg[ N ] , id[ N ] , di[ N ];
vector<int> v[ N ];
int main(){
  cin >> n >> d;
  for( int i = 0 ; i < n ; i ++ )
    cin >> x[ i ] >> y[ i ];
  d *= d;
  //solver.init( n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      if( dist( i , j ) <= d ){
        deg[ i ] ++;
        deg[ j ] ++;
        v[ i ].push_back( j );
        v[ j ].push_back( i );
      }
  for( int i = 0 ; i < n ; i ++ )
    id[ i ] = i;
  sort( id , id + n , [&](int id1, int id2){ return deg[id1] > deg[id2]; } );

  for( int i = 0 ; i < n ; i ++ )
    di[ id[ i ] ] = i;

  Int cand;
  cand.reset();
  for( int i = 0 ; i < n ; i ++ ){
    cand[ i ] = 1;
    for( int j : v[ i ] )
      linkto[ di[ i ] ][ di[ j ] ] = 1;
  }

  ans = 1;
  maxclique( 0 , cand );


  printf( "%d\n" , ans );
  for( int i = 0 ; i < ans ; i ++ )
    printf( "%d%c" , id[ cans[ i ] ] + 1 , " \n"[ i + 1 == ans ] );
}
