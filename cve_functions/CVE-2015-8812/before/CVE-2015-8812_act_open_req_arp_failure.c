static void act_open_req_arp_failure(struct t3cdev *dev, struct sk_buff *skb)
{
	printk(KERN_ERR MOD "ARP failure duing connect\n");
	kfree_skb(skb);
}
