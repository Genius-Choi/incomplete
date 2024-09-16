nautilus_file_operations_unmount_mount_full (GtkWindow               *parent_window,
                                             GMount                  *mount,
                                             GMountOperation         *mount_operation,
                                             gboolean                 eject,
                                             gboolean                 check_trash,
                                             NautilusUnmountCallback  callback,
                                             gpointer                 callback_data)
{
    UnmountData *data;
    int response;

    data = g_new0 (UnmountData, 1);
    data->callback = callback;
    data->callback_data = callback_data;
    if (parent_window)
    {
        data->parent_window = parent_window;
        g_object_add_weak_pointer (G_OBJECT (data->parent_window),
                                   (gpointer *) &data->parent_window);
    }
    if (mount_operation)
    {
        data->mount_operation = g_object_ref (mount_operation);
    }
    data->eject = eject;
    data->mount = g_object_ref (mount);

    if (check_trash && has_trash_files (mount))
    {
        response = prompt_empty_trash (parent_window);

        if (response == GTK_RESPONSE_ACCEPT)
        {
            GTask *task;
            EmptyTrashJob *job;

            job = op_job_new (EmptyTrashJob, parent_window);
            job->should_confirm = FALSE;
            job->trash_dirs = get_trash_dirs_for_mount (mount);
            job->done_callback = empty_trash_for_unmount_done;
            job->done_callback_data = data;

            task = g_task_new (NULL, NULL, empty_trash_task_done, job);
            g_task_set_task_data (task, job, NULL);
            g_task_run_in_thread (task, empty_trash_thread_func);
            g_object_unref (task);
            return;
        }
        else if (response == GTK_RESPONSE_CANCEL)
        {
            if (callback)
            {
                callback (callback_data);
            }

            unmount_data_free (data);
            return;
        }
    }

    do_unmount (data);
}
