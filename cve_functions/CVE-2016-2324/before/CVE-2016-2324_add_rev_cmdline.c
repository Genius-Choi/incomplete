static void add_rev_cmdline(struct rev_info *revs,
			    struct object *item,
			    const char *name,
			    int whence,
			    unsigned flags)
{
	struct rev_cmdline_info *info = &revs->cmdline;
	int nr = info->nr;

	ALLOC_GROW(info->rev, nr + 1, info->alloc);
	info->rev[nr].item = item;
	info->rev[nr].name = xstrdup(name);
	info->rev[nr].whence = whence;
	info->rev[nr].flags = flags;
	info->nr++;
}
