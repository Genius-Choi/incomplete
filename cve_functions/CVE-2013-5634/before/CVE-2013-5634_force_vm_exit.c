void force_vm_exit(const cpumask_t *mask)
{
	smp_call_function_many(mask, exit_vm_noop, NULL, true);
}
