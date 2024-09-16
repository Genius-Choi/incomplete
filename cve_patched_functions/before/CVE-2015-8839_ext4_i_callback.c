static void ext4_i_callback(struct rcu_head *head)
{
	struct inode *inode = container_of(head, struct inode, i_rcu);
	kmem_cache_free(ext4_inode_cachep, EXT4_I(inode));
}
