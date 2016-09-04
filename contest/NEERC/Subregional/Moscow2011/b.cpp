#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , k , x[ N ] , len[ N ];
int ccc[ N * 10 ];
int pos , st[ N ];
void add( int now ){
  st[ now ] = pos;
  vector< int > vv;
  int vl = x[ now ];
  while( vl ){
    vv.push_back( vl % 10 );
    vl /= 10;
  }
  reverse( vv.begin() , vv.end() );
  for( int u : vv )
    ccc[ pos ++ ] = u;
}
int count( int vl ){
  int tlen = 0;
  while( vl ){
    tlen ++;
    vl /= 10;
  }
  return tlen;
}
int cnt[ N ] , til;
bool rm[ N ];
void rebuild(){
  pos = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( !rm[ i ] )
      add( i );
}
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &x[ i ] );
    len[ i ] = count( x[ i ] );
    cnt[ len[ i ] ] ++;
  }
  til = 1;
  for( int i = 1 ;  ; i ++ ){
    if( k >= cnt[ i ] ){
      k -= cnt[ i ];
    }else{
      til = i;
      break;
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( len[ i ] < til )
      rm[ i ] = true;
}
vector< int > cand , tcand;
int pre;
bool better( int ni , int nj ){
  int nlen = len[ ni ];
  for( int xi = max( pre , st[ ni ] ) ; xi < st[ nj ] ; xi ++ )
    if( ccc[ xi ] != ccc[ xi + nlen ] ){
      pre = max( pre , xi );
      return ccc[ xi + nlen ] > ccc[ xi ];
    }
  pre = max( pre , st[ nj ] );
  return false;
}
void remove(){
  rebuild();
  pre = 0;
  assert( !cand.empty() );
  size_t bst = 0;
  for( size_t i = 1 ; i < cand.size() ; i ++ )
    if( better( cand[ bst ] , cand[ i ] ) )
      break;
    else{
      bst = i;
      pre = st[ cand[ i ] ];
    }
  rm[ cand[ bst ] ] = true;
  tcand.clear();
  for( size_t i = 0 ; i < cand.size() ; i ++ )
    if( i != bst )
      tcand.push_back( cand[ i ] );
  cand = tcand;
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( len[ i ] == til )
      cand.push_back( i );
  while( k -- ) remove();
  for( int i = 1 ; i <= n ; i ++ )
    if( !rm[ i ] )
      printf( "%d" , x[ i ] );
  puts( "" );
}
int main(){
  init();
  solve();
}
