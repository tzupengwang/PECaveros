#include <bits/stdc++.h>
using namespace std;
int dn[]={0,1,0,-1};
int dm[]={1,0,-1,0};
int m , n , d;
char cmd[ 9 ];
int main(){
  while( scanf( "%d%d" , &m , &n ) == 2 ){
    int cn = 0 , cm = 0 , cdir = 0;
    bool valid = true;
    while( n -- ){
      scanf( "%s%d" , cmd , &d );
      if( cmd[ 0 ] == 'T' ){
        if( d == 0 )
          cdir = ( cdir + 1 ) & 3;
        else
          cdir = ( cdir + 3 ) & 3;
      }else{
        cn += dn[ cdir ] * d;
        cm += dm[ cdir ] * d;
      }
      if( cn < 0 or cn > m or
          cm < 0 or cm > m )
        valid = false;
      //printf( "%d %d\n" , cn , cm );
    }
    if( valid )
      printf( "%d %d\n" , cm , cn );
    else
      puts( "-1" );
  }
}
