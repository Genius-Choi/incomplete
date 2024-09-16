static void macvtap_dellink(struct net_device *dev,
			    struct list_head *head)
{
	macvtap_del_queues(dev);
	macvlan_dellink(dev, head);
}
