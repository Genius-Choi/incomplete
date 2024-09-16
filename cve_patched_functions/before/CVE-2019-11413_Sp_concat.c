static void Sp_concat(js_State *J)
{
	int i, top = js_gettop(J);
	int n;
	char * volatile out;
	const char *s;

	if (top == 1)
		return;

	s = checkstring(J, 0);
	n = strlen(s);
	out = js_malloc(J, n + 1);
	strcpy(out, s);

	if (js_try(J)) {
		js_free(J, out);
		js_throw(J);
	}

	for (i = 1; i < top; ++i) {
		s = js_tostring(J, i);
		n += strlen(s);
		out = js_realloc(J, out, n + 1);
		strcat(out, s);
	}

	js_pushstring(J, out);
	js_endtry(J);
	js_free(J, out);
}
