static int root_task_group_empty(void)
{
	return list_empty(&root_task_group.children);
}
