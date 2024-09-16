static int trunc_end(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *dibh;
	int error;

	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		return error;

	down_write(&ip->i_rw_mutex);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out;

	if (!i_size_read(&ip->i_inode)) {
		ip->i_height = 0;
		ip->i_goal = ip->i_no_addr;
		gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode));
	}
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = CURRENT_TIME;
	ip->i_diskflags &= ~GFS2_DIF_TRUNC_IN_PROG;

	gfs2_trans_add_bh(ip->i_gl, dibh, 1);
	gfs2_dinode_out(ip, dibh->b_data);
	brelse(dibh);

out:
	up_write(&ip->i_rw_mutex);
	gfs2_trans_end(sdp);
	return error;
}
