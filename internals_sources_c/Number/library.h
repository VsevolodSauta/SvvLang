static long long_max(long a, long b)
{
	return (a > b ? a : b);
}

static long long_min(long a, long b)
{
	return (a < b ? a : b);
}

static long long_gcd(long a, long b)
{
	if(!(a || b))
		return 1;
	if(!a)
		return b;
	if(!b)
		return a;
	while(1)
	{
		if(a % b) {
			a %= b;
		} else {
			return b;
		}
		if(b % a) {
			b %= a;
		} else {
			return a;
		}
	}
}

static long long_lcm(long a, long b)
{
	return (a / long_gcd(a, b)) * b;
}
