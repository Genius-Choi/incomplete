static int alloc_fresh_huge_page(struct hstate *h, nodemask_t *nodes_allowed)
{
	struct page *page;
	int start_nid;
	int next_nid;
	int ret = 0;

	start_nid = hstate_next_node_to_alloc(h, nodes_allowed);
	next_nid = start_nid;

	do {
		page = alloc_fresh_huge_page_node(h, next_nid);
		if (page) {
			ret = 1;
			break;
		}
		next_nid = hstate_next_node_to_alloc(h, nodes_allowed);
	} while (next_nid != start_nid);

	if (ret)
		count_vm_event(HTLB_BUDDY_PGALLOC);
	else
		count_vm_event(HTLB_BUDDY_PGALLOC_FAIL);

	return ret;
}
