static void __init report_hugepages(void)
{
	struct hstate *h;

	for_each_hstate(h) {
		char buf[32];
		printk(KERN_INFO "HugeTLB registered %s page size, "
				 "pre-allocated %ld pages\n",
			memfmt(buf, huge_page_size(h)),
			h->free_huge_pages);
	}
}
