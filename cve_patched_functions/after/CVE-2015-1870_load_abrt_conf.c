int load_abrt_conf()
{
    free_abrt_conf_data();

    map_string_t *settings = new_map_string();
    if (!load_abrt_conf_file(ABRT_CONF, settings))
        perror_msg("Can't load '%s'", ABRT_CONF);

    ParseCommon(settings, ABRT_CONF);
    free_map_string(settings);

    return 0;
}
