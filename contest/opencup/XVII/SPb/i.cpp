#include<bits/stdc++.h>
using namespace std;

typedef long long ll ;
typedef pair< int , int > ii ;

ii gcd(int a, int b){
	if(b == 0) return {1, 0};
  ii q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}

int n ;
int s[ 10005 ] ;
int pos[ 10005 ] ;
ll A[ 40005 ] , B[ 40005 ] ;
const ll bs = 1664525LL , co = 1013904223LL ;
const ll mod = ( 1LL << 32 ) ;

void init() {
  A[ 0 ] = bs , B[ 0 ] = co ;
  for ( int i = 1 ; i < 40000 ; i ++ ) {
    A[ i ] = A[ i - 1 ] * bs % mod ;
    B[ i ] = ( B[ i - 1 ] * bs + co ) % mod ;
  }

  scanf( "%d" , &n ) ;
  for ( int i = 0 ; i < n ; i ++ ) {
    scanf( "%d" , &s[ i ] ) ;
    pos[ s[ i ] ] = s[ i ] ;
  }
}

void process() {
  for ( int i = n ; i >= 1 ; i -- ) {
    if ( i > pos[ i ] ) {
      for ( int md = i - 1 ; md > pos[ i ] ; md -- ) {
        int range = n , 
      }
    }
  }
}

int main() 
  init() ;
  process() ;
  return 0 ;
}
