#include <bits/stdc++.h>
using namespace std;
#define N 101010
struct Nd{
  Nd *t[ 2 ];
  int cc;
  Nd(){
    t[ 0 ] = t[ 1 ] = NULL;
    cc = 0;
  }
};
int n , m , a;
char c[ N ];
Nd* root;
int Cnt( Nd* now ){
  return now ? now->cc : 0;
}
void query( Nd* now , int bt ){
  if( !now or bt >= m ) return;
  if( c[ bt ] == '1' ){
    a += Cnt( now->t[ 1 ] );
    query( now->t[ 0 ] , bt + 1 );
  }else{
    query( now->t[ 1 ] , bt + 1 );
  }
}
void add( Nd* now , int bt ){
  now->cc ++;
  if( bt == m ) return;
  int v = c[ bt ] - '0';
  if( !now->t[ v ] ) now->t[ v ] = new Nd();
  add( now->t[ v ] , bt + 1 );
}
int main(){
  root = new Nd();
  scanf( "%d%d" , &n , &m );
  while( n -- ){
    scanf( "%s" , c );
    a = 0;
    query( root , 0 );
    add( root , 0 );
    printf( "%d\n" , a );
    fflush( stdout );
  }
}
