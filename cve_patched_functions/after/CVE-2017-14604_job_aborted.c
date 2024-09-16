job_aborted (CommonJob *job)
{
    return g_cancellable_is_cancelled (job->cancellable);
}
