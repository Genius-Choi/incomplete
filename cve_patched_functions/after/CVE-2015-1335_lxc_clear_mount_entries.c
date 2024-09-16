int lxc_clear_mount_entries(struct lxc_conf *c)
{
	struct lxc_list *it,*next;

	lxc_list_for_each_safe(it, &c->mount_list, next) {
		lxc_list_del(it);
		free(it->elem);
		free(it);
	}
	return 0;
}
