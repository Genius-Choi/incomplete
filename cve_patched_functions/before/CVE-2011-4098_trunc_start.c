static int trunc_start(struct inode *inode, u64 oldsize, u64 newsize)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct address_space *mapping = inode->i_mapping;
	struct buffer_head *dibh;
	int journaled = gfs2_is_jdata(ip);
	int error;

	error = gfs2_trans_begin(sdp,
				 RES_DINODE + (journaled ? RES_JDATA : 0), 0);
	if (error)
		return error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out;

	gfs2_trans_add_bh(ip->i_gl, dibh, 1);

	if (gfs2_is_stuffed(ip)) {
		gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode) + newsize);
	} else {
		if (newsize & (u64)(sdp->sd_sb.sb_bsize - 1)) {
			error = gfs2_block_truncate_page(mapping, newsize);
			if (error)
				goto out_brelse;
		}
		ip->i_diskflags |= GFS2_DIF_TRUNC_IN_PROG;
	}

	i_size_write(inode, newsize);
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = CURRENT_TIME;
	gfs2_dinode_out(ip, dibh->b_data);

	truncate_pagecache(inode, oldsize, newsize);
out_brelse:
	brelse(dibh);
out:
	gfs2_trans_end(sdp);
	return error;
}
