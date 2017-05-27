#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
#define N 101010
int n , k;
vector< pair<int, pair<int,int> > > v;
int chg( int x ){
  if( x == 1 ) return 0;
  if( x == 3 ) return 1;
  if( x == 2 ) return 2;
  return -1;
}
bool cmp( pair< int , pair<int,int> > p1 ,
          pair< int , pair<int,int> > p2 ){
  if( p1.first != p2.first ) return p1.first > p2.first;
  return chg( p1.second.first ) <
         chg( p2.second.first );
}
void init(){
  n = getint();
  k = getint();
  for( int i = 0 ; i < n ; i ++ ){
    int ai = getint();
    int ei = getint();
    int si = getint();
    v.push_back( { ei , { ai , si } } );
  }
  sort( v.begin() , v.end() , cmp );
}
#define K 321
const int inf = K * 100000;
int dp[ 2 ][ K ][ K ];
void solve(){
  for( int i = 0 ; i <= k ; i ++ )
    for( int j = 0 ; j <= k ; j ++ )
      dp[ 0 ][ i ][ j ] = inf;
  dp[ 0 ][ 0 ][ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    int abi = v[ i - 1 ].second.first;
    int cst = v[ i - 1 ].second.second;
    int now = i & 1 , pre = 1 - now;
    for( int j = 0 ; j <= k ; j ++ )
      for( int jj = 0 ; jj <= k ; jj ++ )
        dp[ now ][ j ][ jj ] = inf;
    for( int j = 0 ; j <= k ; j ++ )
      for( int jj = 0 ; jj <= j ; jj ++ ){
        if( dp[ pre ][ j ][ jj ] == inf ) continue;
        dp[ now ][ j ][ jj ] = min( dp[ now ][ j ][ jj ] ,
                                    dp[ pre ][ j ][ jj ] );
        if( abi & 1 ){
          if( j + 1 <= k ){
            dp[ now ][ j + 1 ][ jj + 1 ] = min( dp[ now ][ j + 1 ][ jj + 1 ],
                                                dp[ pre ][ j ][ jj ] + cst );
          }
        }
        if( abi & 2 ){
          if( jj ){
            dp[ now ][ j ][ jj - 1 ] = min( dp[ now ][ j ][ jj - 1 ] ,
                                            dp[ pre ][ j ][ jj ] + cst );
          }
        }
      }
    //for( int j = 0 ; j <= k ; j ++ )
      //for( int jj = 0 ; jj <= j ; jj ++ )
        //if( dp[ now ][ j ][ jj ] < inf )
          //printf( "%d %d %d : %d\n" , i , j , jj , dp[ now ][ j ][ jj ] );
  }
  printf( "%d\n" , dp[ n & 1 ][ k ][ 0 ] );
}
int main(){
  init();
  solve();
}
