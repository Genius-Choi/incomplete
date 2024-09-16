static int option_parse_index_version(const struct option *opt,
				      const char *arg, int unset)
{
	char *c;
	const char *val = arg;
	pack_idx_opts.version = strtoul(val, &c, 10);
	if (pack_idx_opts.version > 2)
		die(_("unsupported index version %s"), val);
	if (*c == ',' && c[1])
		pack_idx_opts.off32_limit = strtoul(c+1, &c, 0);
	if (*c || pack_idx_opts.off32_limit & 0x80000000)
		die(_("bad index version '%s'"), val);
	return 0;
}
