static void do_pf_read_drq(void)
{
	while (1) {
		if (pf_wait(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "read block", "completion") & STAT_ERR) {
			pi_disconnect(pf_current->pi);
			if (pf_retries < PF_MAX_RETRIES) {
				pf_req_sense(pf_current, 0);
				pf_retries++;
				pi_do_claimed(pf_current->pi, do_pf_read_start);
				return;
			}
			next_request(BLK_STS_IOERR);
			return;
		}
		pi_read_block(pf_current->pi, pf_buf, 512);
		if (pf_next_buf())
			break;
	}
	pi_disconnect(pf_current->pi);
	next_request(0);
}
