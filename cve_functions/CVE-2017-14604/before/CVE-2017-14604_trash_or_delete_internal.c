trash_or_delete_internal (GList                  *files,
                          GtkWindow              *parent_window,
                          gboolean                try_trash,
                          NautilusDeleteCallback  done_callback,
                          gpointer                done_callback_data)
{
    GTask *task;
    DeleteJob *job;

    /* TODO: special case desktop icon link files ... */

    job = op_job_new (DeleteJob, parent_window);
    job->files = g_list_copy_deep (files, (GCopyFunc) g_object_ref, NULL);
    job->try_trash = try_trash;
    job->user_cancel = FALSE;
    job->done_callback = done_callback;
    job->done_callback_data = done_callback_data;

    if (try_trash)
    {
        inhibit_power_manager ((CommonJob *) job, _("Trashing Files"));
    }
    else
    {
        inhibit_power_manager ((CommonJob *) job, _("Deleting Files"));
    }

    if (!nautilus_file_undo_manager_is_operating () && try_trash)
    {
        job->common.undo_info = nautilus_file_undo_info_trash_new (g_list_length (files));
    }

    task = g_task_new (NULL, NULL, delete_task_done, job);
    g_task_set_task_data (task, job, NULL);
    g_task_run_in_thread (task, delete_task_thread_func);
    g_object_unref (task);
}
