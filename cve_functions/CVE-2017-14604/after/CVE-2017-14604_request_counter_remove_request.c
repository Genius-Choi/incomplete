request_counter_remove_request (RequestCounter counter,
                                Request        request)
{
    guint i;

    for (i = 0; i < REQUEST_TYPE_LAST; i++)
    {
        if (REQUEST_WANTS_TYPE (request, i))
        {
            counter[i]--;
        }
    }
}
