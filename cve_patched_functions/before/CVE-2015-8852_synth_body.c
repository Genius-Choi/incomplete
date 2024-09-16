synth_body(const char *len, int rnd)
{
	int i, j, k, l;
	char *b;


	AN(len);
	i = strtoul(len, NULL, 0);
	assert(i > 0);
	b = malloc(i + 1L);
	AN(b);
	l = k = '!';
	for (j = 0; j < i; j++) {
		if ((j % 64) == 63) {
			b[j] = '\n';
			k++;
			if (k == '~')
				k = '!';
			l = k;
		} else if (rnd) {
			b[j] = (random() % 95) + ' ';
		} else {
			b[j] = (char)l;
			if (++l == '~')
				l = '!';
		}
	}
	b[i - 1] = '\n';
	b[i] = '\0';
	return (b);
}
