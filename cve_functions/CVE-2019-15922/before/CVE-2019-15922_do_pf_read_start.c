static void do_pf_read_start(void)
{
	pf_busy = 1;

	if (pf_start(pf_current, ATAPI_READ_10, pf_block, pf_run)) {
		pi_disconnect(pf_current->pi);
		if (pf_retries < PF_MAX_RETRIES) {
			pf_retries++;
			pi_do_claimed(pf_current->pi, do_pf_read_start);
			return;
		}
		next_request(BLK_STS_IOERR);
		return;
	}
	pf_mask = STAT_DRQ;
	ps_set_intr(do_pf_read_drq, pf_ready, PF_TMO, nice);
}
