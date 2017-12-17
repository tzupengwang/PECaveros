#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<char> v;
string ss;
int mp[ 256 ] , len;
inline LL hsh( const vector<int>& vv ){
  LL ret = 0;
  for( auto i : vv )
    ret = (ret << 2) | (i + 1);
  return ret;
}
unordered_map< LL , int > cnt;
void check(){
  vector<int> ord;
  for( int i = 0 ; i < 10 ; i ++ )
    ord.push_back( i );
  do{
    for( int i = 0 ; i < 10 ; i ++ )
      mp[ (int)v[ i ] ] = ord[ i ];
    LL sgn = 0;
    for( int i = 1 ; i < len ; i ++ ){
      if( mp[ (int)ss[ i - 1 ] ] < mp[ (int)ss[ i ] ] )
        sgn = (sgn << 2);
        //sgn.push_back( -1 );
      else if( mp[ (int)ss[ i - 1 ] ] > mp[ (int)ss[ i ] ] )
        sgn = (sgn << 2) | 2;
        //sgn.push_back( +1 );
      else
        sgn = (sgn << 2) | 1;
        //sgn.push_back( 0 );
    }
    //cnt[ hsh( sgn ) ] ++;
    cnt[ sgn ] ++;
  }while( next_permutation( ord.begin() , ord.end() ) );
  for( auto i : cnt ){
    if( i.second > 1 ) continue;
    LL cur = i.first;
    vector<int> vv;
    for( int j = 0 ; j < len - 1 ; j ++ ){
      vv.push_back( cur & 3 );
      cur >>= 2;
    }
    reverse( vv.begin() , vv.end() );
    putchar( ss[ 0 ] );
    for( int j = 1 ; j < len ; j ++ )
      printf( " %c %c" , "<=>"[ vv[ j - 1 ] ] , ss[ j ] );
    puts( "" );
    exit(0);
  }
}
int main(){
  cin >> ss;
  len = ss.length();
  for( size_t i = 0 ; i < ss.length() ; i ++ )
    v.push_back( ss[ i ] );
  sort( v.begin() , v.end() );
  v.resize( unique( v.begin() , v.end() ) - v.begin() );
  if( v.size() == 10u )
    check();
  puts( "Impossible" );
  //freopen( "words.unix.txt" , "r" , stdin );
  //freopen( "useful.txt" , "w" , stdout );
  //string ss;
  //int len = 0;
  //while( cin >> ss ){
    //set<char> S;
    //for( char cc : ss )
      //S.insert( cc );
    //if( S.size() != 10u ) continue;
    //len = max( len , (int)ss.length() );
    //cout << ss << endl;
  //}
  //cerr << len << endl;

}
