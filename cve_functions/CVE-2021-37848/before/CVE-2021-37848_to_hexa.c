static unsigned char to_hexa(unsigned char c)
{
	if (c < 10)
		c += '0';
	else
		c += 'a' - 10;

	return c;
}
