static ssize_t o2nm_cluster_fence_method_store(
	struct config_item *item, const char *page, size_t count)
{
	unsigned int i;

	if (page[count - 1] != '\n')
		goto bail;

	for (i = 0; i < O2NM_FENCE_METHODS; ++i) {
		if (count != strlen(o2nm_fence_method_desc[i]) + 1)
			continue;
		if (strncasecmp(page, o2nm_fence_method_desc[i], count - 1))
			continue;
		if (to_o2nm_cluster(item)->cl_fence_method != i) {
			printk(KERN_INFO "ocfs2: Changing fence method to %s\n",
			       o2nm_fence_method_desc[i]);
			to_o2nm_cluster(item)->cl_fence_method = i;
		}
		return count;
	}

bail:
	return -EINVAL;
}
