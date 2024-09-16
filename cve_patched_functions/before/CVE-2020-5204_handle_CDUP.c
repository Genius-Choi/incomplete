static void handle_CDUP(ctrl_t *ctrl, char *path)
{
	handle_CWD(ctrl, "..");
}
