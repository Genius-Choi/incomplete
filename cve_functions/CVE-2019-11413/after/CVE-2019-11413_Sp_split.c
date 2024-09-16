static void Sp_split(js_State *J)
{
	if (js_isundefined(J, 1)) {
		js_newarray(J);
		js_copy(J, 0);
		js_setindex(J, -2, 0);
	} else if (js_isregexp(J, 1)) {
		Sp_split_regexp(J);
	} else {
		Sp_split_string(J);
	}
}
