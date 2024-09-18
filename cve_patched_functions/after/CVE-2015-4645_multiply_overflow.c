int multiply_overflow(int a, int multiplier)
{
	return (INT_MAX / multiplier) < a;
}
