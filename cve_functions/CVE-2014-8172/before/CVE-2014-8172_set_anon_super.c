int set_anon_super(struct super_block *s, void *data)
{
	int error = get_anon_bdev(&s->s_dev);
	if (!error)
		s->s_bdi = &noop_backing_dev_info;
	return error;
}
