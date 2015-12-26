#include <bits/stdc++.h>
using namespace std;
#define N 26
int n , m , save;
char c[ N ][ N ];
bool flag , vst[ N ][ N ];
inline bool in( int nx , int ny ){
  return 0 <= nx && nx < n &&
         0 <= ny && ny < m;
}
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
void pDFS( int nn , int nm ){
  vst[ nn ][ nm ] = true;
  save ++;
  for( int i = 0 ; i < 4 ; i ++ ){
    int nxtn = nn + dn[ i ];
    int nxtm = nm + dm[ i ];
    if( in( nxtn , nxtm ) && !vst[ nxtn ][ nxtm ] &&
        c[ nxtn ][ nxtm ] != '#' )
      pDFS( nxtn , nxtm );
  }
}
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
  flag = false;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      vst[ i ][ j ] = false;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( !vst[ i ][ j ] && c[ i ][ j ] != '#' ){
        save = 0;
        pDFS( i , j );
        if( save % 2 ) flag = true;
      }
}
int ans;
inline int bit( int a , int k ){
  return ( a >> k ) & 1;
}
typedef long long ll;
set<ll> S;
#define K 100000
int dcnt;
void DFS( int nn , int nm , int msk , int pre , int cst ){
  if( dcnt >= K ) return;
  dcnt ++;
  ll ss = ( ( (ll)nn * m + nm ) << 32 ) + ( (ll)pre << 31 ) + msk;
  if( S.count( ss ) ) return;
  S.insert( ss );
  if( ans != -1 && cst >= ans ) return;
  if( nm >= m ){
    if( pre ) return;
    nn ++; nm = 0;
  }
  if( nn >= n ){
    if( msk || pre ) return;
    if( ans == -1 || cst < ans )
      ans = cst;
    return;
  }
  if( c[ nn ][ nm ] == '#' ){
    if( pre ) return;
    if( bit( msk , nm ) ) return;
    DFS( nn , nm + 1 , msk , pre , cst );
  }else if( c[ nn ][ nm ] == '.' ){
    if( bit( msk , nm ) && pre ){
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 0 , cst );
    }else if( bit( msk , nm ) ){
      DFS( nn , nm + 1 , msk , pre , cst );
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 1 , cst );
    }else if( pre ){
      DFS( nn , nm + 1 , msk , pre , cst );
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 0 , cst );
    }else{
      DFS( nn , nm + 1 , msk ^ ( 1 << nm ) , 1 , cst );
    }
  }else{
    if( bit( msk , nm ) && pre ){
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 0 , cst );
    }else if( bit( msk , nm ) ){
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 1 , cst );
      DFS( nn , nm + 1 , msk , pre , cst + 1 );
    }else if( pre ){
      int nmsk = msk ^ ( 1 << nm );
      DFS( nn , nm + 1 , nmsk , 0 , cst );
      DFS( nn , nm + 1 , msk , pre , cst + 1 );
    }else{
      DFS( nn , nm + 1 , msk ^ ( 1 << nm ) , 1 , cst );
    }
  }
}
void solve(){
  ans = -1;
  S.clear();
  dcnt = 0;
  if( !flag ) DFS( 0 , 0 , 0 , 0 , 0 );
  printf( "%d\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ );
  while( _ -- ){
    init();
    solve();
  }
}
