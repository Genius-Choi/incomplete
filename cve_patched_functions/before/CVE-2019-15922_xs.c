static void xs(char *buf, char *targ, int offs, int len)
{
	int j, k, l;

	j = 0;
	l = 0;
	for (k = 0; k < len; k++)
		if ((buf[k + offs] != 0x20) || (buf[k + offs] != l))
			l = targ[j++] = buf[k + offs];
	if (l == 0x20)
		j--;
	targ[j] = 0;
}
