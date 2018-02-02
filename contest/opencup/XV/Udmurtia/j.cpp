#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define double long double
const double eps = 1e-10;
#define N 11
int n , dice[ N ][ 6 ];

#define BS 10

double ps[ 111 ];

double win( double* a , double* b ){
  for( int i = 0 ; i < 111 ; i ++ ) ps[ i ] = b[ i ];
  for( int i = 1 ; i < 111 ; i ++ ) ps[ i ] += ps[ i - 1 ];
  double ret = 0;
  for( int i = 0 ; i < 111 ; i ++ )
    ret += a[ i ] * ps[ i ];
  return ret;
}

double prob[ 1 << 10 ][ 111 ];
int bk[ 1 << 10 ];

bool no[ 10 ][ 111 ];

int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 6 ; j ++ )
      scanf( "%d" , &dice[ i ][ j ] );
  for( int i = 0 ; i < (1 << n) ; i ++ ){
    if( i == (i & (-i)) ){
      for( int j = 0 ; j < 6 ; j ++ )
        prob[ i ][ BS + dice[ __lg( i ) ][ j ] ] += 1. / 6;
      bk[ i ] = __lg( i );
    }else{
      int cand = i;
      bool gt = false;
      while( cand ){
        int pre = __lg( cand & (-cand) );
        
        double tmp[ 111 ] = {};
        for( int j = 0 ; j < 6 ; j ++ ){
          int cur = dice[ pre ][ j ] + BS;
          double better = 0;
          for( int cc = cur + 2 ; cc < 111 ; cc ++ )
            better += prob[ i ^ (1 << pre) ][ cc ];
          if( better > .5 - eps ){
            for( int cc = 1 ; cc < 111 ; cc ++ )
              tmp[ cc - 1 ] += prob[ i ^ (1 << pre) ][ cc ] / 6.;
          }else{
            tmp[ cur ] += 1. / 6;
          }
        }
        if( not gt or win( tmp , prob[ i ] ) > win( prob[ i ] , tmp ) ){
          for( int cc = 0 ; cc < 111 ; cc ++ )
            prob[ i ][ cc ] = tmp[ cc ];
          bk[ i ] = pre;
          gt = true;
        }

        cand ^= (1 << pre);
      }
    }

    //for( int j = 0 ; j < 111 ; j ++ )
      //if( prob[ i ][ j ] > eps )
        //printf( "%d %d : %.6f\n" , i , j - BS , prob[ i ][ j ] );

  }

  vector<int> ord;
  int now = (1 << n) - 1;
  while( now ){
    ord.push_back( bk[ now ] );
    now ^= (1 << bk[ now ]);
  }

  //for( auto i : ord )
    //cout << i << endl;

  int res = (1 << n) - 1;
  for( size_t _ = 0 ; _ + 1 < ord.size() ; _ ++ ){
    int i = ord[ _ ];
    res ^= (1 << i);
    

    for( int j = 0 ; j < 6 ; j ++ ){
      int val = dice[ i ][ j ];

      bool better = 0;
      for( int ii = val + BS + 2 ; ii < 111 ; ii ++ )
        better += prob[ res ][ ii ];
      if( better > .5 - eps ){
        no[ _ ][ val ] = true;
        //printf( "no %d %d\n" , _ , val );
      }
    }
  }

  for( int _round = 0 ; _round < 10000 ; _round ++ ){
    for( size_t _ = 0 ; _ < ord.size() ; _ ++ ){
      printf( "%d\n" , ord[ _ ] + 1 );
      fflush( stdout );
      int x; scanf( "%d" , &x );
      if( _ + 1 < ord.size() and no[ _ ][ x + _ ] ){
        puts( "No" );
        fflush( stdout );
        continue;
      }
      puts( "Yes" );
      fflush( stdout );
      break;
    }
    char win[ 64 ];
    scanf( "%s" , win );
  }
}
