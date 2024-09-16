static int airo_get_auth(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct airo_info *local = dev->ml_priv;
	struct iw_param *param = &wrqu->param;
	__le16 currentAuthType = local->config.authType;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_DROP_UNENCRYPTED:
		switch (currentAuthType) {
		case AUTH_SHAREDKEY:
		case AUTH_ENCRYPT:
			param->value = 1;
			break;
		default:
			param->value = 0;
			break;
		}
		break;

	case IW_AUTH_80211_AUTH_ALG:
		switch (currentAuthType) {
		case AUTH_SHAREDKEY:
			param->value = IW_AUTH_ALG_SHARED_KEY;
			break;
		case AUTH_ENCRYPT:
		default:
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
			break;
		}
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = 0;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return 0;
}
