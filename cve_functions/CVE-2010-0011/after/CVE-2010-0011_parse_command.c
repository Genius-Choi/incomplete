parse_command(const char *cmd, const char *param, GString *result) {
    CommandInfo *c;
    GString *tmp = g_string_new("");

    if ((c = g_hash_table_lookup(uzbl.behave.commands, cmd))) {
            guint i;
            gchar **par = split_quoted(param, TRUE);
            GArray *a = g_array_new (TRUE, FALSE, sizeof(gchar*));

            if (c->no_split) { /* don't split */
                sharg_append(a, param);
            } else if (par) {
                for (i = 0; i < g_strv_length(par); i++)
                    sharg_append(a, par[i]);
            }

            if (result == NULL) {
                GString *result_print = g_string_new("");

                c->function(uzbl.gui.web_view, a, result_print);
                if (result_print->len)
                    printf("%*s\n", (int)result_print->len, result_print->str);

                g_string_free(result_print, TRUE);
            } else {
                c->function(uzbl.gui.web_view, a, result);
            }
            g_strfreev (par);
            g_array_free (a, TRUE);

            if(strcmp("set", cmd)     &&
               strcmp("event", cmd)   &&
               strcmp("request", cmd)) {
                g_string_printf(tmp, "%s %s", cmd, param?param:"");
                send_event(COMMAND_EXECUTED, tmp->str, NULL);
                g_string_free(tmp, TRUE);
            }
    }
    else {
        gchar *tmp = g_strdup_printf("%s %s", cmd, param?param:"");
        send_event(COMMAND_ERROR, tmp, NULL);
        g_free(tmp);
    }
}
