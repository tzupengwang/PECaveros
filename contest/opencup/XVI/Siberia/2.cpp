#include <bits/stdc++.h>
using namespace std;
#define N 1021
vector<string> vv;
map<string,int> M;
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  int n; scanf( "%d" , &n ); while( n -- ){
    string ss; cin >> ss;
    int iter = 0;
    while( ss[ iter ] != '.' ) iter ++;
    ss = ss.substr( iter + 1 , N );
    if( M.count( ss ) == 0 )
      vv.push_back( ss );
    M[ ss ] ++;
  }
  for( auto i : vv )
    printf( "%s: %d\n" , i.c_str() , M[ i ] );
}
