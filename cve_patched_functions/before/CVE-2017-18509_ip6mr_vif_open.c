static int ip6mr_vif_open(struct inode *inode, struct file *file)
{
	return seq_open_net(inode, file, &ip6mr_vif_seq_ops,
			    sizeof(struct ipmr_vif_iter));
}
