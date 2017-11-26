#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 2048
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
int v[ N ][ N ];
int lv[ N << 1 ][ N ] , to[ N << 1 ][ N ];
int n;
void pull( int no , int l , int r ){
  for( int i = 0 ; i < n ; i ++ )
    lv[ no ][ i ] = lv[ L( no ) ][ i ];
  for( int i = 0 ; i < n ; i ++ ){
    int gt = to[ L( no ) ][ i ];
    int bst = gt;
    if( lv[ R( no ) ][ (gt + 1) % n ] >
        lv[ R( no ) ][ bst ] )
      bst = (gt + 1) % n;
    if( lv[ R( no ) ][ (gt + n - 1) % n ] >
        lv[ R( no ) ][ bst ] )
      bst = (gt + n - 1) % n;
    to[ no ][ i ] = to[ R( no ) ][ bst ];
  }
}
void build_st( int no , int l , int r ){
  if( l == r ){
    for( int i = 0 ; i < n ; i ++ ){
      lv[ no ][ i ] = v[ i ][ l ];
      to[ no ][ i ] = i;
    }
    return;
  }
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
  pull( no , l , r );
}
void modify( int no , int l , int r , int qr , int qc , int qv ){
  if( l == r ){
    lv[ no ][ qr ] = qv;
    return;
  }
  if( qc <= mid )
    modify( L( no ) , l , mid , qr , qc , qv );
  else
    modify( R( no ) , mid + 1 , r , qr , qc , qv );
  pull( no , l , r );
}
inline int getint(){
  int _x=0; char _tc=getchar();    
  while(_tc<'0'||_tc>'9') _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
int r , c;

inline int next( int ci , int cj ){
  int bst = ci , nj = (cj + 1) % c;
  if( v[ (ci + 1) % r ][ nj ] >
      v[ bst ][ nj ] )
    bst = (ci + 1) % r;
  if( v[ (ci + r - 1) % r ][ nj ] >
      v[ bst ][ nj ] )
    bst = (ci + r - 1) % r;
  return bst;
}
int px , py;
int nnxt[ N ] , stk[ N ];
bool oncyc[ N ] , vst[ N ];
pair<int,int> go( int row_num , int k ){
  int col_num = 0;
  while( k -- ){
    row_num = next( row_num , col_num );
    col_num ++;
  }
  return { row_num , col_num };
}
pair<int,int> query( int k ){
  while( k > 0 ){
    if( py == 0 ) break;
    px = next( px , py );
    py = (py + 1) % c;
    k --;
  }
  if( k == 0 ) return {px, py};
  for( int i = 0 ; i < r ; i ++ ){
    nnxt[ i ] = to[ 1 ][ i ];
    oncyc[ i ] = false;
    vst[ i ] = false;
  }
  int stksz = 0;
  stk[ stksz ++ ] = px;
  vst[ px ] = true;
  int oc = 0;
  for( int i = 0 ; i < stksz ; i ++ ){
    int nxt = nnxt[ stk[ i ] ];
    if( vst[ nxt ] ){
      stk[ stksz ] = nxt;
      for( int j = i ; ; j -- ){
        oncyc[ stk[ j ] ] = true;
        oc ++;
        if( stk[ j ] == nxt ) break;
      }
      break;
    }
    stk[ stksz ++ ] = nxt;
    vst[ nxt ] = true;
  }
  int notoc = stksz - oc;
  for( int i = 0 ; i < notoc ; i ++ ){
    if( k == 0 ) return { stk[ i ] , 0 };
    if( k < c ) return go( stk[ i ] , k );
    k -= c;
  }
  k %= (oc * c);
  for( int i = notoc ; i < stksz ; i ++ ){
    if( k == 0 ) return { stk[ i ] , 0 };
    if( k < c ) return go( stk[ i ] , k );
    k -= c;
  }
  return { stk[ stksz ] , 0 };
}
int main(){
  n = r = getint();
  c = getint();
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ )
      v[ i ][ j ] = getint();
  for( int i = 0 ; i < r ; i ++ )
    v[ i ][ c ] = v[ i ][ 0 ];
  build_st( 1 , 0 , c );
  int q = getint(); while( q -- ){
    char cmd[ 9 ];
    scanf( "%s" , cmd );
    if( cmd[ 0 ] == 'c' ){
      int x = getint();
      int y = getint();
      int vv = getint();
      x --;
      y --;
      modify( 1 , 0 , c , x , y , vv );
      if( y == 0 )
        modify( 1 , 0 , c , x , c , vv );
      v[ x ][ y ] = vv;
      continue;
    }
    int stp = getint();
    pair<int,int> ret = query( stp );
    printf( "%d %d\n" , ret.first + 1 , ret.second + 1 );
    tie( px , py ) = ret;
  }
}
