static int proc_status_open(struct inode *inode, struct file *file)
{
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *apriv = dev->ml_priv;
	CapabilityRid cap_rid;
	StatusRid status_rid;
	u16 mode;
	int i;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	data = file->private_data;
	if ((data->rbuffer = kmalloc( 2048, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}

	readStatusRid(apriv, &status_rid, 1);
	readCapabilityRid(apriv, &cap_rid, 1);

	mode = le16_to_cpu(status_rid.mode);

        i = sprintf(data->rbuffer, "Status: %s%s%s%s%s%s%s%s%s\n",
                    mode & 1 ? "CFG ": "",
                    mode & 2 ? "ACT ": "",
                    mode & 0x10 ? "SYN ": "",
                    mode & 0x20 ? "LNK ": "",
                    mode & 0x40 ? "LEAP ": "",
                    mode & 0x80 ? "PRIV ": "",
                    mode & 0x100 ? "KEY ": "",
                    mode & 0x200 ? "WEP ": "",
                    mode & 0x8000 ? "ERR ": "");
	sprintf( data->rbuffer+i, "Mode: %x\n"
		 "Signal Strength: %d\n"
		 "Signal Quality: %d\n"
		 "SSID: %-.*s\n"
		 "AP: %-.16s\n"
		 "Freq: %d\n"
		 "BitRate: %dmbs\n"
		 "Driver Version: %s\n"
		 "Device: %s\nManufacturer: %s\nFirmware Version: %s\n"
		 "Radio type: %x\nCountry: %x\nHardware Version: %x\n"
		 "Software Version: %x\nSoftware Subversion: %x\n"
		 "Boot block version: %x\n",
		 le16_to_cpu(status_rid.mode),
		 le16_to_cpu(status_rid.normalizedSignalStrength),
		 le16_to_cpu(status_rid.signalQuality),
		 le16_to_cpu(status_rid.SSIDlen),
		 status_rid.SSID,
		 status_rid.apName,
		 le16_to_cpu(status_rid.channel),
		 le16_to_cpu(status_rid.currentXmitRate) / 2,
		 version,
		 cap_rid.prodName,
		 cap_rid.manName,
		 cap_rid.prodVer,
		 le16_to_cpu(cap_rid.radioType),
		 le16_to_cpu(cap_rid.country),
		 le16_to_cpu(cap_rid.hardVer),
		 le16_to_cpu(cap_rid.softVer),
		 le16_to_cpu(cap_rid.softSubVer),
		 le16_to_cpu(cap_rid.bootBlockVer));
	data->readlen = strlen( data->rbuffer );
	return 0;
}
