#include <bits/stdc++.h>
using namespace std;
#define N 1021
typedef long long LL;
struct File{
  int type; // 0 for directory 1 for normal file
  LL sz;
  map<string, File*> files;
  File(){
    type = 0;
    sz = 0;
    files.clear();
  }
};
int n , sz;
char buf[ N ];
vector<string> d;
void parse(){
  d.clear();
  int len = strlen( buf );
  string tmp = "";
  for( int i = 1 ; i <= len ; i ++ ){
    if( i == len or buf[ i ] == '/' ){
      d.push_back( tmp );
      tmp = "";
      continue;
    }
    tmp += buf[ i ];
  }
}
File* root;
void add( File* now , size_t which ){
  now->sz += sz;
  if( which == d.size() ){
    now->type = 1;
    return;
  }
  auto it = now->files.find( d[ which ] );
  File* nxt;
  if( it == now->files.end() )
    nxt = now->files[ d[ which ] ] = new File();
  else
    nxt = it->second;
  add( nxt , which + 1 );
}
LL limit;
void print( File* cur , string name ){
  if( cur->type == 1 ) return;
  bool has_dir_chd = false;
  LL mxson_sz = 0;
  for( auto i : cur->files )
    if( i.second->type == 0 ){
      has_dir_chd = true;
      mxson_sz = max( mxson_sz , i.second->sz );
    }
  if( mxson_sz < limit ){
    putchar( " +"[ has_dir_chd ] );
    putchar( ' ' );
    printf( "%s %lld\n" , name.c_str() , cur->sz );
    return;
  }
  printf( "- %s %lld\n" , name.c_str() , cur->sz );
  for( auto i : cur->files ){
    if( i.second->type == 1 ) continue;
    string nxt_name = name;
    nxt_name += i.first;
    nxt_name += "/";
    print( i.second , nxt_name );
  }
}
int main(){
  scanf( "%d" , &n );
  root = new File();
  for( int i = 0; i < n ; i ++ ){
    scanf( "%s%d" , buf , &sz );
    parse();
    add( root , 0 );
  }
  scanf( "%lld" , &limit );
  string name = "/";
  print( root , name );
}
