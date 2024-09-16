directory_load_done (NautilusDirectory *directory,
                     GError            *error)
{
    GList *node;

    nautilus_profile_start (NULL);
    g_object_ref (directory);

    directory->details->directory_loaded = TRUE;
    directory->details->directory_loaded_sent_notification = FALSE;

    if (error != NULL)
    {
        /* The load did not complete successfully. This means
         * we don't know the status of the files in this directory.
         * We clear the unconfirmed bit on each file here so that
         * they won't be marked "gone" later -- we don't know enough
         * about them to know whether they are really gone.
         */
        for (node = directory->details->file_list;
             node != NULL; node = node->next)
        {
            set_file_unconfirmed (NAUTILUS_FILE (node->data), FALSE);
        }

        nautilus_directory_emit_load_error (directory, error);
    }

    /* Call the idle function right away. */
    if (directory->details->dequeue_pending_idle_id != 0)
    {
        g_source_remove (directory->details->dequeue_pending_idle_id);
    }
    dequeue_pending_idle_callback (directory);

    directory_load_cancel (directory);

    g_object_unref (directory);
    nautilus_profile_end (NULL);
}
