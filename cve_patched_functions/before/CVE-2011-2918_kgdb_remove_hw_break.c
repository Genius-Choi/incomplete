kgdb_remove_hw_break(unsigned long addr, int len, enum kgdb_bptype bptype)
{
	int i;

	for (i = 0; i < HBP_NUM; i++)
		if (breakinfo[i].addr == addr && breakinfo[i].enabled)
			break;
	if (i == HBP_NUM)
		return -1;

	if (hw_break_release_slot(i)) {
		printk(KERN_ERR "Cannot remove hw breakpoint at %lx\n", addr);
		return -1;
	}
	breakinfo[i].enabled = 0;

	return 0;
}
