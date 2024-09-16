static void find_metapath(const struct gfs2_sbd *sdp, u64 block,
			  struct metapath *mp, unsigned int height)
{
	unsigned int i;

	for (i = height; i--;)
		mp->mp_list[i] = do_div(block, sdp->sd_inptrs);

}
