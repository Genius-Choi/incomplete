static bool fetch_seccomp(const char *name, const char *lxcpath,
		struct lxc_proc_context_info *i, lxc_attach_options_t *options)
{
	struct lxc_container *c;

	if (!(options->namespaces & CLONE_NEWNS) || !(options->attach_flags & LXC_ATTACH_LSM))
		return true;

	c = lxc_container_new(name, lxcpath);
	if (!c)
		return false;
	i->container = c;
	if (!c->lxc_conf)
		return false;
	if (lxc_read_seccomp_config(c->lxc_conf) < 0) {
		ERROR("Error reading seccomp policy");
		return false;
	}

	return true;
}
