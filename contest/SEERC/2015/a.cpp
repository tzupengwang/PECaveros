#include <bits/stdc++.h>
using namespace std;
#define N 1010101
//struct Formula{
  //vector< Formula > vv;
  //int var , type;
  //// 0 for var , 1 for not , 2 for and , 3 for or
//} f[ 2 ];
char c[ 2 ][ N ];
int trans( char ctmp ){
  if( ctmp >= 'A' && ctmp <= 'Z' ) return ctmp - 'A' + 1;
  if( ctmp >= 'a' && ctmp <= 'z' ) return ctmp - 'a' + 27;
  return 0;
}
int pr[ N ] , len[ 2 ];
int vl[ 99 ];
int eval( int id , int l , int r ){
  if( l == r ) return vl[ trans( c[ id ][ l ] ) ];
  int ntype = -1;
  bool has[ 2 ] = { false , false };
  for( int ptr = l ; ptr <= r ; )
    if( c[ id ][ ptr ] == '~' ){
      ptr ++;
      int tvl = 0;
      if( trans( c[ id ][ ptr ] ) ){
        tvl = 1 - vl[ trans( c[ id ][ ptr ] ) ];
        ptr ++;
      }else if( c[ id ][ ptr ] == '(' ){
        tvl = 1 - eval( id , ptr + 1 , pr[ ptr ] - 1 );
        ptr = pr[ ptr ] + 1;
      }else assert( false );
      has[ tvl ] = true;
      if( ntype == 2 && has[ 0 ] ) return 0;
      if( ntype == 3 && has[ 1 ] ) return 1;
    }else if( c[ id ][ ptr ] == 'V' || c[ id ][ ptr ] == '^' ){
      int utype = c[ id ][ ptr ] == 'V' ? 3 : 2;
      if( ntype != -1 && ntype != utype )
        assert( false );
      ntype = utype;
      ptr ++;
    }else if( trans( c[ id ][ ptr ] ) ){
      int tvl = vl[ trans( c[ id ][ ptr ] ) ];
      has[ tvl ] = true;
      ptr ++;
      if( ntype == 2 && has[ 0 ] ) return 0;
      if( ntype == 3 && has[ 1 ] ) return 1;
    }else if( c[ id ][ ptr ] == '(' ){
      int tvl = eval( id , ptr + 1 , pr[ ptr ] - 1 );
      has[ tvl ] = true;
      ptr = pr[ ptr ] + 1;
      if( ntype == 2 && has[ 0 ] ) return 0;
      if( ntype == 3 && has[ 1 ] ) return 1;
    }else assert( false );
  if( ntype == -1 )
    return has[ 0 ] ? 0 : 1;
  if( ntype == 2 ){
    if( has[ 0 ] ) return 0;
    return 1;
  }
  if( ntype == 3 ){
    if( has[ 1 ] ) return 1;
    return 0;
  }
  assert( false );
  return 0;
}
void gen( int id ){
  len[ id ] = strlen( c[ id ] ) - 1;
  int tlen = 0;
  for( int i = 0 ; i < len[ id ] ; i ++ ){
    if( c[ id ][ i ] == ' ' ) continue;
    c[ id ][ tlen ++ ] = c[ id ][ i ];
  }
  len[ id ] = tlen;
  vector< int > vv;
  for( int i = 0 ; i < len[ id ] ; i ++ )
    if( c[ id ][ i ] == '(' )
      vv.push_back( i );
    else if( c[ id ][ i ] == ')' ){
      pr[ vv.back() ] = i;
      vv.pop_back();
    }
}
int main(){
  for( int i = 0 ; i < 2 ; i ++ ){
    fgets( c[ i ] , N , stdin );
    gen( i );
  }
  srand( 514514 );
#define K 2021
  for( int i = 0 ; i < K ; i ++ ){
    for( int j = 0 ; j < 55 ; j ++ )
      vl[ j ] = rand() % 2;
    int vl1 = eval( 0 , 0 , len[ 0 ] - 1 );
    int vl2 = eval( 1 , 0 , len[ 1 ] - 1 );
    if( vl1 != vl2 ){
      puts( "0" );
      exit( 0 );
    }
  }
  puts( "1" );
}
