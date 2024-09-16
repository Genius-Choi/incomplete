static char *parse_tmp_evals(RCore *core, const char *str) {
	char *res = NULL;
	RStrBuf *buf;
	char *s = strdup (str);
	buf = r_strbuf_new ("");
	int i, argc = r_str_split (s, ',');
	for (i = 0; i < argc; i++) {
		char *eq, *kv = (char *)r_str_word_get0 (s, i);
		if (!kv) {
			break;
		}
		eq = strchr (kv, '=');
		if (eq) {
			*eq = 0;
			const char *ov = r_config_get (core->config, kv);
			r_strbuf_appendf (buf, "e %s=%s;", kv, ov);
			r_config_set (core->config, kv, eq + 1);
			*eq = '=';
		} else {
			eprintf ("Missing '=' in e: expression (%s)\n", kv);
		}
	}
	res = r_strbuf_drain (buf);
	free (s);
	return res;
}
