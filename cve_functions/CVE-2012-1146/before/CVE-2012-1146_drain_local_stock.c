static void drain_local_stock(struct work_struct *dummy)
{
	struct memcg_stock_pcp *stock = &__get_cpu_var(memcg_stock);
	drain_stock(stock);
	clear_bit(FLUSHING_CACHED_CHARGE, &stock->flags);
}
