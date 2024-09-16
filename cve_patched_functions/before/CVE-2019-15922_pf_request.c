static void pf_request(void)
{
	if (pf_busy)
		return;
repeat:
	if (!pf_req && !set_next_request())
		return;

	pf_current = pf_req->rq_disk->private_data;
	pf_block = blk_rq_pos(pf_req);
	pf_run = blk_rq_sectors(pf_req);
	pf_count = blk_rq_cur_sectors(pf_req);

	if (pf_block + pf_count > get_capacity(pf_req->rq_disk)) {
		pf_end_request(BLK_STS_IOERR);
		goto repeat;
	}

	pf_cmd = rq_data_dir(pf_req);
	pf_buf = bio_data(pf_req->bio);
	pf_retries = 0;

	pf_busy = 1;
	if (pf_cmd == READ)
		pi_do_claimed(pf_current->pi, do_pf_read);
	else if (pf_cmd == WRITE)
		pi_do_claimed(pf_current->pi, do_pf_write);
	else {
		pf_busy = 0;
		pf_end_request(BLK_STS_IOERR);
		goto repeat;
	}
}
