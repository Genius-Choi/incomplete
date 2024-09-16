static int proc_wepkey_open( struct inode *inode, struct file *file )
{
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	char *ptr;
	WepKeyRid wkr;
	__le16 lastindex;
	int j=0;
	int rc;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	memset(&wkr, 0, sizeof(wkr));
	data = file->private_data;
	if ((data->rbuffer = kzalloc( 180, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}
	data->writelen = 0;
	data->maxwritelen = 80;
	if ((data->wbuffer = kzalloc( 80, GFP_KERNEL )) == NULL) {
		kfree (data->rbuffer);
		kfree (file->private_data);
		return -ENOMEM;
	}
	data->on_close = proc_wepkey_on_close;

	ptr = data->rbuffer;
	strcpy(ptr, "No wep keys\n");
	rc = readWepKeyRid(ai, &wkr, 1, 1);
	if (rc == SUCCESS) do {
		lastindex = wkr.kindex;
		if (wkr.kindex == cpu_to_le16(0xffff)) {
			j += sprintf(ptr+j, "Tx key = %d\n",
				     (int)wkr.mac[0]);
		} else {
			j += sprintf(ptr+j, "Key %d set with length = %d\n",
				     le16_to_cpu(wkr.kindex),
				     le16_to_cpu(wkr.klen));
		}
		readWepKeyRid(ai, &wkr, 0, 1);
	} while((lastindex != wkr.kindex) && (j < 180-30));

	data->readlen = strlen( data->rbuffer );
	return 0;
}
