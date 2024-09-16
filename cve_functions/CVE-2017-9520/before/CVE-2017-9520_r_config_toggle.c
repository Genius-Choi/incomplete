R_API int r_config_toggle(RConfig *cfg, const char *name) {
	RConfigNode *node = r_config_node_get (cfg, name);
	if (node && node->flags & CN_BOOL) {
		(void)r_config_set_i (cfg, name, !node->i_value);
		return true;
	}
	return false;
}
