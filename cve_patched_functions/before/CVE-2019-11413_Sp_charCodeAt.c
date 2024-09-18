static void Sp_charCodeAt(js_State *J)
{
	const char *s = checkstring(J, 0);
	int pos = js_tointeger(J, 1);
	Rune rune = js_runeat(J, s, pos);
	if (rune > 0)
		js_pushnumber(J, rune);
	else
		js_pushnumber(J, NAN);
}
