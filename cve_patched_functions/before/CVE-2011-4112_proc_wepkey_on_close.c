static void proc_wepkey_on_close( struct inode *inode, struct file *file ) {
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	int i, rc;
	char key[16];
	u16 index = 0;
	int j = 0;

	memset(key, 0, sizeof(key));

	data = file->private_data;
	if ( !data->writelen ) return;

	if (data->wbuffer[0] >= '0' && data->wbuffer[0] <= '3' &&
	    (data->wbuffer[1] == ' ' || data->wbuffer[1] == '\n')) {
		index = data->wbuffer[0] - '0';
		if (data->wbuffer[1] == '\n') {
			rc = set_wep_tx_idx(ai, index, 1, 1);
			if (rc < 0) {
				airo_print_err(ai->dev->name, "failed to set "
				               "WEP transmit index to %d: %d.",
				               index, rc);
			}
			return;
		}
		j = 2;
	} else {
		airo_print_err(ai->dev->name, "WepKey passed invalid key index");
		return;
	}

	for( i = 0; i < 16*3 && data->wbuffer[i+j]; i++ ) {
		switch(i%3) {
		case 0:
			key[i/3] = hex_to_bin(data->wbuffer[i+j])<<4;
			break;
		case 1:
			key[i/3] |= hex_to_bin(data->wbuffer[i+j]);
			break;
		}
	}

	rc = set_wep_key(ai, index, key, i/3, 1, 1);
	if (rc < 0) {
		airo_print_err(ai->dev->name, "failed to set WEP key at index "
		               "%d: %d.", index, rc);
	}
}
