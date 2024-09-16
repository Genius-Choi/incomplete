static int set_next_request(void)
{
	struct pcd_unit *cd;
	int old_pos = pcd_queue;

	do {
		cd = &pcd[pcd_queue];
		if (++pcd_queue == PCD_UNITS)
			pcd_queue = 0;
		if (cd->present && !list_empty(&cd->rq_list)) {
			pcd_req = list_first_entry(&cd->rq_list, struct request,
							queuelist);
			list_del_init(&pcd_req->queuelist);
			blk_mq_start_request(pcd_req);
			break;
		}
	} while (pcd_queue != old_pos);

	return pcd_req != NULL;
}
