int lxc_attach_run_command(void* payload)
{
	lxc_attach_command_t* cmd = (lxc_attach_command_t*)payload;

	execvp(cmd->program, cmd->argv);
	SYSERROR("failed to exec '%s'", cmd->program);
	return -1;
}
