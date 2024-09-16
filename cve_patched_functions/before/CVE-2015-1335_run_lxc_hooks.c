int run_lxc_hooks(const char *name, char *hook, struct lxc_conf *conf,
		  const char *lxcpath, char *argv[])
{
	int which = -1;
	struct lxc_list *it;

	if (strcmp(hook, "pre-start") == 0)
		which = LXCHOOK_PRESTART;
	else if (strcmp(hook, "pre-mount") == 0)
		which = LXCHOOK_PREMOUNT;
	else if (strcmp(hook, "mount") == 0)
		which = LXCHOOK_MOUNT;
	else if (strcmp(hook, "autodev") == 0)
		which = LXCHOOK_AUTODEV;
	else if (strcmp(hook, "start") == 0)
		which = LXCHOOK_START;
	else if (strcmp(hook, "post-stop") == 0)
		which = LXCHOOK_POSTSTOP;
	else if (strcmp(hook, "clone") == 0)
		which = LXCHOOK_CLONE;
	else if (strcmp(hook, "destroy") == 0)
		which = LXCHOOK_DESTROY;
	else
		return -1;
	lxc_list_for_each(it, &conf->hooks[which]) {
		int ret;
		char *hookname = it->elem;
		ret = run_script_argv(name, "lxc", hookname, hook, lxcpath, argv);
		if (ret)
			return ret;
	}
	return 0;
}
