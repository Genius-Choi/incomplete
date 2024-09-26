static inline int check_target(struct arpt_entry *e, const char *name)
{
	struct xt_entry_target *t = arpt_get_target(e);
	struct xt_tgchk_param par = {
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_ARP,
	};

	return xt_check_target(&par, t->u.target_size - sizeof(*t), 0, false);
}
