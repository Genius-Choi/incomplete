void lbs_debugfs_init_one(struct lbs_private *priv, struct net_device *dev)
{
	int i;
	const struct lbs_debugfs_files *files;
	if (!lbs_dir)
		goto exit;

	priv->debugfs_dir = debugfs_create_dir(dev->name, lbs_dir);
	if (!priv->debugfs_dir)
		goto exit;

	for (i=0; i<ARRAY_SIZE(debugfs_files); i++) {
		files = &debugfs_files[i];
		priv->debugfs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->debugfs_dir,
							     priv,
							     &files->fops);
	}

	priv->events_dir = debugfs_create_dir("subscribed_events", priv->debugfs_dir);
	if (!priv->events_dir)
		goto exit;

	for (i=0; i<ARRAY_SIZE(debugfs_events_files); i++) {
		files = &debugfs_events_files[i];
		priv->debugfs_events_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->events_dir,
							     priv,
							     &files->fops);
	}

	priv->regs_dir = debugfs_create_dir("registers", priv->debugfs_dir);
	if (!priv->regs_dir)
		goto exit;

	for (i=0; i<ARRAY_SIZE(debugfs_regs_files); i++) {
		files = &debugfs_regs_files[i];
		priv->debugfs_regs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->regs_dir,
							     priv,
							     &files->fops);
	}

#ifdef PROC_DEBUG
	lbs_debug_init(priv);
#endif
exit:
	return;
}
