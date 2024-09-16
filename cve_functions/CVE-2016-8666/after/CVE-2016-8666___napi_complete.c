void __napi_complete(struct napi_struct *n)
{
	BUG_ON(!test_bit(NAPI_STATE_SCHED, &n->state));

	list_del_init(&n->poll_list);
	smp_mb__before_atomic();
	clear_bit(NAPI_STATE_SCHED, &n->state);
}
