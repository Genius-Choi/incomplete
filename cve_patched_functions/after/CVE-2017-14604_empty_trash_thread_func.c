empty_trash_thread_func (GTask        *task,
                         gpointer      source_object,
                         gpointer      task_data,
                         GCancellable *cancellable)
{
    EmptyTrashJob *job = task_data;
    CommonJob *common;
    GList *l;
    gboolean confirmed;

    common = (CommonJob *) job;

    nautilus_progress_info_start (job->common.progress);

    if (job->should_confirm)
    {
        confirmed = confirm_empty_trash (common);
    }
    else
    {
        confirmed = TRUE;
    }
    if (confirmed)
    {
        for (l = job->trash_dirs;
             l != NULL && !job_aborted (common);
             l = l->next)
        {
            delete_trash_file (common, l->data, FALSE, TRUE);
        }
    }
}
