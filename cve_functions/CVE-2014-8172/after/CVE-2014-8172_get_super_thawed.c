struct super_block *get_super_thawed(struct block_device *bdev)
{
	while (1) {
		struct super_block *s = get_super(bdev);
		if (!s || s->s_writers.frozen == SB_UNFROZEN)
			return s;
		up_read(&s->s_umount);
		wait_event(s->s_writers.wait_unfrozen,
			   s->s_writers.frozen == SB_UNFROZEN);
		put_super(s);
	}
}
