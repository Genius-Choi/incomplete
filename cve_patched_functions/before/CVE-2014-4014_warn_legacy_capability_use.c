static void warn_legacy_capability_use(void)
{
	char name[sizeof(current->comm)];

	pr_info_once("warning: `%s' uses 32-bit capabilities (legacy support in use)\n",
		     get_task_comm(name, current));
}
