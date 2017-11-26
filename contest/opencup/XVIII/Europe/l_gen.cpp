#include <bits/stdc++.h>
using namespace std;
int main(){
  printf( "%d\n" , 200000 );
  for( int i = 0 ; i < 200000 ; i ++ )
    printf( "%c %d %d %d\n" , 
            rand() % 2 + 'A' ,
            rand() % 2001 - 1000 ,
            rand() % 2001 - 1000 ,
            rand() % 998 + 2 );
}
