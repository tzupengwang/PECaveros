#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 3030
char c[ N ] , ac[ N ];
int len , alen;
int vv[ N ][ N ] , vlen[ N ];
bool okay( int now , int id ){
  if( vv[ id ][ 0 ] > now ) return false;
  if( vv[ id ][ vlen[ id ] - 1 ] < len - now ) return false;
  for( int i = 0 ; i + 1 < vlen[ id ] ; i ++ )
    if( vv[ id ][ i + 1 ] - vv[ id ][ i ] > now )
      return false;
  return true;
}
char color[] = "RGB";
void go( int now , int id ){
  if( vlen[ id ] == 0 ) return;
  //if( vv.empty() ) return;
  if( now >= alen ) return;
  //if( now + now >= len ) return;
  if( now ){
    if( okay( now , id ) ){ 
      alen = now;
      for( int i = 0 ; i < alen ; i ++ )
        ac[ i ] = c[ i ];
      return;
    }
  }
  if( c[ now ] == '*' ){
    int ord[ 3 ] = {0, 1, 2};
    //random_shuffle( ord , ord + 3 );
    for( int _ = 0 ; _ < 3 ; _ ++ ){
      char g = color[ ord[ _ ] ];
      c[ now ] = g;
      int nid = id + 1;
      vlen[ nid ] = 0;
      //vector<int> nv;
      //for( auto i : vv )
      for( int j = 0 ; j < vlen[ id ] ; j ++ ){
        int i = vv[ id ][ j ];
        if( i + now < len and
            ( c[ i + now ] == '*' or
              c[ i + now ] == c[ now ] ) )
          vv[ nid ][ vlen[ nid ] ++ ] = i;
          //nv.push_back( i );
      }
      go( now + 1 , nid );
      //if( now + 1 >= alen ){
        //c[ now ] = '*';
        //return;
      //}
    }
    c[ now ] = '*';
  }else{
    //vector<int> nv;
    int nid = id + 1;
    vlen[ nid ] = 0;
    //for( auto i : vv )
    for( int j = 0 ; j < vlen[ id ] ; j ++ ){
      int i = vv[ id ][ j ];
      if( i + now < len and
          ( c[ i + now ] == '*' or
            c[ i + now ] == c[ now ] ) )
        vv[ nid ][ vlen[ nid ] ++ ] = i;
        //nv.push_back( i );
    }
    go( now + 1 , nid );
    //go( now + 1 , nv ); 
  }
}
bool test( int ii ){
  int lst = len - ii;
  for( int i = 0 ; i < ii ; i ++ )
    if( c[ i ] != '*' and c[ lst + i ] != '*' and
        c[ i ] != c[ lst + i ] )
      return false;
  alen = ii;
  for( int i = 0 ; i < ii ; i ++ )
    if( c[ i ] == '*' and c[ lst + i ] == '*' )
      ac[ i ] = 'R';
    else
      ac[ i ] = (c[ i ] == '*' ? c[ lst + i ] : c[ i ] );
  return true;
}
void solve(){
  alen = len;
  for( int i = 0 ; i < len ; i ++ )
    ac[ i ] = (c[ i ] == '*' ? 'R' : c[ i ]);
  //vector<int> cand;
  vlen[ 0 ] = len - 1;
  for( int i = 1 ; i < len ; i ++ )
    vv[ 0 ][ i - 1 ] = i;
    //cand.push_back( i );
  go( 0 , 0 );

  //for( int i = len / 2 + len % 2 ; i < alen ; i ++ )
    //if( test( i ) )
      //return;
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    scanf( "%s" , c );
    len = strlen( c );
    int cnt = 0;
    for( int i = 0 ; i + i < len ; i ++ )
      if( c[ i ] == '*' )
        cnt ++;
    //bool rev = (cnt >= 10);
    //if( rev )
      //reverse( c , c + len );
    solve();
    //if( rev )
      //reverse( ac , ac + alen );
    ac[ alen ] = 0;
    puts( ac );
  }
}
