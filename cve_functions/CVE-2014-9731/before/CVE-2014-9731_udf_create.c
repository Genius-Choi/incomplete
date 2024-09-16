static int udf_create(struct inode *dir, struct dentry *dentry, umode_t mode,
		      bool excl)
{
	struct inode *inode = udf_new_inode(dir, mode);

	if (IS_ERR(inode))
		return PTR_ERR(inode);

	if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		inode->i_data.a_ops = &udf_adinicb_aops;
	else
		inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_file_inode_operations;
	inode->i_fop = &udf_file_operations;
	mark_inode_dirty(inode);

	return udf_add_nondir(dentry, inode);
}
