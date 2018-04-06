#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL t , n , _cs;
int main(){
  scanf( "%lld" , &t ); while( t -- ){
    scanf( "%lld" , &n );
    printf( "Case #%lld: %lld\n" , ++ _cs , n / 3 );
  }
}
