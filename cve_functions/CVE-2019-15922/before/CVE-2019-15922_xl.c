static int xl(char *buf, int offs)
{
	int v, k;

	v = 0;
	for (k = 0; k < 4; k++)
		v = v * 256 + (buf[k + offs] & 0xff);
	return v;
}
