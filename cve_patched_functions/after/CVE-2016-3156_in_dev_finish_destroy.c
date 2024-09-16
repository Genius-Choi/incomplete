void in_dev_finish_destroy(struct in_device *idev)
{
	struct net_device *dev = idev->dev;

	WARN_ON(idev->ifa_list);
	WARN_ON(idev->mc_list);
	kfree(rcu_dereference_protected(idev->mc_hash, 1));
#ifdef NET_REFCNT_DEBUG
	pr_debug("%s: %p=%s\n", __func__, idev, dev ? dev->name : "NIL");
#endif
	dev_put(dev);
	if (!idev->dead)
		pr_err("Freeing alive in_device %p\n", idev);
	else
		kfree(idev);
}
