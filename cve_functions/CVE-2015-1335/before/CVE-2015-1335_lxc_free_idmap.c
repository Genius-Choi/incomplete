static int lxc_free_idmap(struct lxc_list *id_map) {
	struct lxc_list *it, *next;

	lxc_list_for_each_safe(it, id_map, next) {
		lxc_list_del(it);
		free(it->elem);
		free(it);
	}
	return 0;
}
