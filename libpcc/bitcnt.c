
int __builtin_clz(unsigned int);
int __builtin_ctz(unsigned int);
int __builtin_clzl(unsigned long);
int __builtin_ctzl(unsigned long);

int
__builtin_clz(unsigned int v)
{
	int i, n = v;

	for (i = 0; i < 100; i++)
		if ((n << i) < 0)
			break;
	return i;
}

int
__builtin_ctz(unsigned int v)
{
	int i, n = v;

	for (i = 0; i < 100; i++)
		if ((n >> i) & 1)
			break;
	return i;
}

int
__builtin_clzl(unsigned long v)
{
	int i;
	long n = v;

	for (i = 0; i < 100; i++)
		if ((n << i) < 0)
			break;
	return i;
}

int
__builtin_ctzl(unsigned long v)
{
	int i, n = v;

	for (i = 0; i < 100; i++)
		if ((n >> i) & 1)
			break;
	return i;
}
