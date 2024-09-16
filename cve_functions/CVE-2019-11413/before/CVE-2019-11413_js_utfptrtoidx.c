int js_utfptrtoidx(const char *s, const char *p)
{
	Rune rune;
	int i = 0;
	while (s < p) {
		if (*(unsigned char *)s < Runeself)
			++s;
		else
			s += chartorune(&rune, s);
		++i;
	}
	return i;
}
