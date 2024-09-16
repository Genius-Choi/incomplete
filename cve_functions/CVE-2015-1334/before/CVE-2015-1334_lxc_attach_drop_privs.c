static int lxc_attach_drop_privs(struct lxc_proc_context_info *ctx)
{
	int last_cap = lxc_caps_last_cap();
	int cap;

	for (cap = 0; cap <= last_cap; cap++) {
		if (ctx->capability_mask & (1LL << cap))
			continue;

		if (prctl(PR_CAPBSET_DROP, cap, 0, 0, 0)) {
			SYSERROR("failed to remove capability id %d", cap);
			return -1;
		}
	}

	return 0;
}
