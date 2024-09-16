file_fmtcheck(struct magic_set *ms, const struct magic *m, const char *def,
	const char *file, size_t line)
{
	const char *ptr = fmtcheck(m->desc, def);
	if (ptr == def)
		file_magerror(ms,
		    "%s, %" SIZE_T_FORMAT "u: format `%s' does not match"
		    " with `%s'", file, line, m->desc, def);
	return ptr;
}
