#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL getint(){
  LL x = 0; char tc = getchar();
  while( tc < '0' || tc > '9' ) tc = getchar();
  while( tc >= '0' && tc <= '9' ){
    x = x * 10 + tc - '0';
    tc = getchar();
  }
  return x;
}
#define N 101010
#define K 11
int n , k;
LL p[ N ] , q[ N ] , pp[ K ] , qq[ K ];
double v[ N ] , vv[ N ];
vector< pair<double,int> > sv;
void init(){
  n = getint();
  k = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = getint();
    q[ i ] = getint();
    v[ i ] = log( (double)p[ i ] / q[ i ] );
  }
  sv.clear();
  for( int i = 1 ; i <= k ; i ++ ){
    pp[ i ] = getint();
    qq[ i ] = getint();
    vv[ i ] = log( (double)pp[ i ] / qq[ i ] );
    sv.push_back( { vv[ i ] , i } );
  }
  sort( sv.begin() , sv.end() );
  reverse( sv.begin() , sv.end() );
  for( size_t i = 1 ; i < sv.size() ; i ++ )
    sv[ i ].first += sv[ i - 1 ].first;
}
const double inf = 1e100;
double dp[ N ][ K ] , bst;
int fr[ N ][ K ];
int bi , bj , _cs , pos[ K ];
vector< int > ppp;
void find_ans(){
  printf( "Case #%d:\n" , ++ _cs );
  for( int i = 1 ; i <= k ; i ++ )
    pos[ i ] = 0;
  ppp.clear();
  int lft = bi , rgt = bi , tk = bj;
  while( true ){
    lft = min( lft , bi );
    if( fr[ bi ][ bj ] == 0 ) break;
    if( fr[ bi ][ bj ] == 1 ){
      bi --;
    }else if( fr[ bi ][ bj ] == 2 ){
      break;
    }else if( fr[ bi ][ bj ] == 3 ){
      ppp.push_back( bi );
      break;
    }else if( fr[ bi ][ bj ] == 4 ){
      ppp.push_back( bi );
      bi --; bj --;
    }
  }
  lft = max( lft , 1 );
  for( int i = 0 ; i < tk ; i ++ )
    pos[ sv[ i ].second ] = ppp[ i ];
  printf( "%d %d\n" , lft , rgt );
  for( int i = 1 ; i <= k ; i ++ )
    printf( "%d%c" , pos[ i ] , " \n"[ i == k ] );
}
void solve(){
  bst = -inf;
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= k ; j ++ ){
      dp[ i ][ j ] = -inf;
      fr[ i ][ j ] = 0;
    }
  dp[ 0 ][ 0 ] = 0;
  fr[ 0 ][ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j <= min( k , i ) ; j ++ ){
      if( dp[ i - 1 ][ j ] + v[ i ] > dp[ i ][ j ] ){
        dp[ i ][ j ] = dp[ i - 1 ][ j ] + v[ i ];
        fr[ i ][ j ] = 1;
      }
      if( j == 0 ){
        if( v[ i ] > dp[ i ][ j ] ){
          dp[ i ][ j ] = max( dp[ i ][ j ] , v[ i ] );
          fr[ i ][ j ] = 2;
        }
      }
      if( j == 1 ){
        if( 0. > dp[ i ][ j ] ){
          dp[ i ][ j ] = max( dp[ i ][ j ] , 0. );
          fr[ i ][ j ] = 3;
        }
      }
      if( j ){
        if( dp[ i - 1 ][ j - 1 ] > dp[ i ][ j ] ){
          dp[ i ][ j ] = max( dp[ i ][ j ] , dp[ i - 1 ][ j - 1 ] );
          fr[ i ][ j ] = 4;
        }
      }
      double tdp = dp[ i ][ j ];
      if( j ) tdp += sv[ j - 1 ].first;
      if( tdp > bst ){
        bst = tdp;
        bi = i;
        bj = j;
      }
    }
  }
  find_ans();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
