const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
	return &user_arm_view;
}
