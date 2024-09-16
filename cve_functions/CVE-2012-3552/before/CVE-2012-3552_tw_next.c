static inline struct inet_timewait_sock *tw_next(struct inet_timewait_sock *tw)
{
	return !is_a_nulls(tw->tw_node.next) ?
		hlist_nulls_entry(tw->tw_node.next, typeof(*tw), tw_node) : NULL;
}
