grace_disallows_io(struct net *net, struct inode *inode)
{
	return opens_in_grace(net) && mandatory_lock(inode);
}
