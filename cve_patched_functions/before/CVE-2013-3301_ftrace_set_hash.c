ftrace_set_hash(struct ftrace_ops *ops, unsigned char *buf, int len,
		unsigned long ip, int remove, int reset, int enable)
{
	struct ftrace_hash **orig_hash;
	struct ftrace_hash *hash;
	int ret;

	/* All global ops uses the global ops filters */
	if (ops->flags & FTRACE_OPS_FL_GLOBAL)
		ops = &global_ops;

	if (unlikely(ftrace_disabled))
		return -ENODEV;

	if (enable)
		orig_hash = &ops->filter_hash;
	else
		orig_hash = &ops->notrace_hash;

	hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS, *orig_hash);
	if (!hash)
		return -ENOMEM;

	mutex_lock(&ftrace_regex_lock);
	if (reset)
		ftrace_filter_reset(hash);
	if (buf && !ftrace_match_records(hash, buf, len)) {
		ret = -EINVAL;
		goto out_regex_unlock;
	}
	if (ip) {
		ret = ftrace_match_addr(hash, ip, remove);
		if (ret < 0)
			goto out_regex_unlock;
	}

	mutex_lock(&ftrace_lock);
	ret = ftrace_hash_move(ops, enable, orig_hash, hash);
	if (!ret && ops->flags & FTRACE_OPS_FL_ENABLED
	    && ftrace_enabled)
		ftrace_run_update_code(FTRACE_UPDATE_CALLS);

	mutex_unlock(&ftrace_lock);

 out_regex_unlock:
	mutex_unlock(&ftrace_regex_lock);

	free_ftrace_hash(hash);
	return ret;
}
