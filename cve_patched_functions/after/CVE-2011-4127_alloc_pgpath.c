static struct pgpath *alloc_pgpath(void)
{
	struct pgpath *pgpath = kzalloc(sizeof(*pgpath), GFP_KERNEL);

	if (pgpath) {
		pgpath->is_active = 1;
		INIT_DELAYED_WORK(&pgpath->activate_path, activate_path);
	}

	return pgpath;
}
