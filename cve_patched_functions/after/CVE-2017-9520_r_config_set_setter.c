R_API int r_config_set_setter(RConfig *cfg, const char *key, RConfigCallback cb) {
	RConfigNode *node = r_config_node_get (cfg, key);
	if (node) {
		node->setter = cb;
		return 1;
	}
	return 0;
}
