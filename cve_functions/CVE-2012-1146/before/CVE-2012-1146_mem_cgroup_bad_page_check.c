bool mem_cgroup_bad_page_check(struct page *page)
{
	if (mem_cgroup_disabled())
		return false;

	return lookup_page_cgroup_used(page) != NULL;
}
