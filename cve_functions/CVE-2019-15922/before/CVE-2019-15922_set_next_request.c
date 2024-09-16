static int set_next_request(void)
{
	struct pf_unit *pf;
	int old_pos = pf_queue;

	do {
		pf = &units[pf_queue];
		if (++pf_queue == PF_UNITS)
			pf_queue = 0;
		if (pf->present && !list_empty(&pf->rq_list)) {
			pf_req = list_first_entry(&pf->rq_list, struct request,
							queuelist);
			list_del_init(&pf_req->queuelist);
			blk_mq_start_request(pf_req);
			break;
		}
	} while (pf_queue != old_pos);

	return pf_req != NULL;
}
