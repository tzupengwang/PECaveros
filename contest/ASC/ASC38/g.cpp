#include <bits/stdc++.h>
using namespace std;
#define N 111
int h , w , k;
int r1[ N ] , r2[ N ];
int c1[ N ] , c2[ N ];
int mxh , mxw;
void init(){
  scanf( "%d%d%d" , &h , &w , &k );
  for( int i = 0 ; i < k ; i ++ ){
    scanf( "%d%d%d%d" , &r1[ i ] , &c1[ i ] , &r2[ i ] , &c2[ i ] );
    mxh = max( mxh , r2[ i ] );
    mxw = max( mxw , c2[ i ] );
  }
}
bool oc[ N ][ N ] , dn[ N ] , gg[ N ][ N ];
int px , py , who[ N ][ N ];
vector< string > prog;
void solve(){
  if( mxh + 1 < h || mxw + 1 < w ){
    puts( "Impossible" );
    exit( 0 );
  }
  prog.push_back( "Panel container = new Panel(new GridBagLayout());" );
  prog.push_back( "GridBagConstraints gbc = new GridBagConstraints();" );
  for( int now = 0 ; now < k ; now ++ )
    for( int i = r1[ now ] ; i <= r2[ now ] ; i ++ )
      for( int j = c1[ now ] ; j <= c2[ now ] ; j ++ ){
        if( gg[ i ][ j ] ){
          puts( "Impossible" );
          exit( 0 );
        }
        gg[ i ][ j ] = true;
        who[ i ][ j ] = now;
      }
  int ph = 1 , pw = 1;
  bool wtf = false , ya = false;
  for( int _ = 0 ; _ < k ; _ ++ ){
    int now = 0;
    bool got = false;
    for( int i = px ; i < h && !got ; i ++ )
      for( int j = ( i == px ? py : 0 ) ; j < w ; j ++ )
        if( !oc[ i ][ j ] && gg[ i ][ j ] ){
          got = true;
          now = who[ i ][ j ];
          break;
        }
    if( !got ){
      puts( "Impossible" );
      exit( 0 );
    }
    got = false;
    for( int i = px ; i < h && !got ; i ++ )
      for( int j = ( i == px ? py : 0 ) ; j < w ; j ++ )
        if( !oc[ i ][ j ] ){
          got = true;
          px = i; py = j;
          break;
        }
    if( !got || px != r1[ now ] || py != c1[ now ] ){
      puts( "Impossible" );
      exit( 0 );
    }
    for( int i = r1[ now ] ; i <= r2[ now ] ; i ++ )
      for( int j = c1[ now ] ; j <= c2[ now ] ; j ++ ){
        if( oc[ i ][ j ] ){
          puts( "Impossible" );
          exit( 0 );
        }
        oc[ i ][ j ] = true;
      }
    if( c1[ now ] == w - 1 && c2[ now ] == w - 1 )
      wtf = true;
    int nh = r2[ now ] - r1[ now ] + 1;
    int nw = c2[ now ] - c1[ now ] + 1;
    if( _ + 1 == k ){
      if( c2[ now ] == w - 1 )
        ya = true;
    }
    if( c2[ now ] == w - 1 && _ + 1 < k ){
      prog.push_back( "gbc.gridwidth = GridBagConstraints.REMAINDER;" );
      pw = -1;
    }else if( nw != pw ){
      string cmd = "gbc.gridwidth = " + to_string( nw ) + ";";
      prog.push_back( cmd );
      pw = nw;
    }
    {
      string cmd = "gbc.gridheight = " + to_string( nh ) + ";";
      prog.push_back( cmd );
      ph = nh;
    }
    prog.push_back( "container.add(new Component(), gbc);" );
    px = r1[ now ];
    py = c2[ now ] + 1;
  }
  if( !ya && !wtf ){
    puts( "Impossible" );
    exit( 0 );
  }
  for( auto cmd : prog )
    cout << cmd << endl;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "gridbaglayout.in" , "r" , stdin );
  freopen( "gridbaglayout.out" , "w" , stdout );
#endif
  init();
  solve();
}
