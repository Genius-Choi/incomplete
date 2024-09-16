static void do_pf_write_done(void)
{
	if (pf_wait(pf_current, STAT_BUSY, 0, "write block", "done") & STAT_ERR) {
		pi_disconnect(pf_current->pi);
		if (pf_retries < PF_MAX_RETRIES) {
			pf_retries++;
			pi_do_claimed(pf_current->pi, do_pf_write_start);
			return;
		}
		next_request(BLK_STS_IOERR);
		return;
	}
	pi_disconnect(pf_current->pi);
	next_request(0);
}
