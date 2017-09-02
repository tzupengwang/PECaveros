#include <bits/stdc++.h>
using namespace std;
int n;
vector< pair< pair<int,int> , pair<int,string> > > v;
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    string name;
    int d , m , y;
    cin >> name >> d >> m >> y;
    v.push_back( { { y , m } , { d , name } } );
  }
  sort( v.begin() , v.end() );
  cout << v.back().second.second << endl;
  cout << v[ 0 ].second.second << endl;
}
