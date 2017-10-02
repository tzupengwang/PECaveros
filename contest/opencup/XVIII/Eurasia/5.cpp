#include <bits/stdc++.h>
using namespace std;
#define N 202020
int BIT[ N ] , who[ N ];
inline int lb( int x ){ return x & (-x); }
void modify( int pos , int now , int vl ){
  pos ++;
  for( int i = pos ; i < N ; i += lb( i ) )
    if( vl > BIT[ i ] ){
      BIT[ i ] = vl;
      who[ i ] = now;
    }
}
pair<int,int> query( int pos ){
  pos ++;
  int bst = 0 , bwho = 0;
  for( int i = pos ; i ; i -= lb( i ) )
    if( BIT[ i ] > bst ){
      bst = BIT[ i ];
      bwho = who[ i ];
    }
  return { bst , bwho };
}
int m , n , st[ N ] , len[ N ] , a[ N ] , b[ N ];
int dp[ N ] , bst , bk[ N ];
bool blk[ N ] , sst[ N ];
int con[ N ] , fa[ N ] , fb[ N ];
map< pair<int,int> , int > at;
vector< vector<int> > va;
int ans;
void build_ans(){
  for( int i = 1 ; i <= m ; i ++ ){
    if( a[ i ] == -1 and fa[ i ] == -1 )
      blk[ i ] = true;
    if( fa[ i ] == -1 ) continue;
    if( a[ i ] != fa[ i ] or b[ i ] != fb[ i ] )
      at[ { fa[ i ] , fb[ i ] } ] = i;
  }
  for( int rep = 0 ; rep < 2 ; rep ++ ){
    for( int i = 1 ; i <= m ; i ++ ){
      if( blk[ i ] ) continue;
      if( a[ i ] == -1 ) continue;
      if( rep == 0 and fa[ i ] != -1 ) continue;
      int now = i;
      vector<int> tmp;
      tmp.push_back( now );
      while( true ){
        int to = at[ { a[ now ] , b[ now ] } ];
        //printf( "%d -> %d\n" , now , to );
        assert( to > 0 );
        tmp.push_back( to );
        if( to == i ) break;
        if( a[ to ] == -1 ) break;
        now = to;
      }
      for( auto j : tmp )
        blk[ j ] = true;
      va.push_back( tmp );
      ans += (int)tmp.size() - 1;
    }
  }
  printf( "%d %d\n" , ans , (int)va.size() );
  for( auto i : va ){
    printf( "%d " , (int)i.size() );
    for( size_t j = 0 ; j < i.size() ; j ++ )
      printf( "%d%c" , i[ j ] , " \n"[ j + 1 == i.size() ] );
  }
}
int mn[ N ];
int main(){
  scanf( "%d%d" , &m , &n );
  for( int i = 1 ; i <= m ; i ++ ){
    scanf( "%d%d" , &a[ i ] , &b[ i ] );
    if( a[ i ] > 0 and b[ i ] == 1 )
      st[ a[ i ] ] = i;
    if( a[ i ] > 0 )
      len[ a[ i ] ] ++;
    fa[ i ] = fb[ i ] = -1;
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < len[ i ] ; j ++ ){
      assert( a[ st[ i ] + j ] == i );
      assert( b[ st[ i ] + j ] == j + 1 );
    }
  for( int i = 1 ; i <= n ; i ++ )
    len[ i ] += len[ i - 1 ];
  for( int i = 1 ; i <= n ; i ++ ){
    int vl = st[ i ] - len[ i - 1 ] - 1;
    if( vl < 0 or vl > m - len[ n ] ) continue;
    pair<int,int> tp = query( vl );
    bk[ i ] = tp.second;
    dp[ i ] = tp.first + len[ i ] - len[ i - 1 ];
    modify( vl , i , dp[ i ] );
    if( dp[ i ] > dp[ bst ] ) bst = i;
  }
  for( int i = n ; i >= 1 ; i -- )
    len[ i ] -= len[ i - 1 ];
  while( bst ){
    for( int i = st[ bst ] ; i < st[ bst ] + len[ bst ] ; i ++ ){
      blk[ i ] = true;
      fa[ i ] = a[ i ];
      fb[ i ] = b[ i ];
    }
    sst[ bst ] = true;
    bst = bk[ bst ];
  }
  for( int i = m ; i >= 1 ; i -- )
    if( not blk[ i ] )
      con[ i ] = con[ i + 1 ] + 1;
  mn[ m + 1 ] = n + 1;
  for( int i = m ; i >= 1 ; i -- )
    if( fa[ i ] == -1 )
      mn[ i ] = mn[ i + 1 ];
    else
      mn[ i ] = min( mn[ i + 1 ] , fa[ i ] );
  int ptr = 1;
  for( int i = 1 ; i <= n ; i ++ )
    if( not sst[ i ] ){
      while( con[ ptr ] < len[ i ] or
             mn[ ptr ] <= i ) ptr ++;
      assert( ptr <= m );
      for( int j = ptr ; j < ptr + len[ i ] ; j ++ ){
        fa[ j ] = a[ st[ i ] + j - ptr ];
        fb[ j ] = b[ st[ i ] + j - ptr ];
      }
      ptr += len[ i ];
    }
  build_ans();
}
