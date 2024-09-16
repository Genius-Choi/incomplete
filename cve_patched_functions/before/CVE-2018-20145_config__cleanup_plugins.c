static void config__cleanup_plugins(struct mosquitto__config *config)
{
	int i, j;
	struct mosquitto__auth_plugin_config *plug;

	if(config->security_options.auth_plugin_configs){
		for(i=0; i<config->security_options.auth_plugin_config_count; i++){
			plug = &config->security_options.auth_plugin_configs[i];
			mosquitto__free(plug->path);
			plug->path = NULL;

			if(plug->options){
				for(j=0; j<plug->option_count; j++){
					mosquitto__free(plug->options[j].key);
					mosquitto__free(plug->options[j].value);
				}
				mosquitto__free(plug->options);
				plug->options = NULL;
				plug->option_count = 0;
			}
		}
		mosquitto__free(config->security_options.auth_plugin_configs);
		config->security_options.auth_plugin_configs = NULL;
	}
}
