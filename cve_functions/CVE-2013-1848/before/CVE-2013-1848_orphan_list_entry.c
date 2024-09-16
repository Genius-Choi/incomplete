static inline struct inode *orphan_list_entry(struct list_head *l)
{
	return &list_entry(l, struct ext3_inode_info, i_orphan)->vfs_inode;
}
