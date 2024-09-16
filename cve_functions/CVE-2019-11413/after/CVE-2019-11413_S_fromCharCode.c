static void S_fromCharCode(js_State *J)
{
	int i, top = js_gettop(J);
	Rune c;
	char *s, *p;

	s = p = js_malloc(J, (top-1) * UTFmax + 1);

	if (js_try(J)) {
		js_free(J, s);
		js_throw(J);
	}

	for (i = 1; i < top; ++i) {
		c = js_touint16(J, i);
		p += runetochar(p, &c);
	}
	*p = 0;
	js_pushstring(J, s);

	js_endtry(J);
	js_free(J, s);
}
