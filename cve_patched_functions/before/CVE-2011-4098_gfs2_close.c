static int gfs2_close(struct inode *inode, struct file *file)
{
	struct gfs2_sbd *sdp = inode->i_sb->s_fs_info;
	struct gfs2_file *fp;

	fp = file->private_data;
	file->private_data = NULL;

	if (gfs2_assert_warn(sdp, fp))
		return -EIO;

	kfree(fp);

	return 0;
}
