#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 255
#define W 10101
const double eps = 1e-10;
const LL inf = 10000000000000000LL;
int w;
LL dp[ W ] , tdp[ W ];
deque< pair<LL,LL> > dqc[ W ];
#define M first
#define C second
void upd( LL wi , LL ti , LL di ){
  if( di == 0 ){
    for( int i = wi ; i <= w ; i ++ )
      if( dp[ i - wi ] != - inf )
        dp[ i ] = max( dp[ i ] , dp[ i - wi ] + ti );
    return;
  }
  for( int i = 0 ; i <= w ; i ++ )
    tdp[ i ] = dp[ i ];
  for( int i = 0 ; i < wi ; i ++ )
    dqc[ i ].clear();
  for( int i = 0 ; i <= w ; i ++ ){
    LL id = i / wi;
    deque< pair<LL,LL> >& dq = dqc[ i % wi ];
    if( tdp[ i ] != -inf ){
      LL ai = id * di;
      LL bi = tdp[ i ] - (id * ti) - di * (id * id + id) / 2;
      pair<LL,LL> p3 = {ai, bi};
      while( dq.size() > 1u ){
        pair<LL,LL> p1 = dq[ dq.size() - 2u ];
        pair<LL,LL> p2 = dq[ dq.size() - 1u ];
        if( (long double)(p1.C - p3.C) * (p2.M - p1.M) <=
            (long double)(p1.C - p2.C) * (p3.M - p1.M) )
          dq.pop_back();
        else
          break;
      }
      dq.push_back( p3 );
    }
    while( dq.size() > 1u ){
      pair<LL,LL> p1 = dq[ 0 ];
      pair<LL,LL> p2 = dq[ 1 ];
      if( (p1.C - p2.C) <= id * (p2.M - p1.M) )
        dq.pop_front();
      else
        break;
    }
    if( dq.size() ){
      LL val = id * ti - (id * id - id) * di / 2 + dq.front().M * id + dq.front().C;
      dp[ i ] = max( dp[ i ] , val );
    }
  }
}
int dis , dw[ N ] , dt[ N ] , dd[ N ];
int con , ct[ N ] , cd[ N ];
double f( int ti , int di , double goal ){
  if( di == 0 ){
    if( ti < goal ) return 0;
    return w;
  }
  if( ti < goal ) return 0;
  return (ti - goal) / di;
}
double f2( int ti , int di , double& res , double goal ){
  if( di == 0 ){
    if( ti < goal ) return 0;
    double ret = ti * res;
    res = 0;
    return ret;
  }
  if( ti < goal ) return 0;
  double xxi = (ti - goal) / di;
  double ret = ((double)ti * ti - goal * goal) / (2. * di);
  res -= xxi;
  return ret;
}
#define K 60
int idc[ N ];
void solve(){
  double ans = -1e20;
  for( int wi = 0 ; wi <= w ; wi ++ ){
    if( dp[ wi ] == -inf ) continue;
    int goal = w - wi;
    double bl = -1e9 , br = 1e4;
    for( int _ = 0 ; _ < K ; _ ++ ){
      double bmid = (bl + br) * .5;
      double tot = 0;
      for( int i = 0 ; i < con and tot < goal - eps ; i ++ )
        tot += f( ct[ idc[ i ] ] , cd[ idc[ i ] ] , bmid );
      if( tot < goal - eps )
        br = bmid;
      else
        bl = bmid;
    }
    double sum = dp[ wi ] , res = goal;
    for( int i = 0 ; i < con and res > 0 ; i ++ )
      sum += f2( ct[ idc[ i ] ] , cd[ idc[ i ] ] , res , bl );
    ans = max( ans , sum );
  }
  printf( "%.12f\n" , ans );
  exit(0);
}
int main(){
  int d; scanf( "%d%d" , &d , &w );
  while( d -- ){
    char buf[ 8 ]; scanf( "%s" , buf );
    if( buf[ 0 ] == 'C' ){
      scanf( "%d%d" , &ct[ con ] , &cd[ con ] );
      con ++;
    }else{
      scanf( "%d%d%d" , &dw[ dis ] , &dt[ dis ] , &dd[ dis ] );
      dis ++;
    }
  }
  for( int i = 0 ; i < con ; i ++ )
    idc[ i ] = i;
  sort( idc , idc + con , [&](int id1 , int id2){ return cd[ id1 ] > cd[ id2 ]; } );
  for( int i = 1 ; i <= w ; i ++ )
    dp[ i ] = -inf;
  for( int i = 0 ; i < dis ; i ++ )
    upd( dw[ i ] , dt[ i ] , dd[ i ] );
  if( !con ){
    if( dp[ w ] == -inf ){
      puts( "impossible" );
      exit(0);
    }else{
      printf( "%lld\n" , dp[ w ] );
      exit(0);
    }
  }
  solve();
}
