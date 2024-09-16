static uintmax_t parse_mark_ref_eol(const char *p)
{
	char *end;
	uintmax_t mark;

	mark = parse_mark_ref(p, &end);
	if (*end != '\0')
		die("Garbage after mark: %s", command_buf.buf);
	return mark;
}
