static int airo_get_sens(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_param *vwrq,
			 char *extra)
{
	struct airo_info *local = dev->ml_priv;

	readConfigRid(local, 1);
	vwrq->value = le16_to_cpu(local->config.rssiThreshold);
	vwrq->disabled = (vwrq->value == 0);
	vwrq->fixed = 1;

	return 0;
}
