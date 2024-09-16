static inline void lxc_clear_aliens(struct lxc_conf *conf)
{
	struct lxc_list *it,*next;

	lxc_list_for_each_safe(it, &conf->aliens, next) {
		lxc_list_del(it);
		free(it->elem);
		free(it);
	}
}
