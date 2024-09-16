static void do_pf_write_start(void)
{
	pf_busy = 1;

	if (pf_start(pf_current, ATAPI_WRITE_10, pf_block, pf_run)) {
		pi_disconnect(pf_current->pi);
		if (pf_retries < PF_MAX_RETRIES) {
			pf_retries++;
			pi_do_claimed(pf_current->pi, do_pf_write_start);
			return;
		}
		next_request(BLK_STS_IOERR);
		return;
	}

	while (1) {
		if (pf_wait(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "write block", "data wait") & STAT_ERR) {
			pi_disconnect(pf_current->pi);
			if (pf_retries < PF_MAX_RETRIES) {
				pf_retries++;
				pi_do_claimed(pf_current->pi, do_pf_write_start);
				return;
			}
			next_request(BLK_STS_IOERR);
			return;
		}
		pi_write_block(pf_current->pi, pf_buf, 512);
		if (pf_next_buf())
			break;
	}
	pf_mask = 0;
	ps_set_intr(do_pf_write_done, pf_ready, PF_TMO, nice);
}
