static bool get_sensitive_data_permission(const char *event_name)
{
    event_config_t *event_cfg = get_event_config(event_name);

    if (!event_cfg || !event_cfg->ec_sending_sensitive_data)
        return true;

    char *msg = xasprintf(_("Event '%s' requires permission to send possibly sensitive data."
                            "\nDo you want to continue?"),
                            ec_get_screen_name(event_cfg) ? ec_get_screen_name(event_cfg) : event_name);
    const bool response = run_ask_yes_no_yesforever_dialog("ask_send_sensitive_data", msg, GTK_WINDOW(g_wnd_assistant));
    free(msg);

    return response;
}
