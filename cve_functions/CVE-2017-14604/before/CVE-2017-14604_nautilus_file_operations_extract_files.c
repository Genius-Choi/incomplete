nautilus_file_operations_extract_files (GList                   *files,
                                        GFile                   *destination_directory,
                                        GtkWindow               *parent_window,
                                        NautilusExtractCallback  done_callback,
                                        gpointer                 done_callback_data)
{
    ExtractJob *extract_job;
    g_autoptr (GTask) task = NULL;

    extract_job = op_job_new (ExtractJob, parent_window);
    extract_job->source_files = g_list_copy_deep (files,
                                                  (GCopyFunc) g_object_ref,
                                                  NULL);
    extract_job->destination_directory = g_object_ref (destination_directory);
    extract_job->done_callback = done_callback;
    extract_job->done_callback_data = done_callback_data;

    inhibit_power_manager ((CommonJob *) extract_job, _("Extracting Files"));

    if (!nautilus_file_undo_manager_is_operating ())
    {
        extract_job->common.undo_info = nautilus_file_undo_info_extract_new (files,
                                                                             destination_directory);
    }

    task = g_task_new (NULL, extract_job->common.cancellable,
                       extract_task_done, extract_job);
    g_task_set_task_data (task, extract_job, NULL);
    g_task_run_in_thread (task, extract_task_thread_func);
}
