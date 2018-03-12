#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 22
struct DJS{
  vector<int> v;
  vector< vector<int> > history;
  void init( int n ){
    v.resize( n );
    for( int i = 0 ; i < n ; i ++ )
      v[ i ] = i;
    history.clear();
  }
  int f( int x ){
    return x == v[ x ] ? x : f( v[ x ] );
  }
  void uni( int x , int y ){
    v[ f( x ) ] = f( y );
  }
  void save(){
    history.push_back( v );
  }
  void undo(){
    v = history.back();
    history.pop_back();
  }
} djs;
int r , c;
LL encode( int* arr ){
  LL ret = 0;
  for( int i = 0 ; i < c ; i ++ )
    ret = (ret << 5) | arr[ i ];
  return ret;
}
void decode( LL enc , int* arr ){
  for( int i = c - 1 ; i >= 0 ; i -- ){
    arr[ i ] = enc & ((1LL << 5) - 1);
    enc >>= 5;
  }
}
int score( int* arr ){
  int ret = 0;
  for( int i = 0 ; i < c ; i ++ )
    if( arr[ i ] )
      ret ++;
  return ret;
}
unordered_map<LL,LL> bk[ N ];
unordered_map<LL,int> dp[ N ];
char a[ N ][ N ];
bool block[ N ];
int ori[ N ] , now[ N ] , to , pscore;
LL from;
void upd(){
  int rnow[ N ] = {} , iid = 0;
  int map_to[ N ] = {};
  for( int i = 0 ; i < c ; i ++ ){
    if( !now[ i ] ) continue;
    int rp = djs.f( now[ i ] >> 1 );
    if( !map_to[ rp ] )
      map_to[ rp ] = ++ iid;
    rnow[ i ] = (map_to[ rp ] << 1) | (now[ i ] & 1);
  }
  LL nstate = encode( rnow );
  int nscore = pscore + score( rnow );
  auto it = dp[ to ].find( nstate );
  if( it == dp[ to ].end() or
      nscore > it->second ){
    dp[ to ][ nstate ] = nscore;
    bk[ to ][ nstate ] = from;
  }
}
void go( int cur_c , int pre , int nid ){
  if( cur_c >= c ){
    upd();
    return;
  }
  if( ori[ cur_c ] & 1 ){
    if( pre > cur_c ) return;
    if( block[ cur_c ] ) return;
    int val = (ori[ cur_c ] >> 1);
    int nxt = cur_c + 1;
    while( nxt < c and !(ori[ nxt ] & 1) ) nxt ++;
    { // union with next
      if( nxt < c and (ori[ cur_c ] >> 1) != (ori[ nxt ] >> 1) ){
        bool ok = true;
        for( int j = cur_c ; j <= nxt and ok ; j ++ )
          if( block[ j ] )
            ok = false;
        for( int j = cur_c + 1 ; j < nxt and ok ; j ++ )
          if( ori[ j ] )
            ok = false;
        if( ok ){
          for( int j = cur_c ; j <= nxt ; j ++ )
            now[ j ] = (val << 1);
          djs.save();
          djs.uni( ori[ cur_c ] >> 1 , ori[ nxt ] >> 1 );

          go( nxt + 2 , nxt + 2 , nid );

          djs.undo();
          for( int j = cur_c ; j <= nxt ; j ++ )
            now[ j ] = 0;
        }
      }
    }
    { // directly down
      now[ cur_c ] = (val << 1) | 1;
      go( cur_c + 2 , cur_c + 2 , nid );
      now[ cur_c ] = 0;
    }
    now[ cur_c ] = (val << 1);
    { // extend to pre
      for( int i = cur_c - 1 ; i >= pre ; i -- ){
        if( block[ i ] or ori[ i ] ) break;
        now[ i ] = (val << 1) | 1;
        if( i == 0 or !ori[ i - 1 ] )
          go( cur_c + 2 , cur_c + 2 , nid );
        now[ i ] = (val << 1);
      }
      for( int i = cur_c - 1 ; i >= pre ; i -- ){
        if( block[ i ] or ori[ i ] ) break;
        now[ i ] = 0;
      }
    }
    { // extend to nxt
      int til = (nxt == c ? c - 1 : nxt - 2);
      for( int i = cur_c + 1 ; i <= til ; i ++ ){
        if( block[ i ] or ori[ i ] ) break;
        now[ i ] = (val << 1) | 1;
        if( i == c - 1 or !ori[ i + 1 ] )
          go( i + 2 , i + 2 , nid );
        now[ i ] = (val << 1);
      }
      for( int i = cur_c + 1 ; i <= til ; i ++ ){
        if( block[ i ] or ori[ i ] ) break;
        now[ i ] = 0;
      }
    }
    now[ cur_c ] = 0;
  }else{
    go( cur_c + 1 , pre , nid );
    if( cur_c and ori[ cur_c - 1 ] ) return;
    if( cur_c < pre ) return;
    int nxt = cur_c + 1;
    while( nxt < c and !(ori[ nxt ] & 1) ) nxt ++;
    int til = (nxt == c ? c - 1 : nxt - 2);
    // new nid
    for( int i = cur_c ; i <= til ; i ++ ){
      if( block[ i ] or ori[ i ] ) break;
      now[ i     ] = (nid << 1) | 1;
      now[ cur_c ] = (nid << 1) | 1;
      if( i - cur_c + 1 > 2 and (i == c - 1 or !ori[ i + 1 ]) )
        go( i + 2 , i + 2 , nid + 1 );
      now[ i     ] = (nid << 1);
    }
    for( int i = cur_c ; i <= til ; i ++ ){
      if( block[ i ] or ori[ i ] ) break;
      now[ i ] = 0;
    }
  }
}
int ans[ N ][ N ] , _cs;
void solve(){
  for( int i = 0 ; i < N ; i ++ ){
    bk[ i ].clear();
    dp[ i ].clear();
  }
  {
    int ini[ N ] = {};
    ini[ 0 ] = (1LL << 1) | 1;
    dp[ 0 ][ encode( ini ) ] = 0;
  }
  for( int i = 0 ; i < r ; i ++ ){
    to = i + 1;
    for( int j = 0 ; j < c ; j ++ )
      block[ j ] = (a[ i + 1 ][ j ] == '#');
    for( auto _st : dp[ i ] ){
      from = _st.first;
      pscore = _st.second;
      djs.init( N );
      decode( from , ori );
      int mx = 0;
      for( int j = 0 ; j < c ; j ++ )
        if( ori[ j ] & 1 )
          mx = max( mx , ori[ j ] >> 1 );
      go( 0 , 0 , mx + 1 );
    }
  }
  int bst = -1; LL who = 0;
  for( auto _st : dp[ r ] ){
    from = _st.first;
    pscore = _st.second;
    int lst[ N ];
    decode( from , lst );
    int msk = 0 , cnt = 0;
    for( int i = 0 ; i < c ; i ++ )
      if( lst[ i ] ){
        msk |= (1 << (lst[ i ] >> 1));
        cnt += lst[ i ] & 1;
      }
    if( __builtin_popcount( msk ) != 1 )
      continue;
    if( cnt > 1 )
      continue;
    if( !(lst[ c - 1 ] & 1) )
      continue;
    if( pscore > bst ){
      bst = pscore;
      who = from;
    }
  }
  //cerr << bst << endl;
  for( int i = r ; i >= 1 ; i -- ){
    decode( who , ans[ i ] );
    who = bk[ i ][ who ];
  }
  printf( "Case %d:\n" , ++ _cs );
  for( int i = 1 ; i <= r ; i ++ , puts( "" ) )
    for( int j = 0 ; j < c ; j ++ )
      if( a[ i ][ j ] == '#' )
        putchar( a[ i ][ j ] );
      else if( ans[ i ][ j ] )
        putchar( 'C' );
      else
        putchar( '.' );
  puts( "" );
}
int main(){
  while( cin >> r >> c and r ){
    for( int i = 1 ; i <= r ; i ++ )
      cin >> a[ i ];
    solve();
  }
}
