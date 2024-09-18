run_cancel_or_skip_warning (CommonJob  *job,
                            char       *primary_text,
                            char       *secondary_text,
                            const char *details_text,
                            int         total_operations,
                            int         operations_remaining)
{
    int response;

    if (total_operations == 1)
    {
        response = run_warning (job,
                                primary_text,
                                secondary_text,
                                details_text,
                                FALSE,
                                CANCEL,
                                NULL);
    }
    else
    {
        response = run_warning (job,
                                primary_text,
                                secondary_text,
                                details_text,
                                operations_remaining > 1,
                                CANCEL, SKIP_ALL, SKIP,
                                NULL);
    }

    return response;
}
