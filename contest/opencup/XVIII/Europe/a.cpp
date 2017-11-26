#include <bits/stdc++.h>
using namespace std;
#define N 514
char c[ N ][ N ];
int r , n , len;
bool ab( int row ){
  for( int i = 0 ; i < len ; i ++ ){
    if( i == 3 ) continue;
    if( i == 7 ) continue;
    if( c[ row ][ i ] == '-' )
      return true;
  }
  return false;
}
int ava( int row ){
  int ret = 0;
  for( int i = 0 ; i < len ; i ++ ){
    if( i == 3 ) continue;
    if( i == 7 ) continue;
    if( c[ row ][ i ] == '-' )
      ret ++;
  }
  return ret;
}
int dist( int a , int b ){
  return abs( a - b );
}
int clos( int a ){
  return min( dist( a , 0 ) ,
              min( dist( a , r / 2 + 1 ) ,
                   dist( a , r + 2 ) ) );
}
int which_row(){
  int fst = 1 , snd = r / 2 + 2;
  if( ab( fst ) and not ab( snd ) ) return fst;
  if( ab( snd ) and not ab( fst ) ) return snd;
  if( ab( fst ) and ab( snd ) ){
    if( ava( fst ) > ava( snd ) ) return fst;
    if( ava( snd ) > ava( fst ) ) return snd;
    return fst;
  }
  vector<int> cand;
  int bst = -1;
  for( int i = 1 ; i <= r / 2 ; i ++ ){
    int tmp = ava( i );
    if( tmp > bst ){
      cand.clear();
      bst = tmp;
      cand.push_back( i );
    }else if( tmp == bst )
      cand.push_back( i );
  }
  for( int i = r / 2 + 2 ; i < r + 2 ; i ++ ){
    int tmp = ava( i );
    if( tmp > bst ){
      cand.clear();
      bst = tmp;
      cand.push_back( i );
    }else if( tmp == bst )
      cand.push_back( i );
  }
  if( cand.size() == 1u ) return cand[ 0 ];
  vector<int> cand2;
  bst = 1000;
  for( int i : cand ){
    int dd = clos( i );
    if( dd < bst ){
      cand2.clear();
      bst = dd;
      cand2.push_back( i );
    }
  }
  return cand2[ 0 ];
}
int left_c( int row ){
  int ret = 0;
  for( int i = 0 ; i < r + 3 ; i ++ )
    for( int j = 0 ; j < 5 ; j ++ )
      if( c[ i ][ j ] == '#' or
          ( c[ i ][ j ] >= 'a' and
            c[ i ][ j ] <= 'z' ) )
        ret ++;
  return ret;
}
int right_c( int row ){
  int ret = 0;
  for( int i = 0 ; i < r + 3 ; i ++ )
    for( int j = 6 ; j < 11 ; j ++ )
      if( c[ i ][ j ] == '#' or
          ( c[ i ][ j ] >= 'a' and
            c[ i ][ j ] <= 'z' ) )
        ret ++;
  return ret;
}
map<char,int> at;
pair<int,int> go( int now ){
  int rn = which_row();
  //cerr << now << " " << rn << endl;
  int lft = left_c( rn ) , rgt = right_c( rn );
  if( c[ rn ][ at[ 'D' ] ] == '-' or c[ rn ][ at[ 'F' ] ] == '-' ){
    if( c[ rn ][ at[ 'D' ] ] == '-' and c[ rn ][ at[ 'F' ] ] == '-' ){
      if( lft <= rgt ) return { rn , at[ 'D' ] };
      else return { rn , at[ 'F' ] };
    }
    if( c[ rn ][ at[ 'D' ] ] == '-' )
      return { rn , at[ 'D' ] };
    if( c[ rn ][ at[ 'F' ] ] == '-' )
      return { rn , at[ 'F' ] };
  }
  if( c[ rn ][ at[ 'C' ] ] == '-' or c[ rn ][ at[ 'G' ] ] == '-' ){
    //cerr << now << " " << lft << " " << rgt << endl;
    if( c[ rn ][ at[ 'C' ] ] == '-' and c[ rn ][ at[ 'G' ] ] == '-' ){
      if( lft <= rgt ) return { rn , at[ 'C' ] };
      else return { rn , at[ 'G' ] };
    }
    if( c[ rn ][ at[ 'C' ] ] == '-' )
      return { rn , at[ 'C' ] };
    if( c[ rn ][ at[ 'G' ] ] == '-' )
      return { rn , at[ 'G' ] };
  }
  if( c[ rn ][ at[ 'A' ] ] == '-' or c[ rn ][ at[ 'I' ] ] == '-' ){
    if( c[ rn ][ at[ 'A' ] ] == '-' and c[ rn ][ at[ 'I' ] ] == '-' ){
      if( lft <= rgt ) return { rn , at[ 'A' ] };
      else return { rn , at[ 'I' ] };
    }
    if( c[ rn ][ at[ 'A' ] ] == '-' )
      return { rn , at[ 'A' ] };
    if( c[ rn ][ at[ 'I' ] ] == '-' )
      return { rn , at[ 'I' ] };
  }
  if( c[ rn ][ at[ 'E' ] ] == '-' )
    return { rn , at[ 'E' ] };
  if( c[ rn ][ at[ 'B' ] ] == '-' or c[ rn ][ at[ 'H' ] ] == '-' ){
    if( c[ rn ][ at[ 'B' ] ] == '-' and c[ rn ][ at[ 'H' ] ] == '-' ){
      if( lft <= rgt ) return { rn , at[ 'B' ] };
      else return { rn , at[ 'H' ] };
    }
    if( c[ rn ][ at[ 'B' ] ] == '-' )
      return { rn , at[ 'B' ] };
    if( c[ rn ][ at[ 'H' ] ] == '-' )
      return { rn , at[ 'H' ] };
  }
  assert( false );
  return { 0 , 0 };
}
int main(){
  at[ 'A' ] = 0;
  at[ 'B' ] = 1;
  at[ 'C' ] = 2;
  at[ 'D' ] = 4;
  at[ 'E' ] = 5;
  at[ 'F' ] = 6;
  at[ 'G' ] = 8;
  at[ 'H' ] = 9;
  at[ 'I' ] = 10;
  cin >> r >> n;
  for( int i = 0 ; i < r + 3 ; i ++ )
    cin >> c[ i ];
  len = strlen( c[ 0 ] );
  for( int i = 0 ; i < n ; i ++ ){
    pair<int,int> rr = go( i );
    c[ rr.first ][ rr.second ] = ('a' + i);
  }
  for( int i = 0 ; i < r + 3 ; i ++ )
    cout << c[ i ] << endl;
}
