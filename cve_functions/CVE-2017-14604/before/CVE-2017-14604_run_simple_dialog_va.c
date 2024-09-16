run_simple_dialog_va (CommonJob      *job,
                      gboolean        ignore_close_box,
                      GtkMessageType  message_type,
                      char           *primary_text,
                      char           *secondary_text,
                      const char     *details_text,
                      gboolean        show_all,
                      va_list         varargs)
{
    RunSimpleDialogData *data;
    int res;
    const char *button_title;
    GPtrArray *ptr_array;

    g_timer_stop (job->time);

    data = g_new0 (RunSimpleDialogData, 1);
    data->parent_window = &job->parent_window;
    data->ignore_close_box = ignore_close_box;
    data->message_type = message_type;
    data->primary_text = primary_text;
    data->secondary_text = secondary_text;
    data->details_text = details_text;
    data->show_all = show_all;
    data->completed = FALSE;
    g_mutex_init (&data->mutex);
    g_cond_init (&data->cond);

    ptr_array = g_ptr_array_new ();
    while ((button_title = va_arg (varargs, const char *)) != NULL)
    {
        g_ptr_array_add (ptr_array, (char *) button_title);
    }
    g_ptr_array_add (ptr_array, NULL);
    data->button_titles = (const char **) g_ptr_array_free (ptr_array, FALSE);

    nautilus_progress_info_pause (job->progress);

    g_mutex_lock (&data->mutex);

    g_main_context_invoke (NULL,
                           do_run_simple_dialog,
                           data);

    while (!data->completed)
    {
        g_cond_wait (&data->cond, &data->mutex);
    }

    nautilus_progress_info_resume (job->progress);
    res = data->result;

    g_mutex_unlock (&data->mutex);
    g_mutex_clear (&data->mutex);
    g_cond_clear (&data->cond);

    g_free (data->button_titles);
    g_free (data);

    g_timer_continue (job->time);

    g_free (primary_text);
    g_free (secondary_text);

    return res;
}
