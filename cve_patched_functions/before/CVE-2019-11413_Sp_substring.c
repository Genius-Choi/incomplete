static void Sp_substring(js_State *J)
{
	const char *str = checkstring(J, 0);
	const char *ss, *ee;
	int len = utflen(str);
	int s = js_tointeger(J, 1);
	int e = js_isdefined(J, 2) ? js_tointeger(J, 2) : len;

	s = s < 0 ? 0 : s > len ? len : s;
	e = e < 0 ? 0 : e > len ? len : e;

	if (s < e) {
		ss = js_utfidxtoptr(str, s);
		ee = js_utfidxtoptr(ss, e - s);
	} else {
		ss = js_utfidxtoptr(str, e);
		ee = js_utfidxtoptr(ss, s - e);
	}

	js_pushlstring(J, ss, ee - ss);
}
