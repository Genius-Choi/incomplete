static void Sp_localeCompare(js_State *J)
{
	const char *a = checkstring(J, 0);
	const char *b = js_tostring(J, 1);
	js_pushnumber(J, strcmp(a, b));
}
