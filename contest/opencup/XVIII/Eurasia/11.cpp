#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 65536
int n , m;
LL f[ N ] , e[ N ];
vector<int> v[ N ];
#define MAGIC 21
#define FUCK 24
char dp[ 1 << FUCK ];
int fm[ 1 << FUCK ];
bool gt[ 1 << FUCK ];
int id[ N ] , who[ N ] , ff;
LL af[ 1 << FUCK ] , ae[ 1 << FUCK ];
int DP( int msk ){
  if( msk == 0 ) return 0;
  if( gt[ msk ] ) return dp[ msk ];
  int bst = 0 , fr = 0;
  for( int i = 0 ; i < ff ; i ++ )
    if( (msk >> i) & 1 ){
      int tdp = DP( msk ^ (1 << i) );
      LL pre = af[ msk ^ (1 << i) ] | ae[ msk ^ (1 << i) ];
      int mr = 0;
      if( ( f[ 1 ] >> who[ i ]) & 1LL )
        mr = __builtin_popcountll( f[ who[ i ] ] & (~pre) );
      else
        mr = __builtin_popcountll( e[ who[ i ] ] & (~pre) );
      if( tdp + mr > bst ){
        bst = tdp + mr;
        fr = msk ^ (1 << i);
      }
    }
  gt[ msk ] = true;
  fm[ msk ] = fr;
  return dp[ msk ] = bst;
}
void go( int msk , int gg ){
  if( !msk ) return;
  go( fm[ msk ] , 0 );
  int bt = __lg( msk ^ fm[ msk ] );
  printf( "%d%c" , who[ bt ] , " \n"[ gg ] );
}
void solve1(){
  LL tmp = f[ 1 ] | e[ 1 ];
  for( int i = 2 , ptr = 0 ; i <= n ; i ++ )
    if( (tmp >> i) & 1LL ){
      who[ ptr ] = i;
      id[ i ] = ptr ++;
    }
  tmp |= 2;
  int of = __builtin_popcountll( f[ 1 ] );
  for( int i = 2 ; i <= n ; i ++ ){
    f[ i ] &= ~tmp;
    e[ i ] &= ~tmp;
  }
  for( int i = 1 ; i < (1 << ff) ; i ++ ){
    int bt = __lg( i );
    af[ i ] = af[ i ^ (1 << bt) ] | ( f[ who[ bt ] ] );
    ae[ i ] = ae[ i ^ (1 << bt) ] | ( e[ who[ bt ] ] );
  }
  int bst = DP( (1 << ff) - 1 ) + of;
  printf( "%.12f\n" , (double)bst / ( n - 1 ) );
  go( (1 << ff) - 1 , 1 );
}
int que[ N ] , qt;
int wt[ N ] , wtp;
int ind[ N ];
LL ggg[ N ];
map<LL,int> lg;
bool veryok[ 1 << FUCK ];
void okk( int tmsk , int ptr ){
  LL msk = 0;
  for( int i = 0 ; i < ptr ; i ++ )
    if( (tmsk >> i) & 1 )
      msk |= (1LL << who[ i ]);
  for( int i = 0 ; i < wtp ; i ++ )
    que[ i ] = wt[ i ];
  qt = wtp;
  vector<int> ans;
  while( msk ){
    bool good = false;
    for( int i = 0 ; i < qt and msk ; i ++ ){
      if( (f[1] >> que[ i ]) & 1LL ){
        if( msk & e[ que[ i ] ] )
          continue;
        msk &= (~f[ que[ i ] ]);
        ans.push_back( que[ i ] );
        swap( que[ i ] , que[ qt - 1 ] );
        qt --;
        good = true;
      }else{
        if( msk & f[ que[ i ] ] )
          continue;
        msk &= (~e[ que[ i ] ]);
        ans.push_back( que[ i ] );
        swap( que[ i ] , que[ qt - 1 ] );
        qt --;
        good = true;
      }
    }
    assert( good );
  }
  for( int i = 0 ; i < qt ; i ++ )
    ans.push_back( que[ i ] );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int tmpf[ N ] , tmpe[ N ];
void solve2(){
  LL other = 0;
  LL tmp = f[ 1 ] | e[ 1 ];
  int of = __builtin_popcountll( f[ 1 ] );
  wtp = 0;
  for( int i = 2 ; i <= n ; i ++ )
    if( (tmp >> i) & 1LL ){
      wt[ wtp ++ ] = i;
      other |= (f[ i ] & (~(tmp | 2)));
      other |= (e[ i ] & (~(tmp | 2)));
    }
  int ptr = 0;
  for( int i = 2 ; i <= n ; i ++ )
    if( (other >> i) & 1LL ){
      who[ ptr ] = i;
      id[ i ] = ptr ++;
    }
  for( int i = 2 ; i <= n ; i ++ )
    for( int j = 0 ; j < ptr ; j ++ ){
      if( (f[ i ] >> who[j]) & 1LL )
        tmpf[ i ] |= (1 << j);
      if( (e[ i ] >> who[j]) & 1LL )
        tmpe[ i ] |= (1 << j);
    }
  int bst = 0 , bstmsk = 0;
  veryok[ 0 ] = true;
  for( int i = 1 ; i < (1 << ptr) ; i ++ ){
    int msk = i;
    for( int j = 0 ; j < wtp ; j ++ ){
      //cout << i << " " << wt[ j ] << endl;
      if( (f[1] >> wt[ j ]) & 1LL ){
        if( msk & tmpe[ wt[ j ] ] )
          continue;
        if( veryok[ msk & (~tmpf[ wt[ j ] ]) ] ){
          veryok[ i ] = true;
          break;
        }
      }else{
        if( msk & tmpf[ wt[ j ] ] )
          continue;
        //cout << wt[ j ] << endl;
        if( veryok[ msk & (~tmpe[ wt[ j ] ]) ] ){
          veryok[ i ] = true;
          break;
        }
      }
    }
    if( veryok[ i ] and 
        __builtin_popcount( i ) > bst ){
      bst = __builtin_popcount( i );
      bstmsk = i;
    }
  }
  bst += of;
  printf( "%.12f\n" , (double)bst / ( n - 1 ) );
  okk( bstmsk , ptr );
}
int main(){
  for( int i = 1 ; i <= 50 ; i ++ )
    lg[ 1LL << i ] = i;
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int ui , vi , ei;
    scanf( "%d%d%d" , &ui , &vi , &ei );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
    if( ei == 0 ){
      f[ ui ] |= (1LL << vi);
      f[ vi ] |= (1LL << ui);
    }else{
      e[ ui ] |= (1LL << vi);
      e[ vi ] |= (1LL << ui);
    }
  }
  ff = __builtin_popcountll( f[ 1 ] | e[ 1 ] );
  bool wtf = (f[1] | e[1]) == 0LL;
  if( ff <= MAGIC )
    solve1();
  else
    solve2();
  if( wtf ) puts( "" );
}
