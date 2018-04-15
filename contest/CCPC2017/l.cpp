#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
bool leap( int yr ){
  if( yr % 100 == 0 ) return false;
  return yr % 4 == 0;
}
int wd[ 123 ][ 13 ][ 32 ];
int dys[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int Days( int i , int j ){
  if( j != 2 ) return dys[ j ];
  if( leap( i ) ) return 29;
  return 28;
}
void build(){
  int p = 0;
  for( int i = 2007 ; i <= 2100 ; i ++ )
    for( int j = 1 ; j <= 12 ; j ++ )
      for( int d = 1 ; d <= Days( i , j ) ; d ++ ){
        wd[ i - 2000 ][ j ][ d ] = p;
        p = (p + 1) % 7;
      }
  int dlt = 7 - wd[ 16 ][ 3 ][ 13 ];
  for( int i = 2007 ; i <= 2100 ; i ++ )
    for( int j = 1 ; j <= 12 ; j ++ )
      for( int d = 1 ; d <= Days( i , j ) ; d ++ )
        wd[ i - 2000 ][ j ][ d ] = (wd[ i - 2000 ][ j ][ d ] + dlt) % 7;
}
int fst( int year ){
  int got = 0;
  for( int i = 1 ; i <= 31 ; i ++ ){
    if( wd[ year - 2000 ][ 3 ][ i ] )
      continue;
    got ++;
    if( got == 2 ) return i;
  }
  assert( false );
  return -1;
}
int snd( int year ){
  for( int i = 1 ; i <= 30 ; i ++ ){
    if( wd[ year - 2000 ][ 11 ][ i ] )
      continue;
    return i;
  }
  assert( false );
  return -1;
}
int yr , mn , dy , hr , Min , sec;
string solve(){
  if( mn < 3 or mn > 11 ) return "PST";
  if( mn > 3 and mn < 11 ) return "PDT";
  if( mn == 3 ){
    int day = fst( yr );
    if( dy < day ) return "PST";
    if( dy > day ) return "PDT";
    if( make_tuple( hr , Min , sec ) <=
        make_tuple( 1 , 59 , 59 ) ) return "PST";
    if( make_tuple( hr , Min , sec ) >=
        make_tuple( 3 , 0 , 0 ) ) return "PDT";
    return "Neither";
  }else{
    int day = snd( yr );
    if( dy < day ) return "PDT";
    if( dy > day ) return "PST";
    if( make_tuple( hr , Min , sec ) <=
        make_tuple( 0 , 59 , 59 ) ) return "PDT";
    if( make_tuple( hr , Min , sec ) >=
        make_tuple( 2 , 0 , 0 ) ) return "PST";
    return "Both";
  }
}
int cs;
int main(){
  build();
  int t; cin >> t; while( t -- ){
    scanf( "%d-%d-%d %d:%d:%d" , &yr , &mn , &dy , &hr , &Min , &sec );
    printf( "Case #%d: %s\n" , ++ cs , solve().c_str() );
  }
}
