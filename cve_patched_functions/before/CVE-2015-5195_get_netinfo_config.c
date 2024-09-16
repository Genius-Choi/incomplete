get_netinfo_config(void)
{
	ni_status status;
	void *domain;
	ni_id config_dir;
	struct netinfo_config_state *config;

	if (ni_open(NULL, ".", &domain) != NI_OK) return NULL;

	while ((status = ni_pathsearch(domain, &config_dir, NETINFO_CONFIG_DIR)) == NI_NODIR) {
		void *next_domain;
		if (ni_open(domain, "..", &next_domain) != NI_OK) {
			ni_free(next_domain);
			break;
		}
		ni_free(domain);
		domain = next_domain;
	}
	if (status != NI_OK) {
		ni_free(domain);
		return NULL;
	}

	config = emalloc(sizeof(*config));
	config->domain = domain;
	config->config_dir = config_dir;
	config->prop_index = 0;
	config->val_index = 0;
	config->val_list = NULL;

	return config;
}
