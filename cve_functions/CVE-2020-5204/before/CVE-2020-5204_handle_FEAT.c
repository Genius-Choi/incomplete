static void handle_FEAT(ctrl_t *ctrl, char *arg)
{
	snprintf(ctrl->buf, ctrl->bufsz, "211-Features:\r\n"
		 " EPSV\r\n"
		 " PASV\r\n"
		 " SIZE\r\n"
		 " UTF8\r\n"
		 " REST STREAM\r\n"
		 " MLST modify*;perm*;size*;type*;\r\n"
		 "211 End\r\n");
	send_msg(ctrl->sd, ctrl->buf);
}
