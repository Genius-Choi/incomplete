void ip_rt_multicast_event(struct in_device *in_dev)
{
	rt_cache_flush(dev_net(in_dev->dev));
}
