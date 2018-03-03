#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n , e , ow , oh;
int x[ N ] , y[ N ] , w[ N ] , h[ N ];
int vr[ N ] , ho[ N ] , tp[ N ] , dn[ N ] , lf[ N ] , rg[ N ];
int lvr[ N ] , lho[ N ] , ltp[ N ] , ldn[ N ] , llf[ N ] , lrg[ N ];
vector<int> son[ N ];
void init(){
  w[ 0 ] = ow;
  h[ 0 ] = oh;
  for( int i = 0 ; i <= n ; i ++ )
    son[ i ].clear();
  for( int i = 1 ; i <= n ; i ++ ){
    cin >> x[ i ] >> y[ i ];
    cin >> w[ i ] >> h[ i ];
    cin >> ho[ i ] >> vr[ i ];
    cin >> tp[ i ] >> dn[ i ];
    cin >> lf[ i ] >> rg[ i ];
    if( !vr[ i ] and !tp[ i ] and !dn[ i ] )
      tp[ i ] = 1;
    if( !ho[ i ] and !lf[ i ] and !rg[ i ] )
      rg[ i ] = 1;
    //printf( "vr = %d, ho = %d , tp = %d , dn = %d , lf = %d , rg = %d\n" , 
            //vr[ i ] , ho[ i ] , tp[ i ] , dn[ i ] , lf[ i ] , rg[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    int pp = 0;
    LL sz = (LL)ow * oh;
    for( int j = 1 ; j <= n ; j ++ ){
      if( i == j ) continue;
      if( x[ j ] <= x[ i ] and x[ i ] + w[ i ] <= x[ j ] + w[ j ] and
          y[ j ] <= y[ i ] and y[ i ] + h[ i ] <= y[ j ] + h[ j ] ){
        LL csz = (LL)w[ j ] * h[ j ];
        if( csz < sz ){
          sz = csz;
          pp = j;
        }
      }
    }
    son[ pp ].push_back( i );
  }
}
void go( int now ){
  for( int s : son[ now ] ){
    // [x[ now ], x[ now ] + w[ now ]]
    // [y[ now ], y[ now ] + h[ now ]]
    int dx = x[ s ] - x[ now ];
    int dy = y[ s ] - y[ now ];
    
    lvr[ s ] = h[ s ];
    lho[ s ] = w[ s ];
    ltp[ s ] = dy;
    ldn[ s ] = h[ now ] - h[ s ] - dy;
    llf[ s ] = dx;
    lrg[ s ] = w[ now ] - w[ s ] - dx;

    go( s );
  }
}

int ax[ N ] , ay[ N ] , aw[ N ] , ah[ N ];

void cal( int len , int newlen , int l1 , int l2 , int l3 , 
                                 int s1 , int s2 , int s3 ,
                                 int& nl1 , int& nl2 , int& nl3 ){
  //printf( "%d -> %d\n" , len , newlen );
  int fix = 0;
  if( !s1 ) fix += l1 , nl1 = l1;
  if( !s2 ) fix += l2 , nl2 = l2;
  if( !s3 ) fix += l3 , nl3 = l3;
  len -= fix;
  len = max( len , 1 );
  newlen -= fix;
  if( s1 ) nl1 = ((LL)l1 * newlen) / len;
  if( s2 ) nl2 = ((LL)l2 * newlen) / len;
  if( s3 ) nl3 = ((LL)l3 * newlen) / len;

  //printf( "l1 = %d, l2 = %d, l3 = %d\n" , l1 , l2 , l3 );
  //printf( "s1 = %d, s2 = %d, s3 = %d\n" , s1 , s2 , s3 );
  //printf( "nl1 = %d, nl2 = %d, nl3 = %d\n" , nl1 , nl2 , nl3 );
}

void gogo( int now ){

  for( int s : son[ now ] ){
    
    // from w[ now ] -> aw[ now ]
    // from h[ now ] -> ah[ now ]

    int newlvr , newltp , newldn;
    cal( h[ now ] , ah[ now ] , lvr[ s ] , ltp[ s ] , ldn[ s ] ,
                                 vr[ s ] ,  tp[ s ] ,  dn[ s ] ,
                                 newlvr , newltp , newldn );
    int newlho , newllf , newlrg;
    cal( w[ now ] , aw[ now ] , lho[ s ] , llf[ s ] , lrg[ s ] ,
                                 ho[ s ] ,  lf[ s ] ,  rg[ s ] ,
                                 newlho , newllf , newlrg );
    ah[ s ] = newlvr;
    aw[ s ] = newlho;
    ax[ s ] = ax[ now ] + newllf;
    ay[ s ] = ay[ now ] + newltp;

    gogo( s );
  }

}


int _cs;

void solve(){
  go( 0 );


  int op = 0;
  ++ _cs;


  while( e -- ){
    scanf( "%d%d" , &aw[ 0 ] , &ah[ 0 ] );
    gogo( 0 );
  
    printf( "Case %d, resize operation %d:\n" , _cs , ++ op );
    for( int i = 1 ; i <= n ; i ++ ){
      printf( "    Window %d, x = %d, y = %d, width = %d, height = %d\n" , 
              i , ax[ i ] , ay[ i ] , aw[ i ] , ah[ i ] );
    }
  }
}
int main(){
  while( cin >> n >> e >> ow >> oh and n ){
    init();
    solve();
  }
}
