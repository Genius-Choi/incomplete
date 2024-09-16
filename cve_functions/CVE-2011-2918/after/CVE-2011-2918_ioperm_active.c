static int ioperm_active(struct task_struct *target,
			 const struct user_regset *regset)
{
	return target->thread.io_bitmap_max / regset->size;
}
