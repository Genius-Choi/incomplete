static int check_user_pass(ctrl_t *ctrl)
{
	if (!ctrl->name[0])
		return -1;

	if (!strcmp("anonymous", ctrl->name))
		return 1;

	return 0;
}
