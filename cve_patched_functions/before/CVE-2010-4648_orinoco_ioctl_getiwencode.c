static int orinoco_ioctl_getiwencode(struct net_device *dev,
				     struct iw_request_info *info,
				     struct iw_point *erq,
				     char *keybuf)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int index = (erq->flags & IW_ENCODE_INDEX) - 1;
	unsigned long flags;

	if (!priv->has_wep)
		return -EOPNOTSUPP;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	if ((index < 0) || (index >= ORINOCO_MAX_KEYS))
		index = priv->tx_key;

	erq->flags = 0;
	if (!priv->encode_alg)
		erq->flags |= IW_ENCODE_DISABLED;
	erq->flags |= index + 1;

	if (priv->wep_restrict)
		erq->flags |= IW_ENCODE_RESTRICTED;
	else
		erq->flags |= IW_ENCODE_OPEN;

	erq->length = priv->keys[index].key_len;

	memcpy(keybuf, priv->keys[index].key, erq->length);

	orinoco_unlock(priv, &flags);
	return 0;
}
