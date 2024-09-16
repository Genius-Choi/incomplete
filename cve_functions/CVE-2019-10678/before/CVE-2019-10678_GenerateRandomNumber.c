int GenerateRandomNumber(const int range)
{
	if (p == ((unsigned char *) (&entropy + 1)))
	{
		switch (entropy.which)
		{
			case 0:
				entropy.t += time (NULL);
				accSeed ^= entropy.t;
				break;
			case 1:
				entropy.c += clock();
				break;
			case 2:
				entropy.counter++;
				break;
		}
		entropy.which = (entropy.which + 1) % 3;
		p = (unsigned char *) &entropy.t;
	}
	accSeed = ((accSeed * (UCHAR_MAX + 2U)) | 1) + (int) *p;
	p++;
	srand (accSeed);
	return (rand() / (RAND_MAX / range));
}
