static int orinoco_ioctl_getpreamble(struct net_device *dev,
				     struct iw_request_info *info,
				     void *wrqu,
				     char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int *val = (int *) extra;

	if (!priv->has_preamble)
		return -EOPNOTSUPP;

	*val = priv->preamble;
	return 0;
}
