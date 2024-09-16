nautilus_file_set_permissions_recursive (const char         *directory,
                                         guint32             file_permissions,
                                         guint32             file_mask,
                                         guint32             dir_permissions,
                                         guint32             dir_mask,
                                         NautilusOpCallback  callback,
                                         gpointer            callback_data)
{
    GTask *task;
    SetPermissionsJob *job;

    job = op_job_new (SetPermissionsJob, NULL);
    job->file = g_file_new_for_uri (directory);
    job->file_permissions = file_permissions;
    job->file_mask = file_mask;
    job->dir_permissions = dir_permissions;
    job->dir_mask = dir_mask;
    job->done_callback = callback;
    job->done_callback_data = callback_data;

    if (!nautilus_file_undo_manager_is_operating ())
    {
        job->common.undo_info =
            nautilus_file_undo_info_rec_permissions_new (job->file,
                                                         file_permissions, file_mask,
                                                         dir_permissions, dir_mask);
    }

    task = g_task_new (NULL, NULL, set_permissions_task_done, job);
    g_task_set_task_data (task, job, NULL);
    g_task_run_in_thread (task, set_permissions_thread_func);
    g_object_unref (task);
}
