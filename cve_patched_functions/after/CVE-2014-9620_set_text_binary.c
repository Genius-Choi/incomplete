set_text_binary(struct magic_set *ms, struct magic_entry *me, uint32_t nme,
    uint32_t starttest)
{
	static const char text[] = "text";
	static const char binary[] = "binary";
	static const size_t len = sizeof(text);

	uint32_t i = starttest;

	do {
		set_test_type(me[starttest].mp, me[i].mp);
		if ((ms->flags & MAGIC_DEBUG) == 0)
			continue;
		(void)fprintf(stderr, "%s%s%s: %s\n",
		    me[i].mp->mimetype,
		    me[i].mp->mimetype[0] == '\0' ? "" : "; ",
		    me[i].mp->desc[0] ? me[i].mp->desc : "(no description)",
		    me[i].mp->flag & BINTEST ? binary : text);
		if (me[i].mp->flag & BINTEST) {
			char *p = strstr(me[i].mp->desc, text);
			if (p && (p == me[i].mp->desc ||
			    isspace((unsigned char)p[-1])) &&
			    (p + len - me[i].mp->desc == MAXstring
			    || (p[len] == '\0' ||
			    isspace((unsigned char)p[len]))))
				(void)fprintf(stderr, "*** Possible "
				    "binary test for text type\n");
		}
	} while (++i < nme && me[i].mp->cont_level != 0);
	return i;
}
