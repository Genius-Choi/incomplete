unsigned long copy_transact_vsx_from_user(struct task_struct *task,
					  void __user *from)
{
	u64 buf[ELF_NVSRHALFREG];
	int i;

	if (__copy_from_user(buf, from, ELF_NVSRHALFREG * sizeof(double)))
		return 1;
	for (i = 0; i < ELF_NVSRHALFREG ; i++)
		task->thread.transact_fp.fpr[i][TS_VSRLOWOFFSET] = buf[i];
	return 0;
}
