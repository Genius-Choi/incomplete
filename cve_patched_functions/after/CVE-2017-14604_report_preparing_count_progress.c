report_preparing_count_progress (CommonJob  *job,
                                 SourceInfo *source_info)
{
    char *s;

    switch (source_info->op)
    {
        default:
        case OP_KIND_COPY:
        {
            s = f (ngettext ("Preparing to copy %'d file (%S)",
                             "Preparing to copy %'d files (%S)",
                             source_info->num_files),
                   source_info->num_files, source_info->num_bytes);
        }
        break;

        case OP_KIND_MOVE:
        {
            s = f (ngettext ("Preparing to move %'d file (%S)",
                             "Preparing to move %'d files (%S)",
                             source_info->num_files),
                   source_info->num_files, source_info->num_bytes);
        }
        break;

        case OP_KIND_DELETE:
        {
            s = f (ngettext ("Preparing to delete %'d file (%S)",
                             "Preparing to delete %'d files (%S)",
                             source_info->num_files),
                   source_info->num_files, source_info->num_bytes);
        }
        break;

        case OP_KIND_TRASH:
        {
            s = f (ngettext ("Preparing to trash %'d file",
                             "Preparing to trash %'d files",
                             source_info->num_files),
                   source_info->num_files);
        }
        break;

        case OP_KIND_COMPRESS:
            s = f (ngettext ("Preparing to compress %'d file",
                             "Preparing to compress %'d files",
                             source_info->num_files),
                   source_info->num_files);
    }

    nautilus_progress_info_take_details (job->progress, s);
    nautilus_progress_info_pulse_progress (job->progress);
}
