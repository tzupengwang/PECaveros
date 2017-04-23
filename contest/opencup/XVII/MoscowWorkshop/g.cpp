#include <bits/stdc++.h>
using namespace std;
#define N 1010101
char c[ N ];
int main(){
  scanf( "%s" , c );
  int len = strlen( c );
  int ans = 0;
  int l = 0 , r = len - 1;
  while( l < len and c[ l ] == 'L' ){
    l ++;
    ans ++;
  }
  while( r >= 0 and c[ r ] == 'R' ){
    r --;
    ans ++;
  }
  if( l <= r ) ans ++;
  printf( "%d\n" , ans );
}
