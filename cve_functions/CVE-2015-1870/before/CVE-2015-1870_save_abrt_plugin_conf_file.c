int save_abrt_plugin_conf_file(const char *file, map_string_t *settings)
{
    char *path = concat_path_file(PLUGINS_CONF_DIR, file);
    int retval = save_conf_file(path, settings);
    free(path);
    return retval;
}
