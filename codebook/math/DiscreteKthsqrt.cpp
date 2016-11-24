// x^K mod P = A
const int LimitSave = 100000;
LL _mod( LL a , LL mo ){return ( a % mo + mo ) % mo;}
bool ext_gcd(LL A, LL B, LL C, LL &x, LL &y, LL &gn){
	LL t;
	if( A == 0 ){
		gn = B;
		if( _mod(C, B) == 0 )
    { x = 0; y = C / B; return true; }
		return false;
	}
  if( ext_gcd( _mod(B , A) , A , C , y , t , gn ) )
  { x = t - LL(B / A) * y; return true; }
	return false;
}
LL Division( LL A, LL B, LL modular ){
	LL gcdnum, K, Y;
	ext_gcd(modular, B, A, K, Y, gcdnum);
	Y = _mod(Y, modular);
  return Y < 0 ? Y + modular : Y;
}
struct tp{
	LL expo, res;
}data[ LimitSave + 100 ];
bool compareab( const tp &a, const tp &b )
{ return a.res < b.res; }
bool Binary_Search( LL key, LL &pos ){
	LL start, stop;
	start=1; stop=LimitSave;
	while( start <= stop ){
		pos = (start + stop)/2;
		if( data[pos].res == key ) return true;
		if( data[pos].res < key ) start = pos + 1;
		else stop = pos - 1;
	}
	return false;
}
LL get_log( LL root , LL A , LL mod ){
	LL i, j, times, XD, XT, position;
	if( mod - 1 < LimitSave ){
		LL now = 1;
    for( i = 0 ; i < mod ; i ++ ){
			if( now == A ) return i;
			now = _mod( now * root , mod );
		}
	}
	data[1].expo = 0; data[1].res = 1;
  for( i = 1 ; i < LimitSave ; i ++ ){
		data[i+1].expo=i;
		data[i+1].res=_mod(data[i].res*root,mod);
	}
	sort(data+1,data+LimitSave+1,compareab);
	times=mypow(root,LimitSave,mod);
	j=0; XD=1;
	while( 1 ){
		XT = Division(A, XD, mod);
		if( Binary_Search( XT, position ) )
			return j + data[position].expo;
		j = j + LimitSave;
		XD = _mod(XD * times, mod);
	}
}
LL P, K, A;
vector<LL> ans;
LL get_originroot( LL p ){
	LL primes[ 100 ];
	LL tot = 0, tp = P - 1;
	for( LL i = 2 ; i * i <= P - 1 ; i ++ )
		if( _mod( tp , i ) == 0 ){
			primes[ ++ tot ]=i;
			while( _mod(tp,i) == 0 ) tp /= i;
		}
	if( tp != 1 ) primes[ ++ tot] = tp;
	for( LL i = 2 ; ; i ++ ){
		bool ok = true;
    for( LL j = 1 ; j <= tot ; j ++ )
			if( mypow(i, (P-1)/primes[j], P ) == 1 )
      { ok = false; break; }
		if( ok ) return i;
	}
}
//x^K mod P = A
void work_ans() {
  cin>>P>>K>>A;
  A = A % P;
	ans.clear(); // roots in ans
	if( A == 0 )
  { ans.push_back( 0 ); return; }
	LL root,logs,delta,deltapower,now,gcdnum,x,y;
  root=get_originroot(P);
	logs=get_log(root,A,P);
	if( ext_gcd(K, P-1, logs, x, y, gcdnum) ){
		delta=(P-1) / gcdnum;
		x = _mod(x, delta);
		if(x < 0) x += delta;
		now = mypow(root, x, P);
		deltapower = mypow(root, delta, P);
		while(x < P-1 ){
			ans.push_back(now);
			now=_mod(now * deltapower, P);
			x=x+delta;
		}
	}
}
