#include <bits/stdc++.h>
using namespace std;
#define N 101010
char c[ N ] , z[ N ];
bool gg[ 26 ];
int lenc , lenz;
void init(){
  scanf( "%s%s" , c , z );
  lenc = strlen( c );
  lenz = strlen( z );
  for( int i = 0 ; i < lenc ; i ++ )
    gg[ c[ i ] - 'a' ] = true;
}
bool st[ 26 ];
string res[ 26 ];
int used[ 11 ][ N ];
bool got[ 11 ][ N ];
void output(){
  for( int i = 0 ; i < 26 ; i ++ )
    if( gg[ i ] )
      printf( "%c %s\n" , (char)( i + 'a' ) , res[ i ].c_str() );
}
inline bool okay( const string& ss ){
  int len = ss.length();
  int vl = 0;
  for( int i = 1 ; i <= len ; i ++ ){
    vl = vl * 2 + ss[ i - 1 ] - '0';
    if( got[ i ][ vl ] ) return false;
  }
  return used[ len ][ vl ] == 0;
}
inline void add( int id , const string& ss ){
  res[ id ] = ss;
  int vl = 0 , len = ss.length();
  for( int i = 1 ; i <= len ; i ++ ){
    vl = vl * 2 + ss[ i - 1 ] - '0';
    used[ i ][ vl ] ++;
  }
  got[ len ][ vl ] = true;
}
inline void rm( int id , const string& ss ){
  int vl = 0 , len = ss.length();
  for( int i = 1 ; i <= len ; i ++ ){
    vl = vl * 2 + ss[ i - 1 ] - '0';
    used[ i ][ vl ] --;
  }
  got[ len ][ vl ] = false;
}
void go( int nowc , int nowl ){
  if( nowc == lenc ){
    if( nowl == lenz ) output();
    return;
  }
  if( st[ c[ nowc ] - 'a' ] ){
    int tlen = res[ c[ nowc ] - 'a' ].length();
    if( nowl + tlen > lenz ) return;
    for( int i = 0 ; i < tlen ; i ++ )
      if( z[ nowl + i ] != res[ c[ nowc ] - 'a' ][ i ] )
        return;
    go( nowc + 1 , nowl + tlen );
  }else{
    st[ c[ nowc ] - 'a' ] = true;
    string ts = "";
    for( int i = 1 ; i <= 10 && nowl + i <= lenz ; i ++ ){
      ts += z[ nowl + i - 1 ];
      if( okay( ts ) ){
        add( c[ nowc ] - 'a' , ts );
        go( nowc + 1 , nowl + i );
        rm( c[ nowc ] - 'a' , ts );
      }
    }
    st[ c[ nowc ] - 'a' ] = false;
  }
}
void solve(){
  go( 0 , 0 );
}
int main(){
  freopen( "prefix.in" , "r" , stdin );
  freopen( "prefix.out" , "w" , stdout );
  init();
  solve();
}
