void __exit rose_loopback_clear(void)
{
	struct sk_buff *skb;

	del_timer(&loopback_timer);

	while ((skb = skb_dequeue(&loopback_queue)) != NULL) {
		skb->sk = NULL;
		kfree_skb(skb);
	}
}
