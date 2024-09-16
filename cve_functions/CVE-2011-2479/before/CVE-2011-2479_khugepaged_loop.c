static void khugepaged_loop(void)
{
	struct page *hpage;

#ifdef CONFIG_NUMA
	hpage = NULL;
#endif
	while (likely(khugepaged_enabled())) {
#ifndef CONFIG_NUMA
		hpage = khugepaged_alloc_hugepage();
		if (unlikely(!hpage)) {
			count_vm_event(THP_COLLAPSE_ALLOC_FAILED);
			break;
		}
		count_vm_event(THP_COLLAPSE_ALLOC);
#else
		if (IS_ERR(hpage)) {
			khugepaged_alloc_sleep();
			hpage = NULL;
		}
#endif

		khugepaged_do_scan(&hpage);
#ifndef CONFIG_NUMA
		if (hpage)
			put_page(hpage);
#endif
		try_to_freeze();
		if (unlikely(kthread_should_stop()))
			break;
		if (khugepaged_has_work()) {
			DEFINE_WAIT(wait);
			if (!khugepaged_scan_sleep_millisecs)
				continue;
			add_wait_queue(&khugepaged_wait, &wait);
			schedule_timeout_interruptible(
				msecs_to_jiffies(
					khugepaged_scan_sleep_millisecs));
			remove_wait_queue(&khugepaged_wait, &wait);
		} else if (khugepaged_enabled())
			wait_event_freezable(khugepaged_wait,
					     khugepaged_wait_event());
	}
}
