static int proc_config_open(struct inode *inode, struct file *file)
{
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	int i;
	__le16 mode;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	data = file->private_data;
	if ((data->rbuffer = kmalloc( 2048, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}
	if ((data->wbuffer = kzalloc( 2048, GFP_KERNEL )) == NULL) {
		kfree (data->rbuffer);
		kfree (file->private_data);
		return -ENOMEM;
	}
	data->maxwritelen = 2048;
	data->on_close = proc_config_on_close;

	readConfigRid(ai, 1);

	mode = ai->config.opmode & MODE_CFG_MASK;
	i = sprintf( data->rbuffer,
		     "Mode: %s\n"
		     "Radio: %s\n"
		     "NodeName: %-16s\n"
		     "PowerMode: %s\n"
		     "DataRates: %d %d %d %d %d %d %d %d\n"
		     "Channel: %d\n"
		     "XmitPower: %d\n",
		     mode == MODE_STA_IBSS ? "adhoc" :
		     mode == MODE_STA_ESS ? get_rmode(ai->config.rmode):
		     mode == MODE_AP ? "AP" :
		     mode == MODE_AP_RPTR ? "AP RPTR" : "Error",
		     test_bit(FLAG_RADIO_OFF, &ai->flags) ? "off" : "on",
		     ai->config.nodeName,
		     ai->config.powerSaveMode == POWERSAVE_CAM ? "CAM" :
		     ai->config.powerSaveMode == POWERSAVE_PSP ? "PSP" :
		     ai->config.powerSaveMode == POWERSAVE_PSPCAM ? "PSPCAM" :
		     "Error",
		     (int)ai->config.rates[0],
		     (int)ai->config.rates[1],
		     (int)ai->config.rates[2],
		     (int)ai->config.rates[3],
		     (int)ai->config.rates[4],
		     (int)ai->config.rates[5],
		     (int)ai->config.rates[6],
		     (int)ai->config.rates[7],
		     le16_to_cpu(ai->config.channelSet),
		     le16_to_cpu(ai->config.txPower)
		);
	sprintf( data->rbuffer + i,
		 "LongRetryLimit: %d\n"
		 "ShortRetryLimit: %d\n"
		 "RTSThreshold: %d\n"
		 "TXMSDULifetime: %d\n"
		 "RXMSDULifetime: %d\n"
		 "TXDiversity: %s\n"
		 "RXDiversity: %s\n"
		 "FragThreshold: %d\n"
		 "WEP: %s\n"
		 "Modulation: %s\n"
		 "Preamble: %s\n",
		 le16_to_cpu(ai->config.longRetryLimit),
		 le16_to_cpu(ai->config.shortRetryLimit),
		 le16_to_cpu(ai->config.rtsThres),
		 le16_to_cpu(ai->config.txLifetime),
		 le16_to_cpu(ai->config.rxLifetime),
		 ai->config.txDiversity == 1 ? "left" :
		 ai->config.txDiversity == 2 ? "right" : "both",
		 ai->config.rxDiversity == 1 ? "left" :
		 ai->config.rxDiversity == 2 ? "right" : "both",
		 le16_to_cpu(ai->config.fragThresh),
		 ai->config.authType == AUTH_ENCRYPT ? "encrypt" :
		 ai->config.authType == AUTH_SHAREDKEY ? "shared" : "open",
		 ai->config.modulation == MOD_DEFAULT ? "default" :
		 ai->config.modulation == MOD_CCK ? "cck" :
		 ai->config.modulation == MOD_MOK ? "mok" : "error",
		 ai->config.preamble == PREAMBLE_AUTO ? "auto" :
		 ai->config.preamble == PREAMBLE_LONG ? "long" :
		 ai->config.preamble == PREAMBLE_SHORT ? "short" : "error"
		);
	data->readlen = strlen( data->rbuffer );
	return 0;
}
