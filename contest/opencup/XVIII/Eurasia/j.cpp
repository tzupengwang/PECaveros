#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , l;
vector< pair<LL,LL> > a;
void init(){
  scanf( "%lld%lld" , &n , &l );
  l *= 1000;
  a.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld" , &a[ i ].first , &a[ i ].second );
}
const double eps = 1e-10;
void solve(){
  sort( a.begin() , a.end() , greater<pair<LL,LL>>() );
  double ans = 0 , res = l , v = 0;
  for( auto i : a ){
    if( res < eps ) break;
    double aa = (double)i.first;
    double tt = (double)i.second / 1e6;
    double nv = v + aa * tt;
    if( ( v + nv ) * tt * 0.5 < res + eps ){
      res -= ( v + nv ) * tt * 0.5;
      v = nv;
      ans += tt;
    }else{
      double bl = 0 , br = tt;
      for( int _ = 0 ; _ < 50 ; _ ++ ){
        double bmid = (bl + br) * 0.5;
        double tnv = v + aa * bmid;
        if( ( v + tnv ) * bmid * 0.5 < res + eps )
          bl = bmid;
        else
          br = bmid;
      }
      ans += bl;
      res = 0;
    }
  }
  if( res > eps ) ans += res / (double)v;
  printf( "%.12f\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
