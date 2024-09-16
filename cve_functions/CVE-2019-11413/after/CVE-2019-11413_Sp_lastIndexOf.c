static void Sp_lastIndexOf(js_State *J)
{
	const char *haystack = checkstring(J, 0);
	const char *needle = js_tostring(J, 1);
	int pos = js_isdefined(J, 2) ? js_tointeger(J, 2) : (int)strlen(haystack);
	int len = strlen(needle);
	int k = 0, last = -1;
	Rune rune;
	while (*haystack && k <= pos) {
		if (!strncmp(haystack, needle, len))
			last = k;
		haystack += chartorune(&rune, haystack);
		++k;
	}
	js_pushnumber(J, last);
}
