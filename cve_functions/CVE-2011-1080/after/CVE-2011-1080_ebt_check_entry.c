ebt_check_entry(struct ebt_entry *e, struct net *net,
   const struct ebt_table_info *newinfo,
   const char *name, unsigned int *cnt,
   struct ebt_cl_stack *cl_s, unsigned int udc_cnt)
{
	struct ebt_entry_target *t;
	struct xt_target *target;
	unsigned int i, j, hook = 0, hookmask = 0;
	size_t gap;
	int ret;
	struct xt_mtchk_param mtpar;
	struct xt_tgchk_param tgpar;

	/* don't mess with the struct ebt_entries */
	if (e->bitmask == 0)
		return 0;

	if (e->bitmask & ~EBT_F_MASK) {
		BUGPRINT("Unknown flag for bitmask\n");
		return -EINVAL;
	}
	if (e->invflags & ~EBT_INV_MASK) {
		BUGPRINT("Unknown flag for inv bitmask\n");
		return -EINVAL;
	}
	if ( (e->bitmask & EBT_NOPROTO) && (e->bitmask & EBT_802_3) ) {
		BUGPRINT("NOPROTO & 802_3 not allowed\n");
		return -EINVAL;
	}
	/* what hook do we belong to? */
	for (i = 0; i < NF_BR_NUMHOOKS; i++) {
		if (!newinfo->hook_entry[i])
			continue;
		if ((char *)newinfo->hook_entry[i] < (char *)e)
			hook = i;
		else
			break;
	}
	/* (1 << NF_BR_NUMHOOKS) tells the check functions the rule is on
	   a base chain */
	if (i < NF_BR_NUMHOOKS)
		hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
	else {
		for (i = 0; i < udc_cnt; i++)
			if ((char *)(cl_s[i].cs.chaininfo) > (char *)e)
				break;
		if (i == 0)
			hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
		else
			hookmask = cl_s[i - 1].hookmask;
	}
	i = 0;

	mtpar.net	= tgpar.net       = net;
	mtpar.table     = tgpar.table     = name;
	mtpar.entryinfo = tgpar.entryinfo = e;
	mtpar.hook_mask = tgpar.hook_mask = hookmask;
	mtpar.family    = tgpar.family    = NFPROTO_BRIDGE;
	ret = EBT_MATCH_ITERATE(e, ebt_check_match, &mtpar, &i);
	if (ret != 0)
		goto cleanup_matches;
	j = 0;
	ret = EBT_WATCHER_ITERATE(e, ebt_check_watcher, &tgpar, &j);
	if (ret != 0)
		goto cleanup_watchers;
	t = (struct ebt_entry_target *)(((char *)e) + e->target_offset);
	gap = e->next_offset - e->target_offset;

	target = xt_request_find_target(NFPROTO_BRIDGE, t->u.name, 0);
	if (IS_ERR(target)) {
		ret = PTR_ERR(target);
		goto cleanup_watchers;
	}

	t->u.target = target;
	if (t->u.target == &ebt_standard_target) {
		if (gap < sizeof(struct ebt_standard_target)) {
			BUGPRINT("Standard target size too big\n");
			ret = -EFAULT;
			goto cleanup_watchers;
		}
		if (((struct ebt_standard_target *)t)->verdict <
		   -NUM_STANDARD_TARGETS) {
			BUGPRINT("Invalid standard target\n");
			ret = -EFAULT;
			goto cleanup_watchers;
		}
	} else if (t->target_size > gap - sizeof(struct ebt_entry_target)) {
		module_put(t->u.target->me);
		ret = -EFAULT;
		goto cleanup_watchers;
	}

	tgpar.target   = target;
	tgpar.targinfo = t->data;
	ret = xt_check_target(&tgpar, t->target_size,
	      e->ethproto, e->invflags & EBT_IPROTO);
	if (ret < 0) {
		module_put(target->me);
		goto cleanup_watchers;
	}
	(*cnt)++;
	return 0;
cleanup_watchers:
	EBT_WATCHER_ITERATE(e, ebt_cleanup_watcher, net, &j);
cleanup_matches:
	EBT_MATCH_ITERATE(e, ebt_cleanup_match, net, &i);
	return ret;
}
