static void correct_bz_private_goup_name(const char *event_name)
{
    if (strcmp("report_Bugzilla", event_name) == 0 &&
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(g_builder, PRIVATE_TICKET_CB))))
    {
        event_config_t *cfg = get_event_config(event_name);
        if (NULL != cfg)
        {
            GList *item = cfg->options;
            for ( ; item != NULL; item = g_list_next(item))
            {
                event_option_t *opt = item->data;
                if (strcmp("Bugzilla_PrivateGroups", opt->eo_name) == 0
                    && opt->eo_value
                    && strcmp(opt->eo_value, "private") == 0
                    && ask_replace_old_private_group_name())
                {
                    free(opt->eo_value);
                    opt->eo_value = xstrdup("fedora_contrib_private");
                }
            }
        }
    }
}
