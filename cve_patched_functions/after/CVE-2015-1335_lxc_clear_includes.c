static inline void lxc_clear_includes(struct lxc_conf *conf)
{
	struct lxc_list *it,*next;

	lxc_list_for_each_safe(it, &conf->includes, next) {
		lxc_list_del(it);
		free(it->elem);
		free(it);
	}
}
