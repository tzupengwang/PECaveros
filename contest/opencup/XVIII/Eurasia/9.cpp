#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 303030
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
#define K 20
int rmq[ K ][ N ];
int query( int ql , int qr ){
  int bt = __lg( qr - ql + 1 );
  return max( rmq[ bt ][ ql ] ,
              rmq[ bt ][ qr - (1 << bt) + 1 ] );
}

char c[ N ];
int n , st[ N ] , len[ N ] , ptr;
int gt[ N << 1 ] , stmp , dst[ N << 1 ];
inline int id( int nx , int ny , int ok ){
  return ( st[ nx ] + ny ) * 2 + ok;
}
vector< pair<pair<int,int>,int> > wt[ N ];
int totlen , bkx[ N << 1 ] , bky[ N << 1 ];
int bkt[ N << 1 ] , bkok[ N << 1 ];
char bkc[ N << 1 ];
int nwx[ N << 1 ] , cwx[ N << 1 ];
int nwy[ N << 1 ] , cwy[ N << 1 ];
bool update( int sx , int sy , int tx , int ty , char sym , int nd , int ok , int tms ){
  int tid = id( tx , ty , ok );
  if( gt[ tid ] != stmp or
      nd < dst[ tid ] ){
    gt[ tid ] = stmp;
    dst[ tid ] = nd;
    wt[ nd ].push_back( { { tx , ty } , ok } );
    bkc[ tid ] = sym;
    bkx[ tid ] = sx;
    bky[ tid ] = sy;
    bkt[ tid ] = tms;
    bkok[ tid ] = ok;
    return true;
  }
  return false;
}
char ans[ N ];
void solve( int sx , int sy , int tx , int ty ){
  ++ stmp;
  int start = id( sx , sy , 1 );
  wt[ 0 ].push_back( { { sx , sy } , 1 } );
  gt[ start ] = stmp;
  dst[ start ] = 0;
  for( int i = 0 ; i <= totlen ; i ++ ){
    if( wt[ i ].empty() ) continue;
    //cerr << i << endl;
    for( auto j : wt[ i ] ){
      int idj = id( j.first.first , j.first.second , j.second );
      if( i != dst[ idj ] ) continue;
      int nx = j.first.first;
      int ny = j.first.second;
      int nok = j.second;
      //cerr << nx << " " << ny << endl;
      if( ny + 1 < len[ nx ] )
        update( nx , ny , nx , ny + 1 , 'l' , i + 1 , 1 , 1 );
      if( ny - 1 >= 0 )
        update( nx , ny , nx , ny - 1 , 'h' , i + 1 , 1 , 1 );
      if( nwx[ idj ] >= 0 )
        update( nx , ny , nwx[ idj ] , nwy[ idj ] , 'w' , i + 1 , 1 , 1 );
      if( cwx[ idj ] >= 0 )
        update( nx , ny , cwx[ idj ] , cwy[ idj ] , 'b' , i + 1 , 1 , 1 );
      update( nx , ny , nx , len[ nx ] - 1 , '$' , i + 1 , 1 , 1 );
      update( nx , ny , nx , 0 , '0' , i + 1 , 1 , 1 );
      if( nok ){
        {
          int bl = nx + 1 , br = n , ba = -1;
          while( bl <= br ){
            int bmid = (bl + br) >> 1;
            if( query( nx + 1 , bmid ) - 1 >= ny )
              ba = bmid , br = bmid - 1;
            else
              bl = bmid + 1;
          }
          if( ba != -1 )
            update( nx , ny , ba , ny , 'j' , i + ba - nx , 1 , ba - nx );
          else
            ba = n + 1;
          for( int u = nx + 1 ; u < ba ; u ++ )
            if( not update( nx , ny , u , len[ u ] - 1 , 'j' , i + u - nx , 0 , u - nx ) )
              break;
        }
        {
          int bl = 1 , br = nx - 1 , ba = -1;
          while( bl <= br ){
            int bmid = (bl + br) >> 1;
            if( query( bmid , nx - 1 ) - 1 >= ny )
              ba = bmid , bl = bmid + 1;
            else
              br = bmid - 1;
          }
          if( ba != -1 )
            update( nx , ny , ba , ny , 'k' , i + nx - ba , 1 , nx - ba );
          else
            ba = 0;
          for( int u = nx - 1 ; u > ba ; u -- )
            if( not update( nx , ny , u , len[ u ] - 1 , 'k' , i + nx - u , 0 , nx - u ) )
              break;
        }
      }
    }
  }
  int goal1 = id( tx , ty , 0 );
  int goal2 = id( tx , ty , 1 );
  int goal = -1;
  if( gt[ goal1 ] == stmp ){
    if( goal == -1 or dst[ goal1 ] < dst[ goal ] )
      goal = goal1;
  }
  if( gt[ goal2 ] == stmp ){
    if( goal == -1 or dst[ goal2 ] < dst[ goal ] )
      goal = goal2;
  }
  assert( goal != -1 );
  int at = 0;
  while( goal != start ){
    for( int i = 0 ; i < bkt[ goal ] ; i ++ )
      ans[ at ++ ] = bkc[ goal ];
    goal = id( bkx[ goal ] , bky[ goal ] , bkok[ goal ] );
  }
  reverse( ans , ans + at );
  ans[ at ] = '\0';
  puts( ans );
  for( int i = 0 ; i <= totlen ; i ++ )
    wt[ i ].clear();
}
int main(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    st[ i ] = ptr;
    scanf( "%s" , c + ptr );
    len[ i ] = strlen( c + ptr );
    ptr += len[ i ] + 1;
    rmq[ 0 ][ i ] = len[ i ];
  }
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      rmq[ j ][ i ] = max( rmq[ j - 1 ][ i ] ,
                           rmq[ j - 1 ][ i + (1 << (j - 1)) ] );
  int prex = -1 , prey = -1;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j < len[ i ] ; j ++ ){
      cwx[ id( i , j , 0 ) ] = prex;
      cwy[ id( i , j , 0 ) ] = prey;
      cwx[ id( i , j , 1 ) ] = prex;
      cwy[ id( i , j , 1 ) ] = prey;
      if( 'a' <= c[ st[ i ] + j ] and c[ st[ i ] + j ] <= 'z' and
          ( j == 0 or c[ st[ i ] + j - 1 ] < 'a' or
                      c[ st[ i ] + j - 1 ] > 'z' ) )
        prex = i, prey = j;
    }
  }
  int nxtx = -1 , nxty = -1;
  for( int i = n ; i >= 1 ; i -- ){
    for( int j = len[ i ] - 1 ; j >= 0 ; j -- ){
      nwx[ id( i , j , 0 ) ] = nxtx;
      nwy[ id( i , j , 0 ) ] = nxty;
      nwx[ id( i , j , 1 ) ] = nxtx;
      nwy[ id( i , j , 1 ) ] = nxty;
      if( 'a' <= c[ st[ i ] + j ] and c[ st[ i ] + j ] <= 'z' and
          ( j == 0 or c[ st[ i ] + j - 1 ] < 'a' or
                      c[ st[ i ] + j - 1 ] > 'z' ) )
        nxtx = i, nxty = j;
    }
  }
  totlen = accumulate( len + 1 , len + n + 1 , 0 );
  int q = getint(); while( q -- ){
    int sx = getint();
    int sy = getint() - 1;
    int tx = getint();
    int ty = getint() - 1;
    solve( sx , sy , tx , ty );
  }
}
