static int udf_load_vrs(struct super_block *sb, struct udf_options *uopt,
			int silent, struct kernel_lb_addr *fileset)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	loff_t nsr_off;

	if (!sb_set_blocksize(sb, uopt->blocksize)) {
		if (!silent)
			udf_warn(sb, "Bad block size\n");
		return 0;
	}
	sbi->s_last_block = uopt->lastblock;
	if (!uopt->novrs) {
		/* Check that it is NSR02 compliant */
		nsr_off = udf_check_vsd(sb);
		if (!nsr_off) {
			if (!silent)
				udf_warn(sb, "No VRS found\n");
			return 0;
		}
		if (nsr_off == -1)
			udf_debug("Failed to read byte 32768. Assuming open disc. Skipping validity check\n");
		if (!sbi->s_last_block)
			sbi->s_last_block = udf_get_last_block(sb);
	} else {
		udf_debug("Validity check skipped because of novrs option\n");
	}

	/* Look for anchor block and load Volume Descriptor Sequence */
	sbi->s_anchor = uopt->anchor;
	if (!udf_find_anchor(sb, fileset)) {
		if (!silent)
			udf_warn(sb, "No anchor found\n");
		return 0;
	}
	return 1;
}
