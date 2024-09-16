static void netlink_consume_callback(struct netlink_callback *cb)
{
	consume_skb(cb->skb);
	kfree(cb);
}
