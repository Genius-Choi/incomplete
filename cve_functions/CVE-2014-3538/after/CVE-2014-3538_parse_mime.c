parse_mime(struct magic_set *ms, struct magic_entry *me, const char *line)
{
	struct magic *m = &me->mp[0];

	return parse_extra(ms, me, line, offsetof(struct magic, mimetype),
	    sizeof(m->mimetype), "MIME", 1);
}
