#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 2020
#define X first
#define Y second
int n , k;
pair<int,int> v[ N ] , v2[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d%d" , &v[ i ].X , &v[ i ].Y );
  sort( v , v + n );
}

int solve1(){
  int mxy = v[ 0 ].Y , mny = v[ 0 ].Y;
  for( int i = 0 ; i < n ; i ++ ){
    mxy = max( mxy , v[ i ].Y );
    mny = min( mny , v[ i ].Y );
  }
  return max( mxy - mny , v[ n - 1 ].X - v[ 0 ].X );
}

bool lgt[ N ] , rgt[ N ];
int lmxx[ N ] , lmnx[ N ] , lmxy[ N ] , lmny[ N ];
int rmxx[ N ] , rmnx[ N ] , rmxy[ N ] , rmny[ N ];

void upd( bool& gt , int& tmxx , int& tmnx , int& tmxy , int& tmny , pair<int,int> vv ){
  if( not gt ){
    gt = true;
    tmxx = tmnx = vv.X;
    tmxy = tmny = vv.Y;
    return;
  }
  tmxx = max( tmxx , vv.X );
  tmnx = min( tmnx , vv.X );
  tmxy = max( tmxy , vv.Y );
  tmny = min( tmny , vv.Y );
}

bool okay2( int r , int yi , int tn ){
  if( tn == 0 ) return true;
  // O(tn)
  {
    int tmxx , tmnx;
    int tmxy , tmny;
    bool gt = false;
    for( int i = 0 ; i < tn ; i ++ ){
      if( v[ i ].Y >= v[ yi ].Y - r )
        upd( gt , tmxx , tmnx ,
                  tmxy , tmny , v[ i ] );
      lgt[ i ] = gt;
      lmxx[ i ] = tmxx;
      lmnx[ i ] = tmnx;
      lmxy[ i ] = tmxy;
      lmny[ i ] = tmny;
    }
  }
  {
    int tmxx , tmnx;
    int tmxy , tmny;
    bool gt = false;
    for( int i = tn - 1 ; i >= 0 ; i -- ){
      if( v[ i ].Y >= v[ yi ].Y - r )
        upd( gt , tmxx , tmnx ,
                  tmxy , tmny , v[ i ] );
      rgt[ i ] = gt;
      rmxx[ i ] = tmxx;
      rmnx[ i ] = tmnx;
      rmxy[ i ] = tmxy;
      rmny[ i ] = tmny;
    }
  }

  int omxx , omnx;
  int omxy , omny;
  bool ogt = false;
  {
    for( int i = 0 ; i < tn ; i ++ )
      if( v[ i ].Y < v[ yi ].Y - r )
        upd( ogt , omxx , omnx ,
                    omxy , omny , v[ i ] );
  }
  for( int i = 0 , rb = 0 ; i < tn ; i ++ ){
    if( v[ i ].X > v[ yi ].X ) break;
    if( v[ i ].X < v[ yi ].X - r ) continue;

    rb = max( i , rb );
    while( rb < tn and v[ rb ].X <= v[ i ].X + r ) rb ++;

    bool gt = false;
    int tmxx , tmnx , tmxy , tmny;

    if( i and lgt[ i - 1 ] ){
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { lmnx[ i - 1 ] , lmny[ i - 1 ] } );
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { lmxx[ i - 1 ] , lmxy[ i - 1 ] } );
    }
    if( rb < tn and rgt[ rb ] ){
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { rmnx[ rb ] , rmny[ rb ] } );
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { rmxx[ rb ] , rmxy[ rb ] } );
    }
    if( ogt ){
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { omnx , omny } );
      upd( gt , tmxx , tmnx ,
                tmxy , tmny , { omxx , omxy } );
    }
    if( not gt ) return true;

    if( max( tmxx - tmnx , 
             tmxy - tmny ) <= r )
      return true;
  }

  return false;
}

bool okay3( int r , int yi ){
  for( int i = 0 ; i < n ; i ++ ){
    if( v2[ i ].X > v2[ yi ].X ) break;
    if( v2[ i ].X < v2[ yi ].X - r ) continue;

    int tn = 0 , tyi = 0;
    for( int j = 0 ; j < n ; j ++ )
      if( v2[ j ].Y < v2[ yi ].Y - r or
          v2[ j ].X < v2[ i ].X or
          v2[ j ].X > v2[ i ].X + r ){
        v[ tn ++ ] = v2[ j ];
        if( v2[ j ].Y > v[ tyi ].Y )
          tyi = tn - 1;
      }
    if( okay2( r , tyi , tn ) )
      return true;
  }
  return false;
}

int solve3(){
  for( int i = 0 ; i < n ; i ++ )
    v2[ i ] = v[ i ];
  int yi = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( v2[ i ].Y > v2[ yi ].Y )
      yi = i;

  int bl = 0 , br = 40000 , ba = br;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    
    if( okay3( bmid , yi ) )
      ba = bmid , br = bmid - 1;
    else
      bl = bmid + 1;
  }

  return ba;
}

int solve2(){
  int yi = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( v[ i ].Y > v[ yi ].Y )
      yi = i;
  int bl = 0 , br = 40000 , ba = br;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( okay2( bmid , yi , n ) )
      ba = bmid , br = bmid - 1;
    else
      bl = bmid + 1;
  }
  return ba;
}

void solve(){
  int ans = solve1();
  if( k >= 2 ) ans = min( ans , solve2() );
  if( k >= 3 ) ans = min( ans , solve3() );
  printf( "%d\n" , ans );
}
int main(){
  init();
  solve();
}
