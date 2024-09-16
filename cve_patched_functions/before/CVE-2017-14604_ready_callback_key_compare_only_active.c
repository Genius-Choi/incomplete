ready_callback_key_compare_only_active (gconstpointer a,
                                        gconstpointer b)
{
    const ReadyCallback *callback_a;

    callback_a = a;

    /* Non active callbacks never match */
    if (!callback_a->active)
    {
        return -1;
    }

    return ready_callback_key_compare (a, b);
}
