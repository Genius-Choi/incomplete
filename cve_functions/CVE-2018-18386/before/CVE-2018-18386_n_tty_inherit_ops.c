void n_tty_inherit_ops(struct tty_ldisc_ops *ops)
{
	*ops = n_tty_ops;
	ops->owner = NULL;
	ops->refcount = ops->flags = 0;
}
