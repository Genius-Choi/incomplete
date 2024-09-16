report_preparing_link_progress (CopyMoveJob *link_job,
                                int          total,
                                int          left)
{
    CommonJob *job;

    job = (CommonJob *) link_job;

    nautilus_progress_info_take_status (job->progress,
                                        f (_("Creating links in “%B”"),
                                           link_job->destination));

    nautilus_progress_info_take_details (job->progress,
                                         f (ngettext ("Making link to %'d file",
                                                      "Making links to %'d files",
                                                      left), left));

    nautilus_progress_info_set_progress (job->progress, left, total);
}
