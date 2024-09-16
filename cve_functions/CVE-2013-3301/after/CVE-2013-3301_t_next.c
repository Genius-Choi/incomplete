t_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct ftrace_iterator *iter = m->private;
	struct ftrace_ops *ops = iter->ops;
	struct dyn_ftrace *rec = NULL;

	if (unlikely(ftrace_disabled))
		return NULL;

	if (iter->flags & FTRACE_ITER_HASH)
		return t_hash_next(m, pos);

	(*pos)++;
	iter->pos = iter->func_pos = *pos;

	if (iter->flags & FTRACE_ITER_PRINTALL)
		return t_hash_start(m, pos);

 retry:
	if (iter->idx >= iter->pg->index) {
		if (iter->pg->next) {
			iter->pg = iter->pg->next;
			iter->idx = 0;
			goto retry;
		}
	} else {
		rec = &iter->pg->records[iter->idx++];
		if (((iter->flags & FTRACE_ITER_FILTER) &&
		     !(ftrace_lookup_ip(ops->filter_hash, rec->ip))) ||

		    ((iter->flags & FTRACE_ITER_NOTRACE) &&
		     !ftrace_lookup_ip(ops->notrace_hash, rec->ip)) ||

		    ((iter->flags & FTRACE_ITER_ENABLED) &&
		     !(rec->flags & ~FTRACE_FL_MASK))) {

			rec = NULL;
			goto retry;
		}
	}

	if (!rec)
		return t_hash_start(m, pos);

	iter->func = rec;

	return iter;
}
