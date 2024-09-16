static void proc_APList_on_close( struct inode *inode, struct file *file ) {
	struct proc_data *data = file->private_data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	APListRid APList_rid;
	int i;

	if ( !data->writelen ) return;

	memset( &APList_rid, 0, sizeof(APList_rid) );
	APList_rid.len = cpu_to_le16(sizeof(APList_rid));

	for( i = 0; i < 4 && data->writelen >= (i+1)*6*3; i++ ) {
		int j;
		for( j = 0; j < 6*3 && data->wbuffer[j+i*6*3]; j++ ) {
			switch(j%3) {
			case 0:
				APList_rid.ap[i][j/3]=
					hex_to_bin(data->wbuffer[j+i*6*3])<<4;
				break;
			case 1:
				APList_rid.ap[i][j/3]|=
					hex_to_bin(data->wbuffer[j+i*6*3]);
				break;
			}
		}
	}
	disable_MAC(ai, 1);
	writeAPListRid(ai, &APList_rid, 1);
	enable_MAC(ai, 1);
}
