static int orinoco_ioctl_getrid(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_point *data,
				char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	hermes_t *hw = &priv->hw;
	int rid = data->flags;
	u16 length;
	int err;
	unsigned long flags;

	/* It's a "get" function, but we don't want users to access the
	 * WEP key and other raw firmware data */
	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (rid < 0xfc00 || rid > 0xffff)
		return -EINVAL;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = hw->ops->read_ltv(hw, USER_BAP, rid, MAX_RID_LEN, &length,
				extra);
	if (err)
		goto out;

	data->length = min_t(u16, HERMES_RECLEN_TO_BYTES(length),
			     MAX_RID_LEN);

 out:
	orinoco_unlock(priv, &flags);
	return err;
}
