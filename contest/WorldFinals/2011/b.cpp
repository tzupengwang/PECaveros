#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
#define K 10
Pt p[ K ] , q[ 3 ];
vector< vector<Pt> > goal;
vector< pair<double,double> > rot;
void add( int x , int y ){
  double zz = sqrt( x * x + y * y );
  rot.push_back( { x / zz , y / zz } );
}
void normalized( vector<Pt>& pp ){
  for( int i = 1 ; i < 3 ; i ++ ){
    pp[ i ].X -= pp[ 0 ].X;
    pp[ i ].Y -= pp[ 0 ].Y;
  }
  pp[ 0 ].X = pp[ 0 ].Y = 0;
}
int solve(){
  set< vector<Pt> > lazi;
  for( auto rr : rot ){
    vector<Pt> pp;
    pp.resize( K );
    for( int i = 0 ; i < K ; i ++ ){
      pp[ i ].X = round( p[ i ].X * rr.first - p[ i ].Y * rr.second );
      pp[ i ].Y = round( p[ i ].X * rr.second + p[ i ].Y * rr.first );
    }
    normalized( pp );
    for( size_t lex = 0 ; lex < goal.size() ; lex ++ ){
      int x_factor = 1 , y_factor = 1;
      for( int i = 0 ; i < 3 ; i ++ ){
        if( pp[ i ].X ) x_factor = goal[ lex ][ i ].X / pp[ i ].X;
        if( pp[ i ].Y ) y_factor = goal[ lex ][ i ].Y / pp[ i ].Y;
      }
      for( int x_scale : {-1, +1, x_factor} ){
        if( !x_scale ) continue;
        for( int y_scale : {-1, +1, y_factor} ){
          if( !y_scale ) continue;
          vector<Pt> res;
          for( auto i : pp )
            res.push_back( { i.X * x_scale , i.Y * y_scale } );
          bool same = true;
          for( int i = 0 ; i < 3 and same ; i ++ )
            if( res[ i ] != goal[ lex ][ i ] )
              same = false;
          if( same ){
            lazi.insert( res );
            if( lazi.size() > 1u )
              return lazi.size();
          }
        }
      }
    }
  }
  return lazi.size();
}
int main(){
  for( int i = -10 ; i <= 10 ; i ++ ){
    add( -10 , i );
    add( +10 , i );
    add( i , -10 );
    add( i , +10 );
  }
  int _cs = 0;
  while( true ){
    bool ok = false;
    for( int i = 0 ; i < 3 ; i ++ ){
      cin >> p[ i ].X >> p[ i ].Y;
      if( p[ i ].X or p[ i ].Y ) ok = true;
    }
    for( int i = 3 ; i < K ; i ++ ){
      p[ i ].X = rand();
      p[ i ].Y = rand();
    }
    if( not ok ) break;
    for( int i = 0 ; i < 3 ; i ++ )
      cin >> q[ i ].X >> q[ i ].Y;
    int ord[ 3 ] = {0, 1, 2};
    goal.clear();
    do{
      vector<Pt> cur;
      for( int i = 0 ; i < 3 ; i ++ )
        cur.push_back( q[ ord[ i ] ] );
      normalized( cur );
      goal.push_back( cur );
    }while( next_permutation( ord , ord + 3 ) );
    sort( goal.begin() , goal.end() );
    goal.resize( unique( goal.begin() , goal.end() ) - goal.begin() );
    int ret = solve();
    printf( "Case %d: " , ++ _cs );
    if( ret == 0 ) puts( "no solution" );
    else if( ret == 1 ) puts( "equivalent solutions" );
    else puts( "inconsistent solutions" );
  }
}
