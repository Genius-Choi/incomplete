static void add_workflow_buttons(GtkBox *box, GHashTable *workflows, GCallback func)
{
    gtk_container_foreach(GTK_CONTAINER(box), &remove_child_widget, NULL);

    GList *possible_workflows = list_possible_events_glist(g_dump_dir_name, "workflow");
    GHashTable *workflow_table = load_workflow_config_data_from_list(
                        possible_workflows,
                        WORKFLOWS_DIR);
    g_list_free_full(possible_workflows, free);
    g_object_set_data_full(G_OBJECT(box), "workflows", workflow_table, (GDestroyNotify)g_hash_table_destroy);

    GList *wf_list = g_hash_table_get_values(workflow_table);
    wf_list = g_list_sort(wf_list, (GCompareFunc)wf_priority_compare);

    for (GList *wf_iter = wf_list; wf_iter; wf_iter = g_list_next(wf_iter))
    {
        workflow_t *w = (workflow_t *)wf_iter->data;
        char *btn_label = xasprintf("<b>%s</b>\n%s", wf_get_screen_name(w), wf_get_description(w));
        GtkWidget *button = gtk_button_new_with_label(btn_label);
        GList *children = gtk_container_get_children(GTK_CONTAINER(button));
        GtkWidget *label = (GtkWidget *)children->data;
        gtk_label_set_use_markup(GTK_LABEL(label), true);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_widget_set_margin_top(label, 10);
#if ((GTK_MAJOR_VERSION == 3 && GTK_MINOR_VERSION < 11) || (GTK_MAJOR_VERSION == 3 && GTK_MINOR_VERSION == 11 && GTK_MICRO_VERSION < 2))
        gtk_widget_set_margin_left(label, 40);
#else
        gtk_widget_set_margin_start(label, 40);
#endif
        gtk_widget_set_margin_bottom(label, 10);
        g_list_free(children);
        free(btn_label);
        g_signal_connect(button, "clicked", func, w);
        gtk_box_pack_start(box, button, true, false, 2);
    }

    g_list_free(wf_list);
}
