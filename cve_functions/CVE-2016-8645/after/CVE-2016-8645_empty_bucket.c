static inline bool empty_bucket(const struct tcp_iter_state *st)
{
	return hlist_nulls_empty(&tcp_hashinfo.ehash[st->bucket].chain);
}
