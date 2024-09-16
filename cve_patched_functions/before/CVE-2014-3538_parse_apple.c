parse_apple(struct magic_set *ms, struct magic_entry *me, const char *line)
{
	struct magic *m = &me->mp[0];

	return parse_extra(ms, me, line, offsetof(struct magic, apple),
	    sizeof(m->apple), "APPLE", 0);
}
