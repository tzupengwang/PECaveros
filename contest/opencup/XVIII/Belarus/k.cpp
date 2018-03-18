#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
struct Trie{
  int nd[ N ][ 26 ] , msk[ N ] , alive[ N ] , nxt , root;
  bool tag[ N ];
  vector<int> wt[ N ];
  int new_node(){
    ++ nxt;
    msk[ nxt ] = 0;
    alive[ nxt ] = 0;
    wt[ nxt ].clear();
    tag[ nxt ] = false;
    return nxt;
  }
  void init(){
    nxt = 0;
    root = new_node();
  }
  void modify( char* c , int now , int cur , int len , int dlt , int who ){
    if( cur == len ){
      alive[ now ] += dlt;
      if( dlt == 1 )
        wt[ now ].push_back( who );
      tag[ now ] = true;
      return;
    }
    int cc = c[ cur ] - 'a';
    if( !( (msk[ now ] >> cc) & 1 ) ){
      msk[ now ] |= (1 << cc);
      nd[ now ][ cc ] = new_node();
    }
    alive[ now ] -= alive[ nd[ now ][ cc ] ];
    modify( c , nd[ now ][ cc ] , cur + 1 , len , dlt , who );
    alive[ now ] += alive[ nd[ now ][ cc ] ];
  }
  void modify( char* c , int len , int dlt , int who ){
    modify( c , root , 0 , len , dlt , who );
  }
  void kill( int now , char* c , int len , vector<int>& wtk ){
    for( int i = 0 ; i < len ; i ++ ){
      now = nd[ now ][ c[ i ] - 'a' ];
      assert( now );
    }
    wtk = wt[ now ];
  }
  void shortest( int now , char* c , int& len ){
    if( !now or tag[ now ] ) return;
    while( msk[ now ] ){
      int nb = __lg( msk[ now ] & (-msk[ now ]) );
      if( alive[ nd[ now ][ nb ] ] == 0 ){
        msk[ now ] ^= (1 << nb);
        continue;
      }
      c[ len ++ ] = 'a' + nb;
      shortest( nd[ now ][ nb ] , c , len );
      return;
    }
  }
} trie , trie2;
char c[ N ];
int n , k , st[ N ] , len[ N ] , ptr;
bool died[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c + ptr );
    st[ i ] = ptr;
    len[ i ] = strlen( c + ptr );
    ptr += len[ i ] + 1;
  }
  trie.init();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j + k <= len[ i ] ; j ++ )
      trie.modify( c + st[ i ] + j , k , +1 , i );
}
char ans[ N ] , goal[ N ];
int alen;
#define K 111
vector<int> wt;
void Kill(){
  for( int i : wt ){
    if( died[ i ] ) continue;
    died[ i ] = true;
    for( int j = 0 ; j + k <= len[ i ] ; j ++ )
      trie.modify( c + st[ i ] + j , k , -1 , i );
  }
}
char tmp[ K ][ K ];
int tlen[ K ];
void solve(){
  trie.shortest( trie.root , ans , alen );
  wt.clear();
  trie.kill( trie.root , ans , alen , wt );
  Kill();
  while( trie.alive[ trie.root ] ){
    int gt = 0;
    for( int i = 0 ; i < k ; i ++ ){
      int now = trie.root;
      for( int j = alen - i ; j < alen ; j ++ ){
        now = trie.nd[ now ][ ans[ j ] - 'a' ];
        if( !now ) break;
      }
      if( !now or trie.alive[ now ] == 0 ) continue;
      tlen[ gt ] = 0;
      trie.shortest( now , tmp[ gt ] , tlen[ gt ] );
      gt ++;
    }
    trie2.init();
    for( int i = 0 ; i < gt ; i ++ ){
      trie2.modify( tmp[ i ] , tlen[ i ] , +1 , i );
      tmp[ i ][ tlen[ i ] ] = 0;
    }
    trie2.shortest( trie2.root , ans , alen );
    wt.clear();
    trie.kill( trie.root , ans + alen - k , k , wt );
    Kill();
  }
  puts( ans );
}
int main(){
  init();
  solve();
}
