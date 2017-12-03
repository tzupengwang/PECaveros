#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define lgN 20
#define N 300030
#define Q 30030
#define K 1500
typedef long long LL;
inline int getint(){
  int _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
int n , m , a[ N ] , ql[ Q ] , qr[ Q ] , bt[ N ];
int ad[ lgN ][ N ];
LL ps[ N ] , mx[ lgN ][ N ] , mn[ lgN ][ N ];
vector<int> wt[ N / K + 2 ];
inline int And( int l , int r ){
  int cbt = bt[ r - l + 1 ];
  return ad[ cbt ][ l ] &
         ad[ cbt ][ r - (1 << cbt) + 1 ];
}
inline LL Max( int l , int r ){
  int cbt = bt[ r - l + 1 ];
  return max( mx[ cbt ][ l ] ,
              mx[ cbt ][ r - (1 << cbt) + 1 ] );
}
inline LL Min( int l , int r ){
  int cbt = bt[ r - l + 1 ];
  return min( mn[ cbt ][ l ] ,
              mn[ cbt ][ r - (1 << cbt) + 1 ] );
}
inline void build_table(){
  for( int i = 1 ; i < N ; i ++ )
    bt[ i ] = __lg( i );
  for( int i = 1 ; i <= n ; i ++ )
    ad[ 0 ][ i ] = abs( a[ i ] );
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      ad[ j ][ i ] = ad[ j - 1 ][ i ] &
                     ad[ j - 1 ][ i + (1 << (j - 1)) ];
  for( int i = 1 ; i <= n ; i ++ )
    ps[ i ] = ps[ i - 1 ] + a[ i ];
  for( int i = 1 ; i <= n ; i ++ )
    mn[ 0 ][ i ] = mx[ 0 ][ i ] = ps[ i ];
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      mx[ j ][ i ] = max( mx[ j - 1 ][ i ] ,
                          mx[ j - 1 ][ i + (1 << (j - 1)) ] );
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 0 ; i + (1 << j) - 1 <= n ; i ++ )
      mn[ j ][ i ] = min( mn[ j - 1 ][ i ] ,
                          mn[ j - 1 ][ i + (1 << (j - 1)) ] );
}
LL qans[ N ];
int nxt[ N ][ lgN ] , nct[ N ];
int pre[ N ][ lgN ] , pct[ N ];
LL ans[ Q ];
void build_qans(){
  for( int i = 1 ; i <= n ; i ++ ){
    {
      int ct = 0;
      nxt[ i ][ ct ++ ] = i;
      int lst = i , vl = abs( a[ i ] );
      while( lst <= n ){
        int bl = lst + 1 , br = n , ba = n + 1;
        while( bl <= br ){
          int bmid = (bl + br) >> 1;
          if( And( i , bmid ) != vl )
            ba = bmid , br = bmid - 1;
          else
            bl = bmid + 1;
        }
        nxt[ i ][ ct ++ ] = lst = ba;
        if( ba <= n ) vl = And( i , ba );
      }
      nct[ i ] = ct;
    }
    {
      int ct = 0;
      pre[ i ][ ct ++ ] = i;
      int lst = i , vl = abs( a[ i ] );
      while( lst >= 1 ){
        int bl = 1 , br = lst - 1 , ba = 0;
        while( bl <= br ){
          int bmid = (bl + br) >> 1;
          if( And( bmid , i ) != vl )
            ba = bmid , bl = bmid + 1;
          else
            br = bmid - 1;
        }
        pre[ i ][ ct ++ ] = lst = ba;
        if( ba >= 1 ) vl = And( ba , i );
      }
      pct[ i ] = ct;
    }
  }
  for( int i = 1 ; i <= n ; i += K ){
    int id = i / K;
    for( int j = 1 ; j <= n ; j ++ )
      qans[ j ] = 0;
    for( int j = i ; j <= n ; j ++ ){
      qans[ j ] = qans[ j - 1 ];
      for( int k = 0 ; k + 1 < pct[ j ] ; k ++ ){
        int rb = pre[ j ][ k ] , lb = pre[ j ][ k + 1 ] + 1;
        if( rb < i ) break;
        LL tans = And( rb , j ) + ps[ j ] - Min( max( i - 1 , lb - 1 ) , rb - 1 );
        if( tans > qans[ j ] )
          qans[ j ] = tans;
        //int lb = nxt[ i ][ k ] , rb = nxt[ i ][ k + 1 ] - 1;
        //if( lb > j ) break;
        //LL tans = And( i , lb ) + Max( lb , min( rb , j ) ) - ps[ i - 1 ];
        //if( tans > qans[ j ] )
          //qans[ j ] = tans;
      }
    }
    for( int qid : wt[ id ] )
      ans[ qid ] = qans[ qr[ qid ] ];
  }
}
void init(){
  n = getint();
  m = getint();
  //n = 300000;
  //m = 30000;
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = getint();
    //a[ i ] = rand() % 200001 - 100000;
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d" , &ql[ i ] , &qr[ i ] );
    //ql[ i ] = i + 1, qr[ i ] = n - i;
    int blk = (ql[ i ] - 1) / K;
    int st = blk * K + 1;
    if( st < ql[ i ] ){
      blk ++;
      st += K;
    }
    if( st <= qr[ i ] )
      wt[ blk ].push_back( i );
  }
  build_table();
  build_qans();
}
void solve(){
  for( int qid = 0 ; qid < m ; qid ++ ){
    int blk = (ql[ qid ] - 1) / K;
    int st = blk * K + 1;
    if( st < ql[ qid ] ){
      blk ++;
      st += K;
    }
    int til = qr[ qid ];
    for( int i = ql[ qid ] ; i < min( st , til + 1 ) ; i ++ ){
      for( int k = 0 ; k + 1 < nct[ i ] ; k ++ ){
        int lb = nxt[ i ][ k ] , rb = nxt[ i ][ k + 1 ] - 1;
        if( lb > til ) break;
        LL tans = And( i , lb ) + Max( lb , min( rb , til ) ) - ps[ i - 1 ];
        if( tans > ans[ qid ] )
          ans[ qid ] = tans;
      }
    }
  }
  for( int qid = 0 ; qid < m ; qid ++ )
    printf( "%lld\n" , ans[ qid ] );
}
int main(){
  init();
  solve();
}
