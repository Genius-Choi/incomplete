int hostap_set_roaming(local_info_t *local)
{
	u16 val;

	switch (local->host_roaming) {
	case 1:
		val = HFA384X_ROAMING_HOST;
		break;
	case 2:
		val = HFA384X_ROAMING_DISABLED;
		break;
	case 0:
	default:
		val = HFA384X_ROAMING_FIRMWARE;
		break;
	}

	return hostap_set_word(local->dev, HFA384X_RID_CNFROAMINGMODE, val);
}
