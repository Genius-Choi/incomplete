static signed long get_personality(const char *name, const char *lxcpath)
{
	char *p = lxc_cmd_get_config_item(name, "lxc.arch", lxcpath);
	signed long ret;

	if (!p)
		return -1;
	ret = lxc_config_parse_arch(p);
	free(p);
	return ret;
}
