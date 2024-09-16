queue_pages_range(struct mm_struct *mm, unsigned long start, unsigned long end,
		nodemask_t *nodes, unsigned long flags,
		struct list_head *pagelist)
{
	struct queue_pages qp = {
		.pagelist = pagelist,
		.flags = flags,
		.nmask = nodes,
		.prev = NULL,
	};
	struct mm_walk queue_pages_walk = {
		.hugetlb_entry = queue_pages_hugetlb,
		.pmd_entry = queue_pages_pte_range,
		.test_walk = queue_pages_test_walk,
		.mm = mm,
		.private = &qp,
	};

	return walk_page_range(start, end, &queue_pages_walk);
}
