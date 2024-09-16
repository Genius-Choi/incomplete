static int ext3_check_descriptors(struct super_block *sb)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	int i;

	ext3_debug ("Checking group descriptors");

	for (i = 0; i < sbi->s_groups_count; i++) {
		struct ext3_group_desc *gdp = ext3_get_group_desc(sb, i, NULL);
		ext3_fsblk_t first_block = ext3_group_first_block_no(sb, i);
		ext3_fsblk_t last_block;

		if (i == sbi->s_groups_count - 1)
			last_block = le32_to_cpu(sbi->s_es->s_blocks_count) - 1;
		else
			last_block = first_block +
				(EXT3_BLOCKS_PER_GROUP(sb) - 1);

		if (le32_to_cpu(gdp->bg_block_bitmap) < first_block ||
		    le32_to_cpu(gdp->bg_block_bitmap) > last_block)
		{
			ext3_error (sb, "ext3_check_descriptors",
				    "Block bitmap for group %d"
				    " not in group (block %lu)!",
				    i, (unsigned long)
					le32_to_cpu(gdp->bg_block_bitmap));
			return 0;
		}
		if (le32_to_cpu(gdp->bg_inode_bitmap) < first_block ||
		    le32_to_cpu(gdp->bg_inode_bitmap) > last_block)
		{
			ext3_error (sb, "ext3_check_descriptors",
				    "Inode bitmap for group %d"
				    " not in group (block %lu)!",
				    i, (unsigned long)
					le32_to_cpu(gdp->bg_inode_bitmap));
			return 0;
		}
		if (le32_to_cpu(gdp->bg_inode_table) < first_block ||
		    le32_to_cpu(gdp->bg_inode_table) + sbi->s_itb_per_group - 1 >
		    last_block)
		{
			ext3_error (sb, "ext3_check_descriptors",
				    "Inode table for group %d"
				    " not in group (block %lu)!",
				    i, (unsigned long)
					le32_to_cpu(gdp->bg_inode_table));
			return 0;
		}
	}

	sbi->s_es->s_free_blocks_count=cpu_to_le32(ext3_count_free_blocks(sb));
	sbi->s_es->s_free_inodes_count=cpu_to_le32(ext3_count_free_inodes(sb));
	return 1;
}
