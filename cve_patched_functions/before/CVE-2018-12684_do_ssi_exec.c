do_ssi_exec(struct mg_connection *conn, char *tag)
{
	char cmd[1024] = "";
	struct mg_file file = STRUCT_FILE_INITIALIZER;

	if (sscanf(tag, " \"%1023[^\"]\"", cmd) != 1) {
		mg_cry_internal(conn, "Bad SSI #exec: [%s]", tag);
	} else {
		cmd[1023] = 0;
		if ((file.access.fp = popen(cmd, "r")) == NULL) {
			mg_cry_internal(conn,
			                "Cannot SSI #exec: [%s]: %s",
			                cmd,
			                strerror(ERRNO));
		} else {
			send_file_data(conn, &file, 0, INT64_MAX);
			pclose(file.access.fp);
		}
	}
}
