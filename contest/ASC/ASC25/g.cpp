#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int a , b , c;
#define N 6
bool vst[ N ][ N ][ N ];
int deg[ N ][ N ][ N ];
#define K 222
int cnt[ K ];
int nx[ K ] , ny[ K ] , nz[ K ];
vector< tuple<int,int,int> > cand[ N ][ N ][ N ];
inline bool in( int na , int nb , int nc ){
  return 1 <= na && na <= a &&
         1 <= nb && nb <= b &&
         1 <= nc && nc <= c;
}
void output(){
  int oo[ 3 ] = { a , b , c };
  int per[ 3 ] = { 0 , 1 , 2 };
  do{
    printf( "okay[%d][%d][%d] = true;\n" , oo[ per[ 0 ] ] , oo[ per[ 1 ] ] , oo[ per[ 2 ] ] );
    printf( "ans[%d][%d][%d]={" , oo[ per[ 0 ] ] , oo[ per[ 1 ] ] , oo[ per[ 2 ] ] );
    for( int i = 0 ; i < a * b * c ; i ++ ){
      int xx[3] = { nx[ i ] , ny[ i ] , nz[ i ] };
      //printf( "{%d,{%d,%d}}" , nx[ i ] , ny[ i ] , nz[ i ] );
      printf( "{%d,{%d,%d}}" , xx[ per[ 0 ] ] , xx[ per[ 1 ] ] , xx[ per[ 2 ] ] );
      if( i + 1 != a * b * c ) printf( "," );
    }
    printf( "};\n" );
  }while( next_permutation( per , per + 3 ) );
  exit( 0 );
}
void go( int na , int nb , int nc , int now ){
  nx[ now ] = na;
  ny[ now ] = nb;
  nz[ now ] = nc;
  if( now + 1 == a * b * c )
    output();
  if( cnt[ 0 ] > 0 || ( cnt[ 1 ] - ( deg[ na ][ nb ][ nc ] == 1 ) ) > 1 )
    return;
  vst[ na ][ nb ][ nc ] = true;
  cnt[ deg[ na ][ nb ][ nc ] ] --;
  for( auto tp : cand[ na ][ nb ][ nc ] ){
    int xa = get<0>( tp );
    int xb = get<1>( tp );
    int xc = get<2>( tp );
    if( vst[ xa ][ xb ][ xc ] ) continue;
    cnt[ deg[ xa ][ xb ][ xc ] ] --;
    deg[ xa ][ xb ][ xc ] --;
    cnt[ deg[ xa ][ xb ][ xc ] ] ++;
  }
  for( auto tp : cand[ na ][ nb ][ nc ] ){
    int xa = get<0>( tp );
    int xb = get<1>( tp );
    int xc = get<2>( tp );
    if( vst[ xa ][ xb ][ xc ] ) continue;
    go( get<0>( tp ) , get<1>( tp ) , get<2>( tp ) , now + 1 );
  }
  for( auto tp : cand[ na ][ nb ][ nc ] ){
    int xa = get<0>( tp );
    int xb = get<1>( tp );
    int xc = get<2>( tp );
    if( vst[ xa ][ xb ][ xc ] ) continue;
    cnt[ deg[ xa ][ xb ][ xc ] ] --;
    deg[ xa ][ xb ][ xc ] ++;
    cnt[ deg[ xa ][ xb ][ xc ] ] ++;
  }
  cnt[ deg[ na ][ nb ][ nc ] ] ++;
  vst[ na ][ nb ][ nc ] = false;
}
int main(){
  scanf( "%d%d%d" , &a , &b , &c );
  for( int na = 1 ; na <= a ; na ++ )
    for( int nb = 1 ; nb <= b ; nb ++ )
      for( int nc = 1 ; nc <= c ; nc ++ ){
        vector< int > dlt = { 0 , 1 , 2 };
        do{
          for( int i = -1 ; i <= 1 ; i += 2 ){
            if( dlt[ 0 ] == 0 && i == 1 ) break;
            for( int j = -1 ; j <= 1 ; j += 2 ){
              if( dlt[ 1 ] == 0 && j == 1 ) break;
              for( int k = -1 ; k <= 1 ; k += 2 ){
                if( dlt[ 2 ] == 0 && k == 1 ) break;
                int nxta = na + dlt[ 0 ] * i;
                int nxtb = nb + dlt[ 1 ] * j;
                int nxtc = nc + dlt[ 2 ] * k;
                if( in( nxta , nxtb , nxtc ) ){
                  deg[ na ][ nb ][ nc ] ++;
                  cand[ na ][ nb ][ nc ].push_back( make_tuple( nxta , nxtb , nxtc ) );
                }
              }
            }
          }
        }while( next_permutation( dlt.begin() , dlt.end() ) ); 
        cnt[ deg[ na ][ nb ][ nc ] ] ++;
        random_shuffle( cand[ na ][ nb ][ nc ].begin(),
                        cand[ na ][ nb ][ nc ].end() );
      }
  go( 1 , 1 , 1 , 0 );
}
