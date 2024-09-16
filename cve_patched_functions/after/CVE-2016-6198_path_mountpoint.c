path_mountpoint(struct nameidata *nd, unsigned flags, struct path *path)
{
	const char *s = path_init(nd, flags);
	int err;
	if (IS_ERR(s))
		return PTR_ERR(s);
	while (!(err = link_path_walk(s, nd)) &&
		(err = mountpoint_last(nd, path)) > 0) {
		s = trailing_symlink(nd);
		if (IS_ERR(s)) {
			err = PTR_ERR(s);
			break;
		}
	}
	terminate_walk(nd);
	return err;
}
