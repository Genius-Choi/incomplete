static struct inode *proc_sys_make_inode(struct super_block *sb,
		struct ctl_table_header *head, struct ctl_table *table)
{
	struct ctl_table_root *root = head->root;
	struct inode *inode;
	struct proc_inode *ei;

	inode = new_inode(sb);
	if (!inode)
		goto out;

	inode->i_ino = get_next_ino();

	sysctl_head_get(head);
	ei = PROC_I(inode);
	ei->sysctl = head;
	ei->sysctl_entry = table;

	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_mode = table->mode;
	if (!S_ISDIR(table->mode)) {
		inode->i_mode |= S_IFREG;
		inode->i_op = &proc_sys_inode_operations;
		inode->i_fop = &proc_sys_file_operations;
	} else {
		inode->i_mode |= S_IFDIR;
		inode->i_op = &proc_sys_dir_operations;
		inode->i_fop = &proc_sys_dir_file_operations;
		if (is_empty_dir(head))
			make_empty_dir_inode(inode);
	}

	if (root->set_ownership)
		root->set_ownership(head, table, &inode->i_uid, &inode->i_gid);

out:
	return inode;
}
