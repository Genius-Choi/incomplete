remove_callback_link (NautilusDirectory *directory,
                      GList             *link)
{
    ReadyCallback *callback;

    callback = link->data;
    remove_callback_link_keep_data (directory, link);
    g_free (callback);
}
