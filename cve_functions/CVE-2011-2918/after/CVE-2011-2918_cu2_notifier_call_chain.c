int cu2_notifier_call_chain(unsigned long val, void *v)
{
	return raw_notifier_call_chain(&cu2_chain, val, v);
}
