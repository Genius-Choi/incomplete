static void __state_set(struct iwch_ep_common *epc, enum iwch_ep_state new)
{
	epc->state = new;
}
