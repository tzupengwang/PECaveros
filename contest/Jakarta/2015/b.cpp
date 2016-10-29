#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
int _cs;
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    scanf( "%lld" , &n );
    printf( "Case #%d: %s\n" , ++ _cs , n % 2 ? "UDIN" : ( ( n / 2 ) % 2 ? "UDIN" : "UCOK" ) );
  }
}
