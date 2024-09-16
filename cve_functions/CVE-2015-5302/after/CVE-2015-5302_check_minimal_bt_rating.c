static bool check_minimal_bt_rating(const char *event_name)
{
    bool acceptable_rating = true;
    event_config_t *event_cfg = NULL;

    if (!event_name)
        error_msg_and_die(_("Cannot check backtrace rating because of invalid event name"));
    else if (prefixcmp(event_name, "report") != 0)
    {
        log_info("No checks for bactrace rating because event '%s' doesn't report.", event_name);
        return acceptable_rating;
    }
    else
        event_cfg = get_event_config(event_name);

    char *description = NULL;
    acceptable_rating = check_problem_rating_usability(event_cfg, g_cd, &description, NULL);
    if (description)
    {
        add_warning(description);
        free(description);
    }

    return acceptable_rating;
}
