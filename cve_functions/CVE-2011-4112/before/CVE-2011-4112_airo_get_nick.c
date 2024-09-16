static int airo_get_nick(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *dwrq,
			 char *extra)
{
	struct airo_info *local = dev->ml_priv;

	readConfigRid(local, 1);
	strncpy(extra, local->config.nodeName, 16);
	extra[16] = '\0';
	dwrq->length = strlen(extra);

	return 0;
}
