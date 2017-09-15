#include <bits/stdc++.h>
using namespace std;
struct Item{
  int type;
  // 0 for article, 1 for book
  vector< deque<string> > author;
  string title , jp;
  int year , volume , number , pages , paget;
  Item(){
    type = -1;
    volume = -1;
    number = -1;
    pages = -1;
    paget = -1;
  }
  void print( int id ){
    assert( 0 <= type and type <= 1 );
    if( type == 0 ){
      printf( "[%d] " , id );
      for( size_t i = 0 ; i < author.size() ; i ++ ){
        if( i ) printf( ", " );
        printf( "%s" , author[ i ][ 0 ].c_str() );
        for( size_t j = 1 ; j < author[ i ].size() ; j ++ )
          printf( " %c." , author[ i ][ j ][ 0 ] );
      }
      printf( " %s // %s" , title.c_str() , jp.c_str() );
      if( volume != -1 )
        printf( ", %d" , volume );
      if( number != -1 )
        printf( " (%d)" , number );
      printf( " -- %d" , year );
      if( pages != -1 ){
        if( pages == paget )
          printf( " -- p. %d" , pages );
        else
          printf( " -- pp. %d--%d" , pages , paget );
      }
    }else{
      printf( "[%d] " , id );
      for( size_t i = 0 ; i < author.size() ; i ++ ){
        if( i ) printf( ", " );
        printf( "%s" , author[ i ][ 0 ].c_str() );
        for( size_t j = 1 ; j < author[ i ].size() ; j ++ )
          printf( " %c." , author[ i ][ j ][ 0 ] );
      }
      printf( " %s" , title.c_str() );
      if( volume != -1 )
        printf( ", Vol. %d" , volume );
      printf( " -- %s, %d" , jp.c_str() , year );
    }
    puts( "" );
  }
  void read_author( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    deque<string> name;
    author.clear();
    string tmp = "";
    while( buf[ ptr ] != '\"' ){
      if( buf[ ptr ] == ' ' ){
        if( tmp.length() )
          name.push_back( tmp );
        tmp = "";
        ptr ++;
        continue;
      }else if( ptr + 3 < (int)buf.length() and
                buf[ ptr + 0 ] == 'a' and
                buf[ ptr + 1 ] == 'n' and
                buf[ ptr + 2 ] == 'd' and
                buf[ ptr + 3 ] == ' ' ){
        name.push_front( name.back() );
        name.pop_back();
        author.push_back( name );
        name.clear();
        ptr += 4;
      }else{
        tmp += buf[ ptr ];
        ptr ++;
      }
    }
    if( tmp.length() )
      name.push_back( tmp );
    if( name.size() ){
      name.push_front( name.back() );
      name.pop_back();
      author.push_back( name );
    }
    sort( author.begin() , author.end() );
  }
  void read_title( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    while( buf[ ptr ] != '\"' ){
      title += buf[ ptr ];
      ptr ++;
    }
  }
  void read_jp( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    while( buf[ ptr ] != '\"' ){
      jp += buf[ ptr ];
      ptr ++;
    }
  }
  void read_year( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    year = 0;
    while( buf[ ptr ] != '\"' ){
      year = year * 10 + ( buf[ ptr ] - '0' );
      ptr ++;
    }
  }
  void read_volume( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    volume = 0;
    while( buf[ ptr ] != '\"' ){
      volume = volume * 10 + ( buf[ ptr ] - '0' );
      ptr ++;
    }
  }
  void read_number( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    number = 0;
    while( buf[ ptr ] != '\"' ){
      number = number * 10 + ( buf[ ptr ] - '0' );
      ptr ++;
    }
  }
  void read_pages( const string& buf ){
    int ptr = 0;
    while( buf[ ptr ] != '\"' ) ptr ++;
    ptr ++;
    string tmp = "";
    while( buf[ ptr ] != '\"' ){
      tmp += buf[ ptr ];
      ptr ++;
    }
    if( sscanf( tmp.c_str() , "%d--%d" , &pages , &paget ) == 2 )
      return;
    assert( sscanf( tmp.c_str() , "%d" , &pages ) == 1 );
    paget = pages;
  }
  void read( const string& buf ){
    int len = buf.length();
    if( buf[ 1 ] == 'b' ){
      type = 1;
      int ptr = 0;
      while( buf[ ptr ] != '{' ) ptr ++;
      ptr ++;
      while( ptr < len ){
        while( buf[ ptr ] == ' ' ) ptr ++;
        int til = ptr;
        while( buf[ til ] != '\"' ) til ++;
        til ++;
        while( buf[ til ] != '\"' ) til ++;
        til ++;
        if( buf[ ptr ] == 'a' ) read_author( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 't' ) read_title( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'p' ) read_jp( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'y' ) read_year( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'v' ) read_volume( buf.substr( ptr , til - ptr ) );
        else assert( false );
        ptr = til + 1;
      }
    }else if( buf[ 1 ] == 'a' ){
      type = 0;
      int ptr = 0;
      while( buf[ ptr ] != '{' ) ptr ++;
      ptr ++;
      while( ptr < len ){
        while( buf[ ptr ] == ' ' ) ptr ++;
        int til = ptr;
        while( buf[ til ] != '\"' ) til ++;
        til ++;
        while( buf[ til ] != '\"' ) til ++;
        til ++;
        if( buf[ ptr ] == 'a' ) read_author( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 't' ) read_title( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'j' ) read_jp( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'y' ) read_year( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'v' ) read_volume( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'n' ) read_number( buf.substr( ptr , til - ptr ) );
        else if( buf[ ptr ] == 'p' ) read_pages( buf.substr( ptr , til - ptr ) );
        else assert( false );
        ptr = til + 1;
      }
    }else
      assert( false );
  }
} tmp;
bool cmp( Item& i1 , Item& i2 ){
  size_t atmst = min( i1.author.size() , i2.author.size() );
  for( size_t i = 0 ; i < atmst ; i ++ ){
    size_t atmst2 = min( i1.author[ i ].size() , i2.author[ i ].size() );
    for( size_t j = 0 ; j < atmst2 ; j ++ )
      if( i1.author[ i ][ j ] != i2.author[ i ][ j ] )
        return i1.author[ i ][ j ] < i2.author[ i ][ j ];
    if( i1.author[ i ].size() != i2.author[ i ].size() )
      return i1.author[ i ].size() < i2.author[ i ].size();
  }
  if( i1.author.size() != i2.author.size() )
    return i1.author.size() < i2.author.size();
  if( i1.title != i2.title )
    return i1.title < i2.title;
  if( i1.type == 1 and i2.type == 1 )
    return i1.volume < i2.volume;
  return false;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "bibtex.in" , "r" , stdin );
  freopen( "bibtex.out" , "w" , stdout );
#endif
  string buf , tbuf;
  while( getline( cin , tbuf ) )
    buf += tbuf;
  int len = buf.length() , ptr = 0;
  vector<Item> vv;
  while( true ){
    while( ptr < len and buf[ ptr ] != '@' ) ptr ++;
    if( ptr >= len ) break;
    int sptr = ptr;
    while( ptr < len and buf[ ptr ] != '}' ) ptr ++;
    if( ptr >= len ) break;
    tmp.read( buf.substr( sptr , ptr - sptr ) );
    vv.push_back( tmp );
    tmp = Item();
  }
  sort( vv.begin() , vv.end() , cmp );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    vv[ i ].print( i + 1 );
}
