static int parse_hw_handler(struct dm_arg_set *as, struct multipath *m)
{
	unsigned hw_argc;
	int ret;
	struct dm_target *ti = m->ti;

	static struct dm_arg _args[] = {
		{0, 1024, "invalid number of hardware handler args"},
	};

	if (dm_read_arg_group(_args, as, &hw_argc, &ti->error))
		return -EINVAL;

	if (!hw_argc)
		return 0;

	m->hw_handler_name = kstrdup(dm_shift_arg(as), GFP_KERNEL);
	request_module("scsi_dh_%s", m->hw_handler_name);
	if (scsi_dh_handler_exist(m->hw_handler_name) == 0) {
		ti->error = "unknown hardware handler type";
		ret = -EINVAL;
		goto fail;
	}

	if (hw_argc > 1) {
		char *p;
		int i, j, len = 4;

		for (i = 0; i <= hw_argc - 2; i++)
			len += strlen(as->argv[i]) + 1;
		p = m->hw_handler_params = kzalloc(len, GFP_KERNEL);
		if (!p) {
			ti->error = "memory allocation failed";
			ret = -ENOMEM;
			goto fail;
		}
		j = sprintf(p, "%d", hw_argc - 1);
		for (i = 0, p+=j+1; i <= hw_argc - 2; i++, p+=j+1)
			j = sprintf(p, "%s", as->argv[i]);
	}
	dm_consume_args(as, hw_argc - 1);

	return 0;
fail:
	kfree(m->hw_handler_name);
	m->hw_handler_name = NULL;
	return ret;
}
