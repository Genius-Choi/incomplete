static void Sp_toUpperCase(js_State *J)
{
	const char *src = checkstring(J, 0);
	char *dst = js_malloc(J, UTFmax * strlen(src) + 1);
	const char *s = src;
	char *d = dst;
	Rune rune;
	while (*s) {
		s += chartorune(&rune, s);
		rune = toupperrune(rune);
		d += runetochar(d, &rune);
	}
	*d = 0;
	if (js_try(J)) {
		js_free(J, dst);
		js_throw(J);
	}
	js_pushstring(J, dst);
	js_endtry(J);
	js_free(J, dst);
}
