report_preparing_move_progress (CopyMoveJob *move_job,
                                int          total,
                                int          left)
{
    CommonJob *job;

    job = (CommonJob *) move_job;

    nautilus_progress_info_take_status (job->progress,
                                        f (_("Preparing to move to “%B”"),
                                           move_job->destination));

    nautilus_progress_info_take_details (job->progress,
                                         f (ngettext ("Preparing to move %'d file",
                                                      "Preparing to move %'d files",
                                                      left), left));

    nautilus_progress_info_pulse_progress (job->progress);
}
