static unsigned char to_digit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		c -= '0';
	else
		c -= 'a' - 10;

	return c;
}
