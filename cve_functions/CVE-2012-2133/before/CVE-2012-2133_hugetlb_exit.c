static void __exit hugetlb_exit(void)
{
	struct hstate *h;

	hugetlb_unregister_all_nodes();

	for_each_hstate(h) {
		kobject_put(hstate_kobjs[h - hstates]);
	}

	kobject_put(hugepages_kobj);
}
