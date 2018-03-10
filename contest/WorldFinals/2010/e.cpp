#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 22
int r , c;
LL encode( int* a ){
  LL ret = 0;
  for( int i = 0 ; i < c ; i ++ )
    ret = (ret << 5) | a[ i ];
  return ret;
}
void decode( LL x , int* a ){
  for( int i = c - 1 ; i >= 0 ; i -- ){
    a[ i ] = x & ((1 << 5) - 1);
    x >>= 5;
  }
}
int score( int* a ){
  int ret = 0;
  for( int i = 0 ; i < c ; i ++ )
    if( a[ i ] )
      ret ++;
  return ret;
}
char a[ N ][ N ];
void init(){
  for( int i = 1 ; i <= r ; i ++ )
    scanf( "%s" , a[ i ] );
}
unordered_map< LL , int > st[ N ];
unordered_map< LL , LL > bk[ N ];
bool block[ N ];
int cur_row , to , ori[ 10 ] , now[ 10 ];
int cand[ 10 ] , ct , pscore;
LL from;
void upd(){
  LL ev = encode( now );
  int nscore = pscore;
  for( int i = 0 ; i < c ; i ++ )
    if( now[ i ] )
      nscore ++;
  auto it = st[ cur_row ].find( ev );
  if( it == st[ cur_row ].end() or
      nscore > it->second ){
    st[ cur_row ][ ev ] = nscore;
    bk[ cur_row ][ ev ] = from;
  }
}
int map_to[ 111 ];
void gogo( int no , int pre , int iid , int lst ){ // >= pre
  if( no == ct ){
    upd();
    return;
  }

  {
    gogo( no , pre + 1 , iid , lst );
    for( int i = pre ; i <= cand[ no ] - 2 ; i ++ ){
      if( block[ i ] or ori[ i ] ) break;
      now[ i ] = (iid + 1) << 1;
      
      now[ i ] = 0;
    }
  }

  int Ori = map_to[ ori[ cand[ no ] ] >> 1 ];
  if( !map_to[ ori[ cand[ no ] ] >> 1 ] )
    map_to[ ori[ cand[ no ] ] >> 1 ] = ++ iid;
  int val = map_to[ ori[ cand[ no ] ] >> 1 ]; 
  if( no + 1 < ct and (ori[ cand[ no     ] ] >> 1) !=
                       (ori[ cand[ no + 1 ] ] >> 1) ){
    bool ok = true;
    for( int k = cand[ no ] ; k <= cand[ no + 1 ] ; k ++ ){
      if( block[ k ] ){
        ok = false;
        break;
      }
      if( k > cand[ no ] and k < cand[ no + 1 ] and ori[ k ] ){
        ok = false;
        break;
      }
    }
    if( ok ){
      for( int k = cand[ no ] ; k <= cand[ no + 1 ] ; k ++ )
        now[ k ] = val << 1;
      gogo( no + 2 , cand[ no + 1 ] + 2 , iid , lst );
      for( int k = cand[ no ] ; k <= cand[ no + 1 ] ; k ++ )
        now[ k ] = 0;
    }
  }
  if( not block[ cand[ no ] ] ){
    if( cand[ no ] + 1 == c or !ori[ cand[ no ] + 1 ] ){
      for( int i = cand[ no ] ; i >= pre ; i -- ){
        if( block[ i ] ) break;
        if( i < cand[ no ] and ori[ i ] ) break;
        now[ i ] = (val << 1) | 1;
        gogo( no + 1 , cand[ no ] + 2 , iid , lst );
        now[ i ] = (val << 1);
      }
      for( int i = cand[ no ] ; i >= pre ; i -- ){
        if( block[ i ] ) break;
        now[ i ] = 0;
      }
    }
    if( cand[ no ] == 0 or !ori[ cand[ no ] - 1 ] ){
      int til = (no + 1 == ct ? c - 1 : cand[ no + 1 ] - 2);
      for( int i = cand[ no ] ; i <= til ; i ++ ){
        if( block[ i ] ) break;
        if( i > cand[ no ] and ori[ i ] ) break;
        now[ i ] = (val << 1) | 1;
        gogo( no + 1 , i + 2 , iid , lst );
        now[ i ] = (val << 1);
      }
      for( int i = cand[ no ] ; i <= til ; i ++ ){
        if( block[ i ] ) break;
        now[ i ] = 0;
      }
    }
  }
  map_to[ ori[ cand[ no ] ] >> 1 ] = Ori;
}
int ans[ N ][ N ] , _cs;
void solve(){
  for( int i = 0 ; i <= r ; i ++ ){
    st[ i ].clear();
    bk[ i ].clear();
  }
  {
    int start[ 10 ];
    for( int i = 0 ; i < c ; i ++ )
      start[ i ] = 0;
    start[ 0 ] = (1 << 1) | 1;
    st[ 0 ][ encode( start ) ] = 0;
  }
  for( int i = 0 ; i + 1 <= r ; i ++ ){
    cur_row = i + 1;
    for( int j = 0 ; j < c ; j ++ )
      if( a[ i + 1 ][ j ] == '#' )
        block[ j ] = true;
      else
        block[ j ] = false;
    to = i + 1;
    for( auto cur : st[ i ] ){
      from = cur.first;
      decode( cur.first , ori );
      pscore = cur.second;
      ct = 0;
      for( int j = 0 ; j < c ; j ++ )
        if( ori[ j ] & 1 )
          cand[ ct ++ ] = j;
      for( int j = 0 ; j < c ; j ++ )
        now[ j ] = 0;
      gogo( 0 , 0 , 0 , 100 );
    }
  }
  int bst = -1; LL who = 0;
  for( auto cur : st[ r ] ){
    int arr[ 10 ];
    decode( cur.first , arr );
    int msk = 0;
    for( int i = 0 ; i < c ; i ++ ){
      if( !arr[ i ] ) continue;
      msk |= (1 << (arr[ i ] >> 1));
    }
    if( __builtin_popcount( msk ) != 1 )
      continue;
    if( (arr[ c - 1 ] & 1) != 1 )
      continue;
    if( cur.second > bst ){
      bst = cur.second;
      who = cur.first;
    }
  }
  cerr << bst << endl;
  printf( "Case %d:\n" , ++ _cs );
  for( int i = r ; i >= 1 ; i -- ){
    decode( who , ans[ i ] );
    who = bk[ i ][ who ];
  }
  for( int i = 1 ; i <= r ; i ++ , puts( "" ) )
    for( int j = 0 ; j < c ; j ++ )
      if( a[ i ][ j ] == '#' )
        putchar( a[ i ][ j ] );
      else if( ans[ i ][ j ] )
        putchar( 'C' );
      else
        putchar( '.' );
}
int main(){
  while( scanf( "%d%d" , &r , &c ) == 2 and r ){
    init();
    solve();
  }
}
