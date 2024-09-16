static int udf_load_vat(struct super_block *sb, int p_index, int type1_index)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map = &sbi->s_partmaps[p_index];
	struct buffer_head *bh = NULL;
	struct udf_inode_info *vati;
	uint32_t pos;
	struct virtualAllocationTable20 *vat20;
	sector_t blocks = sb->s_bdev->bd_inode->i_size >> sb->s_blocksize_bits;

	udf_find_vat_block(sb, p_index, type1_index, sbi->s_last_block);
	if (!sbi->s_vat_inode &&
	    sbi->s_last_block != blocks - 1) {
		pr_notice("Failed to read VAT inode from the last recorded block (%lu), retrying with the last block of the device (%lu).\n",
			  (unsigned long)sbi->s_last_block,
			  (unsigned long)blocks - 1);
		udf_find_vat_block(sb, p_index, type1_index, blocks - 1);
	}
	if (!sbi->s_vat_inode)
		return 1;

	if (map->s_partition_type == UDF_VIRTUAL_MAP15) {
		map->s_type_specific.s_virtual.s_start_offset = 0;
		map->s_type_specific.s_virtual.s_num_entries =
			(sbi->s_vat_inode->i_size - 36) >> 2;
	} else if (map->s_partition_type == UDF_VIRTUAL_MAP20) {
		vati = UDF_I(sbi->s_vat_inode);
		if (vati->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
			pos = udf_block_map(sbi->s_vat_inode, 0);
			bh = sb_bread(sb, pos);
			if (!bh)
				return 1;
			vat20 = (struct virtualAllocationTable20 *)bh->b_data;
		} else {
			vat20 = (struct virtualAllocationTable20 *)
							vati->i_ext.i_data;
		}

		map->s_type_specific.s_virtual.s_start_offset =
			le16_to_cpu(vat20->lengthHeader);
		map->s_type_specific.s_virtual.s_num_entries =
			(sbi->s_vat_inode->i_size -
				map->s_type_specific.s_virtual.
					s_start_offset) >> 2;
		brelse(bh);
	}
	return 0;
}
