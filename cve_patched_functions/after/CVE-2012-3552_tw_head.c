static inline struct inet_timewait_sock *tw_head(struct hlist_nulls_head *head)
{
	return hlist_nulls_empty(head) ? NULL :
		list_entry(head->first, struct inet_timewait_sock, tw_node);
}
