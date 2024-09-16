void free_xenballooned_pages(int nr_pages, struct page **pages)
{
	int i;

	mutex_lock(&balloon_mutex);

	for (i = 0; i < nr_pages; i++) {
		if (pages[i]) {
			__SetPageOffline(pages[i]);
			balloon_append(pages[i]);
		}
	}

	balloon_stats.target_unpopulated -= nr_pages;

	/* The balloon may be too large now. Shrink it if needed. */
	if (current_credit())
		schedule_delayed_work(&balloon_worker, 0);

	mutex_unlock(&balloon_mutex);
}
