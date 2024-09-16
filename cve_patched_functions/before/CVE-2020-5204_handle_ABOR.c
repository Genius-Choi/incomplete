static void handle_ABOR(ctrl_t *ctrl, char *arg)
{
	DBG("Aborting any current transfer ...");
	if (do_abort(ctrl))
		send_msg(ctrl->sd, "426 Connection closed; transfer aborted.\r\n");

	send_msg(ctrl->sd, "226 Closing data connection.\r\n");
}
