#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Item{
  vector<int> a;
  int d1 , d2 , d3;
  Item(){ d1 = d2 = d3 = 1; }
  Item( int _d1 , int _d2 , int _d3 ){
    d1 = _d1; d2 = _d2; d3 = _d3;
    a.resize( d1 * d2 * d3 );
  }
  Item( const vector<int>& cand ){
    a = cand;
    d1 = d2 = 1; d3 = cand.size();
  }
  int size() const{ return d1 * d2 * d3; }
  int val( int x ) const{ return a[ x % size() ]; }
  int operator[]( int x ) const{ return a[ x % size() ]; }
  int& operator[]( int x ){ return a[ x % size() ]; }
  int val( int x , int y , int z ) const{
    return a[ (x * d2 * d3 + y * d3 + z ) % size() ];
  }
  void assign( int x , int y , int z , int v ){
    a[ (x * d2 * d3 + y * d3 + z ) % size() ] = v;
  }
  void print() const{
    for( int i = 0 ; i < d1 ; i ++ ){
      if( i ) puts( "" );
      for( int j = 0 ; j < d2 ; j ++ )
        for( int k = 0 ; k < d3 ; k ++ )
          printf( "%d%c" , val( i , j , k ) , " \n"[ k + 1 == d3 ] );
    }
  }
};
Item Iota( const Item& x ){
  vector<int> v;
  for( int i = 1 ; i <= x[ 0 ] ; i ++ )
    v.push_back( i );
  return Item( v );
}
Item rho( const Item& a , const Item& dim ){
  Item ret;
  if( dim.size() == 1 )
    ret = Item( 1 , 1 , dim[ 0 ] );
  if( dim.size() == 2 )
    ret = Item( 1 , dim[ 0 ] , dim[ 1 ] );
  if( dim.size() == 3 )
    ret = Item( dim[ 0 ] , dim[ 1 ] , dim[ 2 ] );
  for( int i = 0 ; i < ret.size() ; i ++ )
    ret[ i ] = a[ i ];
  return ret;
}
Item drop( const Item& a , const Item& d ){
  Item ret( 1 , 1 , a.size() - d[ 0 ] );
  for( int i = 0 ; i < a.size() - d[ 0 ] ; i ++ )
    ret[ i ] = a[ i + d[ 0 ] ];
  return ret;
}
Item operator+( const Item& i1 , int tk ){
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] + tk;
  return ret;
}
Item operator+( const Item& i1 , const Item& i2 ){
  if( i1.size() != i2.size() ){
    if( i1.size() == 1 ) return i2 + i1[ 0 ];
    if( i2.size() == 1 ) return i1 + i2[ 0 ];
    assert( false );
    return Item();
  }
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] + i2[ i ];
  return ret;
}
Item operator-( const Item& i1 , int tk ){
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] - tk;
  return ret;
}
Item operator-( int tk , const Item& i1 ){
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = tk - i1[ i ];
  return ret;
}
Item operator-( const Item& i1 , const Item& i2 ){
  if( i1.size() != i2.size() ){
    if( i1.size() == 1 ) return i1[ 0 ] - i2;
    if( i2.size() == 1 ) return i1 - i2[ 0 ];
    assert( false );
    return Item();
  }
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] - i2[ i ];
  return ret;
}
Item operator*( const Item& i1 , int tk ){
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] * tk;
  return ret;
}
Item operator*( const Item& i1 , const Item& i2 ){
  if( i1.size() != i2.size() ){
    if( i1.size() == 1 ) return i2 * i1[ 0 ];
    if( i2.size() == 1 ) return i1 * i2[ 0 ];
    assert( false );
    return Item();
  }
  Item ret = i1;
  for( int i = 0 ; i < i1.size() ; i ++ )
    ret[ i ] = i1[ i ] * i2[ i ];
  return ret;
}
#define PLUS 0
#define MINUS 1
#define MUL 2
Item Insert( const Item& a , int op ){
  Item ret( 1 , a.d1 , a.d2 );
  for( int i = 0 ; i < a.d1 ; i ++ )
    for( int j = 0 ; j < a.d2 ; j ++ ){
      int val = a.val( i , j , a.d3 - 1 );
      for( int k = a.d3 - 2 ; k >= 0 ; k -- ){
        if( op == PLUS )
          val = a.val( i , j , k ) + val;
        else if( op == MINUS )
          val = a.val( i , j , k ) - val;
        else if( op == MUL )
          val = a.val( i , j , k ) * val;
        else
          assert( false );
      }
      ret.assign( 1 , i , j , val );
    }
  return ret;
}
string buf;
vector<string> tokens;
void tokenized(){
  tokens.clear();
  stringstream ss( buf );
  string tmp;
  while( ss >> tmp )
    tokens.push_back( tmp );
}
vector<int> pr;
void preparse(){
  pr.resize( tokens.size() );
  vector<int> wt;
  for( size_t i = 0 ; i < tokens.size() ; i ++ )
    if( tokens[ i ] == "(" )
      wt.push_back( i );
    else if( tokens[ i ] == ")" ){
      pr[ wt.back() ] = i;
      wt.pop_back();
    }
}
map<string,Item> memo;
#define Key first.first
#define Val first.second
#define S second.first
#define T second.second
Item go( int l , int r );
typedef pair< pair<string,Item> , pair<int,int> > info;
Item eval( const info& pp ){
  if( pp.S != -1 ) return go( pp.S , pp.T );
  if( pp.Key.length() == 0 )
    return pp.Val;
  return memo[ pp.Key ];
}
Item parse( vector< info >& v ){
  Item lst;
  reverse( v.begin() , v.end() );
  for( size_t i = 0 ; i < v.size() ; i ++ ){
    if( v[ i ].S != -1 )
      v[ i ].Val = go( v[ i ].S , v[ i ].T );
    if( i == 0 ){
      if( v[ i ].Key.length() == 0 )
        lst = v[ i ].Val;
      else
        lst = memo[ v[ i ].Key ];
      continue;
    }
    if( v[ i ].Key == "=" ){
      memo[ v[ i + 1 ].Key ] = lst;
      i ++;
      continue;
    }
    if( v[ i ].Key == "iota" ){
      lst = Iota( lst );
      continue;
    }
    if( v[ i ].Key == "rho" ){
      lst = rho( lst , eval( v[ i + 1 ] ) );
      i ++;
      continue;
    }
    if( v[ i ].Key == "drop" ){
      lst = drop( lst , eval( v[ i + 1 ] ) );
      i ++;
      continue;
    }
    if( v[ i ].Key == "/" ){
      if( v[ i + 1 ].Key == "+" )
        lst = Insert( lst , PLUS );
      if( v[ i + 1 ].Key == "-" )
        lst = Insert( lst , MINUS );
      if( v[ i + 1 ].Key == "*" )
        lst = Insert( lst , MUL );
      i ++;
      continue;
    }
    if( v[ i ].Key == "+" ){
      lst = eval( v[ i + 1 ] ) + lst;
      i ++;
      continue;
    }
    if( v[ i ].Key == "-" ){
      lst = eval( v[ i + 1 ] ) - lst;
      i ++;
      continue;
    }
    if( v[ i ].Key == "*" ){
      lst = eval( v[ i + 1 ] ) * lst;
      i ++;
      continue;
    }
    assert( false );
  }
  return lst;
}
Item go( int l , int r ){
  vector< info > v;
  for( int i = l ; i <= r ; ){
    if( tokens[ i ] == "(" ){
      v.push_back( { { "" , Item() } ,
                     { i + 1 , pr[ i ] - 1 } } );
      i = pr[ i ] + 1;
      continue;
    }
    if( !isdigit( tokens[ i ][ 0 ] ) ){
      v.push_back( { { tokens[ i ] , Item() } , {-1, -1} } );
      i ++;
      continue;
    }
    vector<int> tv;
    while( i <= r and isdigit( tokens[ i ][ 0 ] ) ){
      tv.push_back( atoi( tokens[ i ].c_str() ) );
      i ++;
    }
    v.push_back( { { "" , Item( tv ) } , {-1, -1} } );
  }
  return parse( v );
}
int _cs;
int main(){
  while( getline( cin , buf ) ){
    if( buf == "#" ) break;
    tokenized();
    preparse();
    printf( "Case %d: %s\n" , ++ _cs , buf.c_str() );
    go( 0 , tokens.size() - 1u ).print();
  }
}
