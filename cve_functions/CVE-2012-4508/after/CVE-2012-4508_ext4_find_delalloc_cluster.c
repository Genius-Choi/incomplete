int ext4_find_delalloc_cluster(struct inode *inode, ext4_lblk_t lblk,
			       int search_hint_reverse)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t lblk_start, lblk_end;
	lblk_start = lblk & (~(sbi->s_cluster_ratio - 1));
	lblk_end = lblk_start + sbi->s_cluster_ratio - 1;

	return ext4_find_delalloc_range(inode, lblk_start, lblk_end,
					search_hint_reverse);
}
