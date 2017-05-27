#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 30303
#define K 8
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
LL n , a[ N ][ K ];
const LL infll = 1000000000000000000LL;
inline LL f( int id , LL nn ){
  LL ret = 0 , bs = 1;
  bool out = false;
  for( int i = 0 ; i < K ; i ++ ){
    if( i ){
      if( bs > infll / nn )
        out = true;
      bs = bs * nn;
    }
    if( !a[ id ][ i ] ) continue;
    if( out ) return infll;
    if( a[ id ][ i ] > infll / bs )
      return infll;
    ret += a[ id ][ i ] * bs;
    if( ret >= infll ) return infll;
  }
  return ret;
}
int nxt[ N ];
int main(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 7 ; j >= 0 ; j -- )
      a[ i ][ j ] = getint();
  int k;
  k = getint();
  priority_queue<
    pair<LL,int>,
    vector< pair<LL,int> >,
    greater< pair<LL,int> > > heap;
  for( int i = 0 ; i < n ; i ++ ){
    heap.push( { f( i , 1 ) , i } );
    nxt[ i ] = 2;
  }
  while( -- k ){
    auto i = heap.top(); heap.pop();
    int who = i.second;
    heap.push( { f( who , nxt[ who ] ) , who } );
    nxt[ who ] ++;
  }
  printf( "%lld\n" , heap.top().first );
}
