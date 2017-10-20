#include <bits/stdc++.h>
using namespace std;
#define N 100
int s;
int main(){
  cin >> s;
  if( s % 3 == 0 ){
    int rep = s / 3;
    for( int i = 0 ; i < rep ; i ++ )
      cout << "21";
    cout << endl;
  }else if( s % 3 == 1 ){
    int rep = s / 3;
    for( int i = 0 ; i < rep ; i ++ )
      cout << "12";
    cout << "1" << endl;
  }else{
    int rep = s / 3;
    for( int i = 0 ; i < rep ; i ++ )
      cout << "21";
    cout << "2" << endl;
  }
}
