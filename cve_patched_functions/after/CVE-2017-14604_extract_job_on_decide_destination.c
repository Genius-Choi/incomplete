extract_job_on_decide_destination (AutoarExtractor *extractor,
                                   GFile           *destination,
                                   GList           *files,
                                   gpointer         user_data)
{
    ExtractJob *extract_job = user_data;
    GFile *decided_destination;
    g_autofree char *basename = NULL;

    nautilus_progress_info_set_details (extract_job->common.progress,
                                        _("Verifying destination"));

    basename = g_file_get_basename (destination);
    decided_destination = nautilus_generate_unique_file_in_directory (extract_job->destination_directory,
                                                                      basename);

    if (job_aborted ((CommonJob *) extract_job))
    {
        g_object_unref (decided_destination);
        return NULL;
    }

    extract_job->output_files = g_list_prepend (extract_job->output_files,
                                                decided_destination);

    return g_object_ref (decided_destination);
}
