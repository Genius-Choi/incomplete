int nearest_power(int num)
{
	int n = 1;

	while (n < num) n <<= 1;
	return n;
}
