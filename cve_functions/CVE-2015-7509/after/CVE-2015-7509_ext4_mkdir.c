static int ext4_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	handle_t *handle;
	struct inode *inode;
	struct buffer_head *dir_block = NULL;
	struct ext4_dir_entry_2 *de;
	struct ext4_dir_entry_tail *t;
	unsigned int blocksize = dir->i_sb->s_blocksize;
	int csum_size = 0;
	int err, retries = 0;

	if (EXT4_HAS_RO_COMPAT_FEATURE(dir->i_sb,
				       EXT4_FEATURE_RO_COMPAT_METADATA_CSUM))
		csum_size = sizeof(struct ext4_dir_entry_tail);

	if (EXT4_DIR_LINK_MAX(dir))
		return -EMLINK;

	dquot_initialize(dir);

retry:
	handle = ext4_journal_start(dir, EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
					EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3 +
					EXT4_MAXQUOTAS_INIT_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

	inode = ext4_new_inode(handle, dir, S_IFDIR | mode,
			       &dentry->d_name, 0, NULL);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_stop;

	inode->i_op = &ext4_dir_inode_operations;
	inode->i_fop = &ext4_dir_operations;
	inode->i_size = EXT4_I(inode)->i_disksize = inode->i_sb->s_blocksize;
	dir_block = ext4_bread(handle, inode, 0, 1, &err);
	if (!dir_block)
		goto out_clear_inode;
	BUFFER_TRACE(dir_block, "get_write_access");
	err = ext4_journal_get_write_access(handle, dir_block);
	if (err)
		goto out_clear_inode;
	de = (struct ext4_dir_entry_2 *) dir_block->b_data;
	de->inode = cpu_to_le32(inode->i_ino);
	de->name_len = 1;
	de->rec_len = ext4_rec_len_to_disk(EXT4_DIR_REC_LEN(de->name_len),
					   blocksize);
	strcpy(de->name, ".");
	ext4_set_de_type(dir->i_sb, de, S_IFDIR);
	de = ext4_next_entry(de, blocksize);
	de->inode = cpu_to_le32(dir->i_ino);
	de->rec_len = ext4_rec_len_to_disk(blocksize -
					   (csum_size + EXT4_DIR_REC_LEN(1)),
					   blocksize);
	de->name_len = 2;
	strcpy(de->name, "..");
	ext4_set_de_type(dir->i_sb, de, S_IFDIR);
	set_nlink(inode, 2);

	if (csum_size) {
		t = EXT4_DIRENT_TAIL(dir_block->b_data, blocksize);
		initialize_dirent_tail(t, blocksize);
	}

	BUFFER_TRACE(dir_block, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_dirent_node(handle, inode, dir_block);
	if (err)
		goto out_clear_inode;
	set_buffer_verified(dir_block);
	err = ext4_mark_inode_dirty(handle, inode);
	if (!err)
		err = ext4_add_entry(handle, dentry, inode);
	if (err) {
out_clear_inode:
		clear_nlink(inode);
		unlock_new_inode(inode);
		ext4_mark_inode_dirty(handle, inode);
		iput(inode);
		goto out_stop;
	}
	ext4_inc_count(handle, dir);
	ext4_update_dx_flag(dir);
	err = ext4_mark_inode_dirty(handle, dir);
	if (err)
		goto out_clear_inode;
	unlock_new_inode(inode);
	d_instantiate(dentry, inode);
out_stop:
	brelse(dir_block);
	ext4_journal_stop(handle);
	if (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}
