static void pf_end_request(blk_status_t err)
{
	if (!pf_req)
		return;
	if (!blk_update_request(pf_req, err, blk_rq_cur_bytes(pf_req))) {
		__blk_mq_end_request(pf_req, err);
		pf_req = NULL;
	}
}
