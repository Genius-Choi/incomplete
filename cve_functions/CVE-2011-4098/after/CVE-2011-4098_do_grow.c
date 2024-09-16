static int do_grow(struct inode *inode, u64 size)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *dibh;
	struct gfs2_alloc *al = NULL;
	int error;

	if (gfs2_is_stuffed(ip) &&
	    (size > (sdp->sd_sb.sb_bsize - sizeof(struct gfs2_dinode)))) {
		al = gfs2_alloc_get(ip);
		if (al == NULL)
			return -ENOMEM;

		error = gfs2_quota_lock_check(ip);
		if (error)
			goto do_grow_alloc_put;

		al->al_requested = 1;
		error = gfs2_inplace_reserve(ip);
		if (error)
			goto do_grow_qunlock;
	}

	error = gfs2_trans_begin(sdp, RES_DINODE + RES_STATFS + RES_RG_BIT, 0);
	if (error)
		goto do_grow_release;

	if (al) {
		error = gfs2_unstuff_dinode(ip, NULL);
		if (error)
			goto do_end_trans;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto do_end_trans;

	i_size_write(inode, size);
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = CURRENT_TIME;
	gfs2_trans_add_bh(ip->i_gl, dibh, 1);
	gfs2_dinode_out(ip, dibh->b_data);
	brelse(dibh);

do_end_trans:
	gfs2_trans_end(sdp);
do_grow_release:
	if (al) {
		gfs2_inplace_release(ip);
do_grow_qunlock:
		gfs2_quota_unlock(ip);
do_grow_alloc_put:
		gfs2_alloc_put(ip);
	}
	return error;
}
