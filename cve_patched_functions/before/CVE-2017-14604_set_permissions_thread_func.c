set_permissions_thread_func (GTask        *task,
                             gpointer      source_object,
                             gpointer      task_data,
                             GCancellable *cancellable)
{
    SetPermissionsJob *job = task_data;
    CommonJob *common;

    common = (CommonJob *) job;

    nautilus_progress_info_set_status (common->progress,
                                       _("Setting permissions"));

    nautilus_progress_info_start (job->common.progress);

    set_permissions_file (job, job->file, NULL);
}
