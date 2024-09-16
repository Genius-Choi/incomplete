static int canon(Rune c)
{
	Rune u = toupperrune(c);
	if (c >= 128 && u < 128)
		return c;
	return u;
}
