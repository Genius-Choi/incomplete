static inline void inode_sb_list_del(struct inode *inode)
{
	if (!list_empty(&inode->i_sb_list)) {
		spin_lock(&inode_sb_list_lock);
		list_del_init(&inode->i_sb_list);
		spin_unlock(&inode_sb_list_lock);
	}
}
