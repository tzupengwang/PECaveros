struct Treap{
	int lsum , rsum , sum , maxsum;
	int sz , num , val , pri , tag;
	bool tagn; Treap *l , *r;
	Treap( int _val ){
		lsum = rsum = sum = maxsum = val = _val; sz = 1;
		pri = rand(); l = r = NULL; tag = 0; tagn = false;
	}
};
void push( Treap * a ){
	if( a->tagn ){
		a->val = a->num;
		if( a->l ){
			a->l->sum = a->num * a->l->sz;
			if( a->num >= 0 )
				a->l->lsum = a->l->rsum = a->l->maxsum = a->l->sum;
			else a->l->lsum = a->l->rsum = a->l->maxsum = a->num;
			a->l->tagn = true , a->l->num = a->num;
		}
		if( a->r ){
			a->r->sum = a->num * a->r->sz;
			if( a->num >= 0 )
				a->r->lsum = a->r->rsum = a->r->maxsum = a->r->sum;
			else a->r->lsum = a->r->rsum = a->r->maxsum = a->num;
			a->r->tagn = true , a->r->num = a->num;
		}
		a->tagn = false;
	}
	if( a->tag ){
		Treap *swp = a->l; a->l = a->r; a->r = swp;
		int swp2;
		if( a->l ){
			a->l->tag ^= 1;
			swp2 = a->l->lsum; a->l->lsum = a->l->rsum; a->l->rsum = swp2;
		}
		if( a->r ){
			a->r->tag ^= 1;
			swp2 = a->r->lsum; a->r->lsum = a->r->rsum; a->r->rsum = swp2;
		}
		a->tag = 0;
	}
}
int Sum( Treap * a ){ return a ? a->sum : 0; }
int Size( Treap * a ){ return a ? a->sz : 0; }
int lSum( Treap * a ){ return a ? a->lsum : 0; }
int rSum( Treap * a ){ return a ? a->rsum : 0; }
int maxSum( Treap * a ){ return a ? a->maxsum : -inf; }
void pull( Treap * a ){
	a->sum = Sum( a->l ) + Sum( a->r ) + a->val;
	a->lsum = Sum( a->l ) + a->val + max( 0 , lSum( a->r ) );
	if( a->l ) a->lsum = max( lSum( a->l ) , a->lsum );
	a->rsum = Sum( a->r ) + a->val + max( 0 , rSum( a->l ) );
	if( a->r ) a->rsum = max( rSum( a->r ) , a->rsum );
	a->maxsum = max( 0 , rSum( a->l ) ) + a->val + max( 0 , lSum( a->r ) );
	a->maxsum = max( a->maxsum , max( maxSum( a->l ) , maxSum( a->r ) ) );
	a->sz = Size( a->l ) + Size( a->r ) + 1;
}
Treap* merge( Treap *a , Treap *b ){
	if( !a || !b ) return a ? a : b;
	if( a->pri > b->pri ){
		push( a );
		a->r = merge( a->r , b );
		pull( a );
		return a;
	}else{
		push( b );
		b->l = merge( a , b->l );
		pull( b );
		return b;
	}
}
void split( Treap *t , int k , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	push( t );
	if( Size( t->l ) + 1 <= k ){
		a = t;
		split( t->r , k - Size( t->l ) - 1 , a->r , b );
		pull( a );
	}else{
		b = t;
		split( t->l , k , a , b->l );
		pull( b );
	}
}
void Delete( Treap *t ){
	if( t->l ) Delete( t->l );
	if( t->r ) Delete( t->r );
	delete t;
}
char c[ 20 ]; int n , m;
void solve(){
	Treap *t = NULL , *tl = NULL , *tr = NULL;
	n = getint(); m = getint();
	for( int i = 0 ; i < n ; i ++ )
		t = merge( t , new Treap( getint() ) );
	while( m -- ){
		scanf( "%s" , c );
		if( c[ 0 ] == 'I' ){
			int p , k;
			p = getint(); k = getint();
			split( t , p , tl , tr );
			t = NULL;
			while( k -- )
				t = merge( t , new Treap( getint() ) );
			t = merge( t , tr );
			t = merge( tl , t );
		}else if( c[ 0 ] == 'D' ){
			int p , k;
			p = getint(); k = getint();
			split( t , p - 1 , tl , t );
			split( t , k , t , tr );
			Delete( t );
			t = merge( tl , tr );
		}else if( c[ 0 ] == 'R' ){
			int p , k;
			p = getint(); k = getint();
			split( t , p - 1 , tl , t );
			split( t , k , t , tr );
			t->tag ^= 1;
			int swp = t->lsum; t->lsum = t->rsum; t->rsum = swp;
			t = merge( t , tr );
			t = merge( tl , t );
		}else if( c[ 0 ] == 'G' ){
			int p , k;
			p = getint(); k = getint();
			split( t , p - 1 , tl , t );
			split( t , k , t , tr );
			printf( "%d\n" , Sum( t ) );
			t = merge( t , tr );
			t = merge( tl , t );
		}else if( c[ 2 ] == 'K' ){
			int p , k;
			p = getint(); k = getint();
			split( t , p - 1 , tl , t );
			split( t , k , t , tr );
			t->tagn = true; t->num = getint();
			t->sum = t->num * t->sz;
			if( t->num >= 0 )
				t->lsum = t->rsum = t->maxsum = t->sum;
			else t->lsum = t->rsum = t->maxsum = t->num;
			t = merge( t , tr );
			t = merge( tl , t );
		}else printf( "%d\n" , maxSum( t ) );

	}
}
