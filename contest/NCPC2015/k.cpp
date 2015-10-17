#include <bits/stdc++.h>
using namespace std;
#define N 9
int __, n = 6;
int a[ N ] , b[ N ] , c[ N ] , bs[ N ];
set<int> s1 , s2;
typedef set<int>::iterator si;
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &b[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    c[ i ] = i;
}
void solve(){
  s1.clear();
  s2.clear();
  do{
    int num1 = 0, num2 = 0;
    for( int i = 0 ; i < n ; i ++ ){
      num1 = num1 + bs[ i ] * a[ c[ i ] ];
      num2 = num2 + bs[ i ] * b[ c[ i ] ];
      s1.insert( num1 );
      s2.insert( num2 );
    }
  }while( next_permutation( c , c + n ) );
  int ans1 = 0, ans2 = 0;
  for( si it = s1.begin() ; it != s1.end() ; it ++ )
    if( s2.count( *it ) == 0 ) ans1 ++;
  for( si it = s2.begin() ; it != s2.end() ; it ++ )
    if( s1.count( *it ) == 0 ) ans2 ++;
  printf( "%d %d\n" , ans1 , ans2 );
}
int main(){
  bs[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    bs[ i ] = bs[ i - 1 ] * 10;
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
