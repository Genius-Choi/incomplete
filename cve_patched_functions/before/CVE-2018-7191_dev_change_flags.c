int dev_change_flags(struct net_device *dev, unsigned int flags)
{
	int ret;
	unsigned int changes, old_flags = dev->flags, old_gflags = dev->gflags;

	ret = __dev_change_flags(dev, flags);
	if (ret < 0)
		return ret;

	changes = (old_flags ^ dev->flags) | (old_gflags ^ dev->gflags);
	__dev_notify_flags(dev, old_flags, changes);
	return ret;
}
