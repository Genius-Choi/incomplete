static void Sp_trim(js_State *J)
{
	const char *s, *e;
	s = checkstring(J, 0);
	while (istrim(*s))
		++s;
	e = s + strlen(s);
	while (e > s && istrim(e[-1]))
		--e;
	js_pushlstring(J, s, e - s);
}
