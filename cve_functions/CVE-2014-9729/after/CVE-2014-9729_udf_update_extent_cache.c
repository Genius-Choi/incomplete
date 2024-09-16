static void udf_update_extent_cache(struct inode *inode, loff_t estart,
				    struct extent_position *pos, int next_epos)
{
	struct udf_inode_info *iinfo = UDF_I(inode);

	spin_lock(&iinfo->i_extent_cache_lock);
	/* Invalidate previously cached extent */
	__udf_clear_extent_cache(inode);
	if (pos->bh)
		get_bh(pos->bh);
	memcpy(&iinfo->cached_extent.epos, pos,
	       sizeof(struct extent_position));
	iinfo->cached_extent.lstart = estart;
	if (next_epos)
		switch (iinfo->i_alloc_type) {
		case ICBTAG_FLAG_AD_SHORT:
			iinfo->cached_extent.epos.offset -=
			sizeof(struct short_ad);
			break;
		case ICBTAG_FLAG_AD_LONG:
			iinfo->cached_extent.epos.offset -=
			sizeof(struct long_ad);
		}
	spin_unlock(&iinfo->i_extent_cache_lock);
}
