int udf_add_aext(struct inode *inode, struct extent_position *epos,
		 struct kernel_lb_addr *eloc, uint32_t elen, int inc)
{
	int adsize;
	struct short_ad *sad = NULL;
	struct long_ad *lad = NULL;
	struct allocExtDesc *aed;
	uint8_t *ptr;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (!epos->bh)
		ptr = iinfo->i_ext.i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
	else
		ptr = epos->bh->b_data + epos->offset;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		return -EIO;

	if (epos->offset + (2 * adsize) > inode->i_sb->s_blocksize) {
		unsigned char *sptr, *dptr;
		struct buffer_head *nbh;
		int err, loffset;
		struct kernel_lb_addr obloc = epos->block;

		epos->block.logicalBlockNum = udf_new_block(inode->i_sb, NULL,
						obloc.partitionReferenceNum,
						obloc.logicalBlockNum, &err);
		if (!epos->block.logicalBlockNum)
			return -ENOSPC;
		nbh = udf_tgetblk(inode->i_sb, udf_get_lb_pblock(inode->i_sb,
								 &epos->block,
								 0));
		if (!nbh)
			return -EIO;
		lock_buffer(nbh);
		memset(nbh->b_data, 0x00, inode->i_sb->s_blocksize);
		set_buffer_uptodate(nbh);
		unlock_buffer(nbh);
		mark_buffer_dirty_inode(nbh, inode);

		aed = (struct allocExtDesc *)(nbh->b_data);
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT))
			aed->previousAllocExtLocation =
					cpu_to_le32(obloc.logicalBlockNum);
		if (epos->offset + adsize > inode->i_sb->s_blocksize) {
			loffset = epos->offset;
			aed->lengthAllocDescs = cpu_to_le32(adsize);
			sptr = ptr - adsize;
			dptr = nbh->b_data + sizeof(struct allocExtDesc);
			memcpy(dptr, sptr, adsize);
			epos->offset = sizeof(struct allocExtDesc) + adsize;
		} else {
			loffset = epos->offset + adsize;
			aed->lengthAllocDescs = cpu_to_le32(0);
			sptr = ptr;
			epos->offset = sizeof(struct allocExtDesc);

			if (epos->bh) {
				aed = (struct allocExtDesc *)epos->bh->b_data;
				le32_add_cpu(&aed->lengthAllocDescs, adsize);
			} else {
				iinfo->i_lenAlloc += adsize;
				mark_inode_dirty(inode);
			}
		}
		if (UDF_SB(inode->i_sb)->s_udfrev >= 0x0200)
			udf_new_tag(nbh->b_data, TAG_IDENT_AED, 3, 1,
				    epos->block.logicalBlockNum, sizeof(struct tag));
		else
			udf_new_tag(nbh->b_data, TAG_IDENT_AED, 2, 1,
				    epos->block.logicalBlockNum, sizeof(struct tag));
		switch (iinfo->i_alloc_type) {
		case ICBTAG_FLAG_AD_SHORT:
			sad = (struct short_ad *)sptr;
			sad->extLength = cpu_to_le32(EXT_NEXT_EXTENT_ALLOCDECS |
						     inode->i_sb->s_blocksize);
			sad->extPosition =
				cpu_to_le32(epos->block.logicalBlockNum);
			break;
		case ICBTAG_FLAG_AD_LONG:
			lad = (struct long_ad *)sptr;
			lad->extLength = cpu_to_le32(EXT_NEXT_EXTENT_ALLOCDECS |
						     inode->i_sb->s_blocksize);
			lad->extLocation = cpu_to_lelb(epos->block);
			memset(lad->impUse, 0x00, sizeof(lad->impUse));
			break;
		}
		if (epos->bh) {
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(epos->bh->b_data, loffset);
			else
				udf_update_tag(epos->bh->b_data,
						sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(epos->bh, inode);
			brelse(epos->bh);
		} else {
			mark_inode_dirty(inode);
		}
		epos->bh = nbh;
	}

	udf_write_aext(inode, epos, eloc, elen, inc);

	if (!epos->bh) {
		iinfo->i_lenAlloc += adsize;
		mark_inode_dirty(inode);
	} else {
		aed = (struct allocExtDesc *)epos->bh->b_data;
		le32_add_cpu(&aed->lengthAllocDescs, adsize);
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
				UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
			udf_update_tag(epos->bh->b_data,
					epos->offset + (inc ? 0 : adsize));
		else
			udf_update_tag(epos->bh->b_data,
					sizeof(struct allocExtDesc));
		mark_buffer_dirty_inode(epos->bh, inode);
	}

	return 0;
}
