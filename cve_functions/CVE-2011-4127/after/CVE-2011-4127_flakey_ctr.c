static int flakey_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	static struct dm_arg _args[] = {
		{0, UINT_MAX, "Invalid up interval"},
		{0, UINT_MAX, "Invalid down interval"},
	};

	int r;
	struct flakey_c *fc;
	unsigned long long tmpll;
	struct dm_arg_set as;
	const char *devname;

	as.argc = argc;
	as.argv = argv;

	if (argc < 4) {
		ti->error = "Invalid argument count";
		return -EINVAL;
	}

	fc = kzalloc(sizeof(*fc), GFP_KERNEL);
	if (!fc) {
		ti->error = "Cannot allocate linear context";
		return -ENOMEM;
	}
	fc->start_time = jiffies;

	devname = dm_shift_arg(&as);

	if (sscanf(dm_shift_arg(&as), "%llu", &tmpll) != 1) {
		ti->error = "Invalid device sector";
		goto bad;
	}
	fc->start = tmpll;

	r = dm_read_arg(_args, &as, &fc->up_interval, &ti->error);
	if (r)
		goto bad;

	r = dm_read_arg(_args, &as, &fc->down_interval, &ti->error);
	if (r)
		goto bad;

	if (!(fc->up_interval + fc->down_interval)) {
		ti->error = "Total (up + down) interval is zero";
		goto bad;
	}

	if (fc->up_interval + fc->down_interval < fc->up_interval) {
		ti->error = "Interval overflow";
		goto bad;
	}

	r = parse_features(&as, fc, ti);
	if (r)
		goto bad;

	if (dm_get_device(ti, devname, dm_table_get_mode(ti->table), &fc->dev)) {
		ti->error = "Device lookup failed";
		goto bad;
	}

	ti->num_flush_requests = 1;
	ti->num_discard_requests = 1;
	ti->private = fc;
	return 0;

bad:
	kfree(fc);
	return -EINVAL;
}
