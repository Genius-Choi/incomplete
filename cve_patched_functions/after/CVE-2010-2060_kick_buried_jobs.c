kick_buried_jobs(tube t, unsigned int n)
{
    unsigned int i;
    for (i = 0; (i < n) && kick_buried_job(t); ++i);
    return i;
}
