#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 4040
char c[ N ][ N ];
int n , len[ N ] , ord[ N ];
inline bool okay( int i , int j ){
  int ptr = 0;
  for( int k = 0 ; k < len[ j ] ; k ++ ){
    while( ptr < len[ i ] and c[ i ][ ptr ] != c[ j ][ k ] )
      ptr ++;
    if( ptr == len[ i ] )
      return false;
    ptr ++;
  }
  return true;
}
void imp(){
  puts( "impossible" );
  exit(0);
}
int enc( int x , int y ){
  return x * N + y;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] );
    len[ i ] = strlen( c[ i ] );
    ord[ i ] = i;
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( len[ i ] >= len[ 0 ] )
      imp();
  sort( ord , ord + n + 1 ,
        [&](int id1 , int id2){ return len[id1] > len[id2]; } );
}
unordered_map< int , int > pre[ N ];
int bk[ N ];
bool vst[ N ];
void solve(){
  pre[ 0 ][ enc(0, 0) ] = enc(0, 0);
  for( int _ = 0 ; _ < n ; _ ++ ){
    if( pre[ _ ].empty() ) imp();
    if( pre[ _ ].size() == 1u ){
      for( auto st : pre[ _ ] ){
        int who = st.first;
        int nx = who / N;
        int ny = who % N;
        if( nx == ny ){
          if( okay( ord[ nx ] , ord[ _ + 1 ] ) )
            pre[ _ + 1 ][ enc( nx , _ + 1 ) ] = who;
        }else{
          if( okay( ord[ nx ] , ord[ _ + 1 ] ) )
            pre[ _ + 1 ][ enc( ny , _ + 1 ) ] = who;
          if( okay( ord[ ny ] , ord[ _ + 1 ] ) )
            pre[ _ + 1 ][ enc( nx , _ + 1 ) ] = who;
        }
      }
    }else{
      vector<int> cand;
      for( auto st : pre[ _ ] ){
        int who = st.first;
        int nx = who / N;
        int ny = who % N;
        cand.push_back( nx );
        cand.push_back( ny );
      }
      sort( cand.begin() , cand.end() );
      cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
      assert( cand.size() == 3u );
      if( okay( ord[ cand[ 2 ] ] , ord[ _ + 1 ] ) ){
        pre[ _ + 1 ][ enc( cand[ 0 ] , _ + 1 ) ] = enc( cand[ 0 ] , cand[ 2 ] );
        pre[ _ + 1 ][ enc( cand[ 1 ] , _ + 1 ) ] = enc( cand[ 1 ] , cand[ 2 ] );
      }else{
        if( okay( ord[ cand[ 0 ] ] , ord[ _ + 1 ] ) )
          pre[ _ + 1 ][ enc( cand[ 2 ] , _ + 1 ) ] = enc( cand[ 0 ] , cand[ 2 ] );
        if( okay( ord[ cand[ 1 ] ] , ord[ _ + 1 ] ) )
          pre[ _ + 1 ][ enc( cand[ 2 ] , _ + 1 ) ] = enc( cand[ 1 ] , cand[ 2 ] );
      }
    }
  }
  if( pre[ n ].empty() ) imp();
  int aenc = pre[ n ].begin()->first;
  int ax = aenc / N;
  int ay = aenc % N;
  for( int i = n ; i >= 1 ; i -- ){
    int p = pre[ i ][ enc( ax , ay ) ];
    int px = p / N;
    int py = p % N;
    bk[ i ] = px + py - ((ax + ay) - i);
    ax = px;
    ay = py;
  }
  vector<int> a[ 2 ];
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = n ; j >= 1 ; j -- ){
      if( vst[ j ] ) continue;
      while( j ){
        a[ i ].push_back( j );
        vst[ j ] = true;
        j = bk[ j ];
      }
      break;
    }
  printf( "%d %d\n" , (int)a[ 0 ].size() , (int)a[ 1 ].size() );
  for( int i = 0 ; i < 2 ; i ++ )
    for( int id : a[ i ] )
      puts( c[ ord[ id ] ] );
}
int main(){
  init();
  solve();
}
