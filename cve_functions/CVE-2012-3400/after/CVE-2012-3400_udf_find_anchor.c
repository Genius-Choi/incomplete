static int udf_find_anchor(struct super_block *sb,
			   struct kernel_lb_addr *fileset)
{
	sector_t lastblock;
	struct udf_sb_info *sbi = UDF_SB(sb);

	lastblock = udf_scan_anchors(sb, sbi->s_last_block, fileset);
	if (lastblock)
		goto out;

	/* No anchor found? Try VARCONV conversion of block numbers */
	UDF_SET_FLAG(sb, UDF_FLAG_VARCONV);
	/* Firstly, we try to not convert number of the last block */
	lastblock = udf_scan_anchors(sb,
				udf_variable_to_fixed(sbi->s_last_block),
				fileset);
	if (lastblock)
		goto out;

	/* Secondly, we try with converted number of the last block */
	lastblock = udf_scan_anchors(sb, sbi->s_last_block, fileset);
	if (!lastblock) {
		/* VARCONV didn't help. Clear it. */
		UDF_CLEAR_FLAG(sb, UDF_FLAG_VARCONV);
		return 0;
	}
out:
	sbi->s_last_block = lastblock;
	return 1;
}
