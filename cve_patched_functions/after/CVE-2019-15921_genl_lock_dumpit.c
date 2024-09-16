static int genl_lock_dumpit(struct sk_buff *skb, struct netlink_callback *cb)
{
	/* our ops are always const - netlink API doesn't propagate that */
	const struct genl_ops *ops = cb->data;
	int rc;

	genl_lock();
	rc = ops->dumpit(skb, cb);
	genl_unlock();
	return rc;
}
