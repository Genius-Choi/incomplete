static int test_bdev_super(struct super_block *s, void *data)
{
	return (void *)s->s_bdev == data;
}
