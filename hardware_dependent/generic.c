long eldestOneNumber(long arg)
{
	long shift = sizeof(arg) * 4;
	while(shift > 0)
	{
		arg |= arg >> shift;
		shift /= 2;
	}
	return arg ^ (arg >> 1);
}

long eldestOnePosition(long arg)
{
	if(arg == -1) return sizeof(arg) * 8;
	if(arg == 0) return -1;

	unsigned long uarg = (unsigned long) arg;

	long shift = sizeof(uarg) * 4;
	long inc = sizeof(uarg) * 2;
	while(1)
	{
		if(1ul << shift <= uarg)
		{
			if((1ul << (shift + 1) > uarg) || (shift == sizeof(uarg) - 1))
			{
				return shift;
			} else {
				shift += inc;
			}
		} else {
			shift -= inc;
		}
		inc /= 2;
	}
}

long anyZeroPosition(long arg)
{
	if(arg == -1) return -1;
	for(long position = 0; position < sizeof(arg) * 8; position++)
	{
		if((arg & (1ul << position)) == 0)
			return position;
	}

	// UNREACHABLE
	ASSERT_C("Allocator: no zero found, but some exist.", 0);
	return -1;
}

long is2Power(long arg)
{
	return (arg & (arg - 1)) == 0;
}

void memcpy(char* dest, char* src, long size)
{
        long i = size / sizeof(long);
        while(i)
        {
                i--;
                ((long*) dest)[i] = ((long*) src)[i];
        }
        i = size % sizeof(long);
        while(i)
        {
                dest[size - i] = src[size - i];
                i--;
        }
}

