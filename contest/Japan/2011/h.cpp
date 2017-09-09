#include <bits/stdc++.h>
using namespace std;
const int mod = 2011;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int mul( int a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
int inv( int a ){
  return mpow( a , mod - 2 );
}
int n;
#define N 111
char c[ N ][ N ];
int to[ N ][ N ];
void init(){
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c[ i ] );
    vector<int> v;
    for( int j = 0 ; c[ i ][ j ] ; j ++ )
      if( c[ i ][ j ] == '(' )
        v.push_back( j );
      else if( c[ i ][ j ] == ')' ){
        to[ i ][ v.back() ] = j;
        v.pop_back();
      }
  }
}
int pri( char ctmp ){
  if( ctmp == '+' ) return 1;
  if( ctmp == '-' ) return 1;
  if( ctmp == '*' ) return 2;
  assert( false );
  return -1;
}
int cal( int up , int dn , int l , int r ){
  int base = -1;
  for( int j = l ; j <= r ; j ++ ){
    for( int i = up ; i <= dn ; i ++ )
      if( c[ i ][ j ] != '.' ){
        base = i;
        break;
      }
    if( base != -1 ) break;
  }
  //printf( "%d %d %d %d : %d\n" , up , dn , l , r , base );
  vector<int> dd;
  vector<char> op;
  bool tag = false;
  bool pre = false;
  for( int j = l ; j <= r ; ){
    if( c[ base ][ j ] == '(' ){
      int vl = cal( up , dn , j + 1 , to[ base ][ j ] - 1 );
      j = to[ base ][ j ] + 1;
      if( j <= r and up <= base - 1 and
          '0' <= c[ base - 1 ][ j ] and
          c[ base - 1 ][ j ] <= '9' ){
        vl = mpow( vl , c[ base - 1 ][ j ] - '0' );
        j ++;
      }
      if( tag ){
        vl = sub( 0 , vl );
        tag = false;
      }
      pre = true;
      dd.push_back( vl );
    }else if( c[ base ][ j ] == '-' ){
      int til = j;
      while( til <= r and c[ base ][ til ] == '-' ) til ++;
      if( til - j == 1 ){
        if( !pre )
          tag = !tag;
        else{
          if( dd.empty() )
            dd.push_back( 0 );
          while( op.size() and pri( op.back() ) >= pri( '-' ) ){
            int d2 = dd.back(); dd.pop_back();
            int d1 = dd.back(); dd.pop_back();
            char who = op.back(); op.pop_back();
            if( who == '+' )
              dd.push_back( add( d1 , d2 ) );
            else if( who == '-' )
              dd.push_back( sub( d1 , d2 ) );
            else if( who == '*' )
              dd.push_back( mul( d1 , d2 ) );
            else
              assert( false );
          }
          op.push_back( '-' );
          pre = false;
        }
      }else{
        int tup = cal( up , base - 1 , j , til - 1 );
        int tdn = cal( base + 1 , dn , j , til - 1 );
        int vl = mul( tup , inv( tdn ) );
        pre = true;
        if( tag ){
          vl = sub( 0 , vl );
          tag = false;
        }
        dd.push_back( vl );
      }
      j = til;
    }else if( '0' <= c[ base ][ j ] and c[ base ][ j ] <= '9' ){
      int til = j;
      while( til <= r and '0' <= c[ base ][ til ] and c[ base ][ til ] <= '9' )
        til ++;
      int rr = 0;
      while( j < til ){
        rr = add( mul( rr , 10 ) , c[ base ][ j ] - '0' );
        j ++;
      }
      if( j <= r and up <= base - 1 and
          '0' <= c[ base - 1 ][ j ] and
          c[ base - 1 ][ j ] <= '9' ){
        rr = mpow( rr , c[ base - 1 ][ j ] - '0' );
        j ++;
      }
      if( tag ){
        rr = sub( 0 , rr );
        tag = false;
      }
      dd.push_back( rr );
      pre = true;
    }else if( c[ base ][ j ] == '+' or c[ base ][ j ] == '*' ){
      while( op.size() and pri( op.back() ) >= pri( c[ base ][ j ] ) ){
        int d2 = dd.back(); dd.pop_back();
        int d1 = dd.back(); dd.pop_back();
        char who = op.back(); op.pop_back();
        if( who == '+' )
          dd.push_back( add( d1 , d2 ) );
        else if( who == '-' )
          dd.push_back( sub( d1 , d2 ) );
        else if( who == '*' )
          dd.push_back( mul( d1 , d2 ) );
        else
          assert( false );
      }
      op.push_back( c[ base ][ j ] );
      j ++;
      pre = false;
    }else j ++;
  }
  while( op.size() ){
    int d2 = dd.back(); dd.pop_back();
    int d1 = dd.back(); dd.pop_back();
    char who = op.back(); op.pop_back();
    if( who == '+' )
      dd.push_back( add( d1 , d2 ) );
    else if( who == '-' )
      dd.push_back( sub( d1 , d2 ) );
    else if( who == '*' )
      dd.push_back( mul( d1 , d2 ) );
    else
      assert( false );
  }
  return dd.back();
}
void solve(){
  printf( "%d\n" , cal( 0 , n - 1 , 0 , strlen( c[ 0 ] ) - 1 ) );
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
