config_remotely(
	sockaddr_u *	remote_addr
	)
{
	struct FILE_INFO remote_cuckoo;
	char origin[128];

	snprintf(origin, sizeof(origin), "remote config from %s",
		 stoa(remote_addr));
	memset(&remote_cuckoo, 0, sizeof(remote_cuckoo));
	remote_cuckoo.fname = origin;
	remote_cuckoo.line_no = 1;
	remote_cuckoo.col_no = 1;
	ip_file = &remote_cuckoo;
	input_from_file = 0;

	init_syntax_tree(&cfgt);
	yyparse();
	cfgt.source.attr = CONF_SOURCE_NTPQ;
	cfgt.timestamp = time(NULL);
	cfgt.source.value.s = estrdup(stoa(remote_addr));

	DPRINTF(1, ("Finished Parsing!!\n"));

	save_and_apply_config_tree();

	input_from_file = 1;
}
