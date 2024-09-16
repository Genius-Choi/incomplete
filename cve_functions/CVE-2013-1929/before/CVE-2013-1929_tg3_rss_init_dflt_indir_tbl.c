static void tg3_rss_init_dflt_indir_tbl(struct tg3 *tp, u32 qcnt)
{
	int i;

	for (i = 0; i < TG3_RSS_INDIR_TBL_SIZE; i++)
		tp->rss_ind_tbl[i] = ethtool_rxfh_indir_default(i, qcnt);
}
