static void Sp_replace(js_State *J)
{
	if (js_isregexp(J, 1))
		Sp_replace_regexp(J);
	else
		Sp_replace_string(J);
}
