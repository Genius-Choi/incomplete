static void ext3_destroy_inode(struct inode *inode)
{
	if (!list_empty(&(EXT3_I(inode)->i_orphan))) {
		printk("EXT3 Inode %p: orphan list check failed!\n",
			EXT3_I(inode));
		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 16, 4,
				EXT3_I(inode), sizeof(struct ext3_inode_info),
				false);
		dump_stack();
	}
	call_rcu(&inode->i_rcu, ext3_i_callback);
}
