int prism2_update_comms_qual(struct net_device *dev)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int ret = 0;
	struct hfa384x_comms_quality sq;

	iface = netdev_priv(dev);
	local = iface->local;
	if (!local->sta_fw_ver)
		ret = -1;
	else if (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1)) {
		if (local->func->get_rid(local->dev,
					 HFA384X_RID_DBMCOMMSQUALITY,
					 &sq, sizeof(sq), 1) >= 0) {
			local->comms_qual = (s16) le16_to_cpu(sq.comm_qual);
			local->avg_signal = (s16) le16_to_cpu(sq.signal_level);
			local->avg_noise = (s16) le16_to_cpu(sq.noise_level);
			local->last_comms_qual_update = jiffies;
		} else
			ret = -1;
	} else {
		if (local->func->get_rid(local->dev, HFA384X_RID_COMMSQUALITY,
					 &sq, sizeof(sq), 1) >= 0) {
			local->comms_qual = le16_to_cpu(sq.comm_qual);
			local->avg_signal = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.signal_level));
			local->avg_noise = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.noise_level));
			local->last_comms_qual_update = jiffies;
		} else
			ret = -1;
	}

	return ret;
}
