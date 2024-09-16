handle_copy_move_conflict (CommonJob *job,
                           GFile     *src,
                           GFile     *dest,
                           GFile     *dest_dir)
{
    FileConflictResponse *response;

    g_timer_stop (job->time);
    nautilus_progress_info_pause (job->progress);

    response = copy_move_conflict_ask_user_action (job->parent_window,
                                                   src,
                                                   dest,
                                                   dest_dir);

    nautilus_progress_info_resume (job->progress);
    g_timer_continue (job->time);

    return response;
}
