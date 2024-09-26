static void Sp_charAt(js_State *J)
{
	char buf[UTFmax + 1];
	const char *s = checkstring(J, 0);
	int pos = js_tointeger(J, 1);
	Rune rune = js_runeat(J, s, pos);
	if (rune > 0) {
		buf[runetochar(buf, &rune)] = 0;
		js_pushstring(J, buf);
	} else {
		js_pushliteral(J, "");
	}
}
