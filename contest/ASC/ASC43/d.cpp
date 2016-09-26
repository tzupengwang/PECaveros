#include <bits/stdc++.h>
using namespace std;
#define N 11
int h;
// vector< pair< pair<int,int> , string > > vv;
string now;
char cc[]=".SGR";
int cost[] = { 0 , 5 , 3 , 10 };
int tag[ N ] , wt[ N ] , s[ N ] , hp[ N ];
pair< int , int > find_ans( int msk ){
  now = "";
  int ncst = 0;
  for( int i = 0 ; i < 10 ; i ++ ){
    tag[ i ] = 0;
    now += cc[ msk & 3 ];
    ncst += cost[ msk & 3 ];
    msk >>= 2;
    s[ i ] = 0;
    for( int j = i ; j >= 0 && j >= i - 4 ; j -- )
      if( now[ j ] == 'S' )
        s[ i ] ++;
  }
  int alive = 0 , kill = 0;
  for( int _ = 0 ; _ < 10 || alive > 0 ; _ ++ ){
    for( int i = 9 ; i >= 0 ; i -- ){
      msk = tag[ i ];
      while( msk ){
        int x = __lg( msk & (-msk) );
        wt[ x ] --;
        if( wt[ x ] == 0 ){
          tag[ i ] ^= ( 1 << x );
          tag[ i + 1 ] ^= ( 1 << x );
          wt[ x ] = s[ i + 1 ] + 1;
          if( i == 9 ) alive --;
        }
        msk ^= ( 1 << x );
      }
    }
    if( _ < 10 ){
      tag[ 0 ] ^= ( 1 << _ );
      wt[ _ ] = s[ 0 ] + 1;
      hp[ _ ] = h;
      alive ++;
    }
    for( int i = 9 ; i >= 0 ; i -- ){
      if( now[ i ] == 'S' || now[ i ] == '.' ) continue;
      if( now[ i ] == 'R' && _ % 3 != 2 ) continue;
      int dlt = ( now[ i ] == 'G' ? 1 : 4 );
      msk = tag[ i ];
      while( msk ){
        int x = __lg( msk & (-msk) );
        hp[ x ] -= dlt;
        if( hp[ x ] <= 0 ){
          tag[ i ] ^= ( 1 << x );
          kill ++;
          alive --;
        }
        msk ^= ( 1 << x );
        if( dlt == 1 ) break;
      }
    }
  }
  return { ncst , kill };
}
bool cmp( pair< pair<int,int> , string > p1 ,
          pair< pair<int,int> , string > p2 ){
  if( p1.first.first != p2.first.first )
    return p1.first.first < p2.first.first;
  if( p1.first.second != p2.first.second )
    return p1.first.second > p2.first.second;
  return p1.second < p2.second;
}
bool cmp2( pair<int,int> p1 , pair<int,int> p2 ){
  if( p1.first != p2.first )
    return p1.first < p2.first;
  return p1.second > p2.second;
}
int bst[ N ];
string ss[ N ];
int main(){
  for( h = 1 ; h <= 30 ; h ++ ){
    for( int i = 1 ; i <= 10 ; i ++ ){
      bst[ i ] = 1048577;
      ss[ i ] = "";
    }
    vector< pair<int,int> > vv;
    for( int i = 0 ; i < ( 1 << 20 ) ; i ++ ){
      pair<int,int> tp = find_ans( i );
      // vv.push_back( { find_ans( i ) , now } );
      if( tp.first < bst[ tp.second ] ||
          ( tp.first == bst[ tp.second ] &&
            now < ss[ tp.second ] ) ){
        bst[ tp.second ] = tp.first;
        ss[ tp.second ] = now;
      }
    }
    // sort( vv.begin() , vv.end() , cmp );
    for( int i = 1 ; i <= 10 ; i ++ ){
      if( bst[ i ] == 1048577 ) continue;
      vv.push_back( { bst[ i ] , i } );
    }
    sort( vv.begin() , vv.end() , cmp2 );
    int pre = 0;
    for( auto i : vv )
      if( i.second > pre ){
        stringstream sss;
        sss << "$" << i.first << " -> kill " << i.second << " with " << ss[ i.second ];
        string iss;
        getline( sss , iss );
        printf( "v[%d].push_back(\"%s\");\n" , h , iss.c_str() );
        // cout << iss << endl;
        // printf( "$%d -> kill %d with %s\n" , i.first , i.second ,
                                             // ss[ i.second ].c_str() );
        pre = i.second;
      }
    cerr << h << " done." << endl;
  }

  // int pre = 0;
  // for( auto i : vv )
    // if( i.first.second > pre ){
      // printf( "$%d -> kill %d with %s\n" , i.first.first , i.first.second ,
                                           // i.second.c_str() );
      // pre = i.first.second;
    // }
}
