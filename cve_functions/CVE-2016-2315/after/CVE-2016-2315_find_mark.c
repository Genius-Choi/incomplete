static struct object_entry *find_mark(uintmax_t idnum)
{
	uintmax_t orig_idnum = idnum;
	struct mark_set *s = marks;
	struct object_entry *oe = NULL;
	if ((idnum >> s->shift) < 1024) {
		while (s && s->shift) {
			uintmax_t i = idnum >> s->shift;
			idnum -= i << s->shift;
			s = s->data.sets[i];
		}
		if (s)
			oe = s->data.marked[idnum];
	}
	if (!oe)
		die("mark :%" PRIuMAX " not declared", orig_idnum);
	return oe;
}
