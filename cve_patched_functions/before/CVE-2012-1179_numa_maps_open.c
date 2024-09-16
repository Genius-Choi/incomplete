static int numa_maps_open(struct inode *inode, struct file *file)
{
	struct numa_maps_private *priv;
	int ret = -ENOMEM;
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv) {
		priv->proc_maps.pid = proc_pid(inode);
		ret = seq_open(file, &proc_pid_numa_maps_op);
		if (!ret) {
			struct seq_file *m = file->private_data;
			m->private = priv;
		} else {
			kfree(priv);
		}
	}
	return ret;
}
