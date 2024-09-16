int add_overflow(int a, int b)
{
	return (INT_MAX - a) < b;
}
