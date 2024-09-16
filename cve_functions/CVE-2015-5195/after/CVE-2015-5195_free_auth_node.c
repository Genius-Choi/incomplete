free_auth_node(
	config_tree *ptree
	)
{
	if (ptree->auth.keys) {
		free(ptree->auth.keys);
		ptree->auth.keys = NULL;
	}

	if (ptree->auth.keysdir) {
		free(ptree->auth.keysdir);
		ptree->auth.keysdir = NULL;
	}

	if (ptree->auth.ntp_signd_socket) {
		free(ptree->auth.ntp_signd_socket);
		ptree->auth.ntp_signd_socket = NULL;
	}
}
