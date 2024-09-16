static void jit_free_defer(struct work_struct *arg)
{
	module_free(NULL, arg);
}
