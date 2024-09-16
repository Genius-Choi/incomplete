static void Sp_indexOf(js_State *J)
{
	const char *haystack = checkstring(J, 0);
	const char *needle = js_tostring(J, 1);
	int pos = js_tointeger(J, 2);
	int len = strlen(needle);
	int k = 0;
	Rune rune;
	while (*haystack) {
		if (k >= pos && !strncmp(haystack, needle, len)) {
			js_pushnumber(J, k);
			return;
		}
		haystack += chartorune(&rune, haystack);
		++k;
	}
	js_pushnumber(J, -1);
}
