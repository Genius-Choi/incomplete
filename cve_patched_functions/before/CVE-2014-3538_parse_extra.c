parse_extra(struct magic_set *ms, struct magic_entry *me, const char *line,
    off_t off, size_t len, const char *name, int nt)
{
	size_t i;
	const char *l = line;
	struct magic *m = &me->mp[me->cont_count == 0 ? 0 : me->cont_count - 1];
	char *buf = (char *)m + off;

	if (buf[0] != '\0') {
		len = nt ? strlen(buf) : len;
		file_magwarn(ms, "Current entry already has a %s type "
		    "`%.*s', new type `%s'", name, (int)len, buf, l);
		return -1;
	}	

	if (*m->desc == '\0') {
		file_magwarn(ms, "Current entry does not yet have a "
		    "description for adding a %s type", name);
		return -1;
	}

	EATAB;
	for (i = 0; *l && ((isascii((unsigned char)*l) &&
	    isalnum((unsigned char)*l)) || strchr("-+/.", *l)) &&
	    i < len; buf[i++] = *l++)
		continue;

	if (i == len && *l) {
		if (nt)
			buf[len - 1] = '\0';
		if (ms->flags & MAGIC_CHECK)
			file_magwarn(ms, "%s type `%s' truncated %"
			    SIZE_T_FORMAT "u", name, line, i);
	} else {
		if (nt)
			buf[i] = '\0';
	}

	if (i > 0)
		return 0;
	else
		return -1;
}
