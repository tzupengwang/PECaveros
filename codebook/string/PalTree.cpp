const int MAXN = 200010;
struct PalT{
  struct Node{
    int nxt[ 33 ] , len , fail;
    ll cnt;
  };
  int tot , lst;
  Node nd[ MAXN * 2 ];
  char* s;
  int newNode( int l , int _fail ){
    int res = ++tot;
    memset( nd[ res ].nxt , 0 , sizeof nd[ res ].nxt );
    nd[ res ].len = l;
    nd[ res ].cnt = 0;
    nd[ res ].fail = _fail;
    return res;
  }
  void push( int p ){
    int np = lst;
    int c = s[ p ] - 'a';
    while( p - nd[ np ].len - 1 < 0
        || s[ p ] != s[ p - nd[ np ].len - 1 ] )
      np = nd[ np ].fail;

    if( nd[ np ].nxt[ c ] ){
      nd[ nd[ np ].nxt[ c ] ].cnt++;
      lst = nd[ np ].nxt[ c ];
      return ;
    }
    int nq = newNode( nd[ np ].len + 2 , 0 );
    nd[ nq ].cnt++;
    nd[ np ].nxt[ c ] = nq;
    lst = nq;
    if( nd[ nq ].len == 1 ){
      nd[ nq ].fail = 2;
      return ;
    }
    int tf = nd[ np ].fail;
    while( p - nd[ tf ].len - 1 < 0
        || s[ p ] != s[ p - nd[ tf ].len - 1 ] )
      tf = nd[ tf ].fail;

    nd[ nq ].fail = nd[ tf ].nxt[ c ];
    return ;
  }
  void init( char* _s ){
    s = _s;
    tot = 0;
    newNode( -1 , 1 );
    newNode( 0 , 1 );
    lst = 2;
    for( int i = 0 ; s[ i ] ; i++ )
      push( i );
  }
  void yutruli(){
#define REPD(i, s, e) for(int i = (s); i >= (e); i--)
    REPD( i , tot , 1 )
      nd[ nd[ i ].fail ].cnt += nd[ i ].cnt;
    nd[ 1 ].cnt = nd[ 2 ].cnt = 0ll;
  }
} pA;
int main(){ pA.init( sa ); }
