#include <random>
mt19937 rng(0x5EED);
int randint(int lb, int ub)
{ return uniform_int_distribution<int>(lb, ub)(rng); }

#define SECs (clock() / CLOCKS_PER_SEC)

struct KeyHasher {
	size_t operator()(const Key& k) const {
		return k.first + k.second * 100000;
	}
};
typedef unordered_map<Key,int,KeyHasher> map_t;
