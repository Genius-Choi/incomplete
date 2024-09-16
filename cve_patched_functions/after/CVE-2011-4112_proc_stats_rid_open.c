static int proc_stats_rid_open( struct inode *inode,
				struct file *file,
				u16 rid )
{
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *apriv = dev->ml_priv;
	StatsRid stats;
	int i, j;
	__le32 *vals = stats.vals;
	int len;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	data = file->private_data;
	if ((data->rbuffer = kmalloc( 4096, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}

	readStatsRid(apriv, &stats, rid, 1);
	len = le16_to_cpu(stats.len);

        j = 0;
	for(i=0; statsLabels[i]!=(char *)-1 && i*4<len; i++) {
		if (!statsLabels[i]) continue;
		if (j+strlen(statsLabels[i])+16>4096) {
			airo_print_warn(apriv->dev->name,
			       "Potentially disastrous buffer overflow averted!");
			break;
		}
		j+=sprintf(data->rbuffer+j, "%s: %u\n", statsLabels[i],
				le32_to_cpu(vals[i]));
	}
	if (i*4 >= len) {
		airo_print_warn(apriv->dev->name, "Got a short rid");
	}
	data->readlen = j;
	return 0;
}
