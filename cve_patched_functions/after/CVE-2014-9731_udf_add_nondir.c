static int udf_add_nondir(struct dentry *dentry, struct inode *inode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	struct inode *dir = dentry->d_parent->d_inode;
	struct udf_fileident_bh fibh;
	struct fileIdentDesc cfi, *fi;
	int err;

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	if (unlikely(!fi)) {
		inode_dec_link_count(inode);
		unlock_new_inode(inode);
		iput(inode);
		return err;
	}
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(iinfo->i_location);
	*(__le32 *)((struct allocDescImpUse *)cfi.icb.impUse)->impUse =
		cpu_to_le32(iinfo->i_unique & 0x00000000FFFFFFFFUL);
	udf_write_fi(dir, &cfi, fi, &fibh, NULL, NULL);
	if (UDF_I(dir)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		mark_inode_dirty(dir);
	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);
	unlock_new_inode(inode);
	d_instantiate(dentry, inode);

	return 0;
}
