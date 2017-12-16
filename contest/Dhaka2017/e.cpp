#include <bits/stdc++.h>
using namespace std;
bool isLeapYear(int year){
  if (year % 400 == 0) return true;
  else if(year % 100 == 0) return false;
  else if(year % 4 == 0) return true;
  else return false;
}
int cs;
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    int d , m , y , yy;
    cin >> d >> m >> y >> yy;
    int ans = yy - y;
    if( d == 29 and m == 2 ){
      ans = 0;
      for( int i = y + 1 ; i <= yy ; i ++ )
        if( isLeapYear( i ) )
          ans ++;
    }
    printf( "Case %d: %d\n" , ++ cs , ans );
  }
}
