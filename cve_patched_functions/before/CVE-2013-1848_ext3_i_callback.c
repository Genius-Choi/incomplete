static void ext3_i_callback(struct rcu_head *head)
{
	struct inode *inode = container_of(head, struct inode, i_rcu);
	kmem_cache_free(ext3_inode_cachep, EXT3_I(inode));
}
