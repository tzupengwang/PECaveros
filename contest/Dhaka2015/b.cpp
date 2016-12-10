#include <bits/stdc++.h>
using namespace std;
map<string,int> M , M2;
int main(){
  M[ "JAN" ] = 31;
  M[ "FEB" ] = 28;
  M[ "MAR" ] = 31;
  M[ "APR" ] = 30;
  M[ "MAY" ] = 31;
  M[ "JUN" ] = 30;
  M[ "JUL" ] = 31;
  M[ "AUG" ] = 31;
  M[ "SEP" ] = 30;
  M[ "OCT" ] = 31;
  M[ "NOV" ] = 30;
  M[ "DEC" ] = 31;
  M2[ "SUN" ] = 0; 
  M2[ "MON" ] = 1; 
  M2[ "TUE" ] = 2; 
  M2[ "WED" ] = 3; 
  M2[ "THU" ] = 4; 
  M2[ "FRI" ] = 5; 
  M2[ "SAT" ] = 6;
  int t; scanf( "%d" , &t ); while( t -- ){
    string mon , day;
    cin >> mon >> day;
    int mn = M[ mon ];
    int dy = M2[ day ];
    int ans = 0;
    for( int i = 0 ; i < mn ; i ++ ){
      if( dy >= 5 ) ans ++;
      dy = ( dy + 1 ) % 7;
    }
    printf( "%d\n" , ans );
  }
} 
