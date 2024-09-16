static struct inode *ext3_alloc_inode(struct super_block *sb)
{
	struct ext3_inode_info *ei;

	ei = kmem_cache_alloc(ext3_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;
	ei->i_block_alloc_info = NULL;
	ei->vfs_inode.i_version = 1;
	atomic_set(&ei->i_datasync_tid, 0);
	atomic_set(&ei->i_sync_tid, 0);
	return &ei->vfs_inode;
}
