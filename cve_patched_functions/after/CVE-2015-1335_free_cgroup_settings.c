static void free_cgroup_settings(struct lxc_list *result)
{
	struct lxc_list *iterator, *next;

	lxc_list_for_each_safe(iterator, result, next) {
		lxc_list_del(iterator);
		free(iterator);
	}
	free(result);
}
