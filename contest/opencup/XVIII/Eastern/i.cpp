#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
char c[ N ];
int main(){
  scanf( "%s" , c );
  int l = 0 , r = strlen( c ) - 1;
  while( l < r and c[ l ] == 'A' ) l ++;
  while( l < r and c[ r ] == '!' ) r --;
  if( c[ 0 ] == 'A' and c[ strlen( c ) - 1 ] == '!' and l == r )
    puts( "Panic!" );
  else
    puts( "No panic" );
}
