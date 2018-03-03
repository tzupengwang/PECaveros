#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 33
int n , g , b , ind[ N ];
pair<int,int> v[ N ];
vector< int > nxt[ N ];
int parse(){
  char buf[ 256 ];
  scanf( "%s" , buf );
  int ret;
  if( sscanf( buf , "i%d" , &ret ) == 1 )
    return ret;
  if( sscanf( buf , "g%d" , &ret ) == 1 )
    return n + ret;
  assert( false );
  return -1;
}
int And( int ai , int bi ){
  if( ai and bi ) return 1;
  return 0;
}
int Or( int ai , int bi ){
  if( ai or bi ) return 1;
  return 0;
}
int Xor( int ai , int bi ){
  return (ai + bi) & 1;
}
int Not( int ai ){
  return 1 - ai;
}
int from[ N ] , gate[ N ];
#define AND 0
#define OR 1
#define XOR 2
#define NOT 3
vector<int> inp[ N ];
vector<int> oup[ N ];
vector<int> topo;
int ft = -1 , fg = -1 , _cs;
void solve(){
  printf( "Case %d: " , ++ _cs );


  ft = fg = -1;

  for( int i = n ; i <= n + g ; i ++ )
    for( int fail_type = 0 ; fail_type < 3 ; fail_type ++ ){
      if( i == n and fail_type ) continue;
      for( int j = n + 1 ; j <= n + g ; j ++ )
        inp[ j ].clear();

      for( int now : topo ){
        if( now <= n ) continue;
        
        if( now != i ){         
          if( gate[ now ] == AND ){
            for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
              inp[ now ].push_back( And( inp[ v[ now ].first  ][ j ],
                                         inp[ v[ now ].second ][ j ] ) );
          }else if( gate[ now ] == OR ){
            for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
              inp[ now ].push_back( Or( inp[ v[ now ].first  ][ j ],
                                        inp[ v[ now ].second ][ j ] ) );
          }else if( gate[ now ] == XOR ){
            for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
              inp[ now ].push_back( Xor( inp[ v[ now ].first  ][ j ],
                                         inp[ v[ now ].second ][ j ] ) );
          }else{
            for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
              inp[ now ].push_back( Not( inp[ v[ now ].first  ][ j ] ) );
          }
        }else{
          if( fail_type == 2 ){
            if( gate[ now ] == AND ){
              for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
                inp[ now ].push_back( 1 - And( inp[ v[ now ].first  ][ j ],
                                           inp[ v[ now ].second ][ j ] ) );
            }else if( gate[ now ] == OR ){
              for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
                inp[ now ].push_back( 1 - Or( inp[ v[ now ].first  ][ j ],
                                          inp[ v[ now ].second ][ j ] ) );
            }else if( gate[ now ] == XOR ){
              for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
                inp[ now ].push_back( 1 - Xor( inp[ v[ now ].first  ][ j ],
                                           inp[ v[ now ].second ][ j ] ) );
            }else{
              for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
                inp[ now ].push_back( 1 - Not( inp[ v[ now ].first  ][ j ] ) );
            }
          }else{
            for( size_t j = 0 ; j < inp[ v[ now ].first ].size() ; j ++ )
              inp[ now ].push_back( fail_type );
          }
        }
      }

      bool ok = true;

      for( int j = 1 ; j <= b and ok ; j ++ )
        if( oup[ j ] != inp[ from[ j ] ] )
          ok = false;

      if( not ok ) continue;

      if( i == n ){
        puts( "No faults detected" );
        return;
      }

      if( ft != -1 ){
        puts( "Unable to totally classify the failure" );
        return;
      }
      ft = fail_type;
      fg = i - n;
    }
  if( ft == -1 )
    puts( "Unable to totally classify the failure" );
    //puts( "No faults detected" );
  else{
    printf( "Gate %d is failing; " , fg );
    if( ft == 0 )
      puts( "output stuck at 0" );
    else if( ft == 1 )
      puts( "output stuck at 1" );
    else
      puts( "output inverted" );
  }
}
int main(){
  while( scanf( "%d%d%d" , &n , &g , &b ) == 3 and n ){
    for( int i = 1 ; i <= n ; i ++ )
      inp[ i ].clear();
    for( int i = 1 ; i <= b ; i ++ )
      oup[ i ].clear();
    for( int i = 0 ; i <= n + g ; i ++ ){
      nxt[ i ].clear();
      ind[ i ] = 0;
    }
    for( int i = n + 1 ; i <= n + g ; i ++ ){
      char type[ N ];
      scanf( "%s" , type );
      int in1 = -1 , in2 = -1;
      in1 = parse();
      if( type[ 0 ] != 'n' )
        in2 = parse();
      v[ i ] = {in1, in2};
      nxt[ in1 ].push_back( i );
      ind[ i ] = 1;
      if( in2 != -1 ){
        nxt[ in2 ].push_back( i );
        ind[ i ] ++;
      }
      if( type[ 0 ] == 'a' )
        gate[ i ] = AND;
      if( type[ 0 ] == 'n' )
        gate[ i ] = NOT;
      if( type[ 0 ] == 'o' )
        gate[ i ] = OR;
      if( type[ 0 ] == 'x' )
        gate[ i ] = XOR;
    }
    for( int i = 1 ; i <= b ; i ++ ){
      scanf( "%d" , &from[ i ] );
      from[ i ] += n;
    }
    int test; scanf( "%d" , &test ); while( test -- ){
      for( int i = 1 , x ; i <= n ; i ++ ){
        scanf( "%d" , &x );
        inp[ i ].push_back( x );
      }
      for( int i = 1 , x ; i <= b ; i ++ ){
        scanf( "%d" , &x );
        oup[ i ].push_back( x );
      }
    }
    topo.clear();
    for( int i = 1 ; i <= n + g ; i ++ )
      if( !ind[ i ] )
        topo.push_back( i );
    for( size_t _ = 0 ; _ < topo.size() ; _ ++ ){
      int i = topo[ _ ];
      for( int j : nxt[ i ] ){
        ind[ j ] --;
        if( ind[ j ] == 0 )
          topo.push_back( j );
      }
    }
    solve();
  }
}
