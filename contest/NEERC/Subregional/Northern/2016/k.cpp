#include <bits/stdc++.h>
using namespace std;
int n , d , m , y , ans;
int day[] = { 0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };
int main(){
  freopen( "king.in" , "r" , stdin );
  freopen( "king.out" , "w" , stdout );
  scanf( "%d%d%d" , &d , &m , &y );
  y -= 18;
  scanf( "%d" , &n );
  vector< pair<tuple<int,int,int>,int> > vv;
  ans = -1;
  int id = 0;
  while( n -- ){
    int dd , mm , yy;
    scanf( "%d%d%d" , &dd , &mm , &yy );
    vv.push_back( make_pair( make_tuple( yy , mm , dd ) , ++ id ) );
  }
  sort( vv.begin() , vv.end() );
  for( auto i : vv )
    if( i.first <= make_tuple( y , m , d ) )
      ans = i.second;
  printf( "%d\n" , ans );
}
