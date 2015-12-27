#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef priority_queue<int> heap;
int main(){
  heap h1 , h2;
  h1.push( 1 );
  h2.push( 4 );
  h1.join( h2 );
  h1.size(); // 2
  h2.size(); // 0
  h1.top(); // 4
}
