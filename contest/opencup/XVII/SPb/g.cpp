#include <bits/stdc++.h>
using namespace std;
int fans;
string ask(){
#ifdef LOCAL
  int rnd = ( (long long)rand() * rand() ) % fans;
  string ret = "A";
  while( rnd ){
    ret += (char)( rnd % 26 + 'A' );
    rnd /= 26;
  }
  return ret;
#else
  printf( "+\n" );
  fflush( stdout );
  char x[ 100 ];
  scanf( "%s" , x );
  string ret = "";
  for( int i = 0 ; x[ i ] ; i ++ )
    ret += x[ i ];
  return ret;
#endif
}
map<string,int> cnt;
int main(){
  int times = 1;
#ifdef LOCAL
  times = 1000;
#endif
  for( int rep = 0 ; rep < times ; rep ++ ){
#ifdef LOCAL
    srand( rep * rep );
    int gg = rand() % 7 + 1;
    fans = 1;
    while( gg -- ) fans *= 10;
#endif
    cnt.clear();
    for( int i = 0 ; i < 10000 ; i ++ )
      cnt[ ask() ] ++;

    double xx = 0 , x = 0;
    int sz = (int)cnt.size();
    for( auto i : cnt ){
      xx += i.second * i.second;
      x += i.second;
    }

    int bst = 10000000;
    double dlt = 1e9;
    for( int cand = 10 ; cand <= 10000000 ; cand *= 10 ){
      if( cand < sz ) continue;
      double var = xx / cand - ( x / cand ) * ( x / cand );
      double vv = ( -1e4 + cand * 1e4 ) / (double)cand / (double)cand;
      //double ddlt = fabs( vv - var );
      double ddlt = fabs( vv - var ) / vv;
      if( ddlt < dlt ){
        dlt = ddlt;
        bst = cand;
      }
    }
#ifdef LOCAL
    if( bst != fans )
      printf( "Wrong Answer expected %d found %d\n" , fans , bst );
    //else
      //puts( "Accepted" );
#else
    printf( "= %d\n" , bst );
    fflush( stdout );
#endif
  }
}
