nautilus_directory_cancel_loading_file_attributes (NautilusDirectory      *directory,
                                                   NautilusFile           *file,
                                                   NautilusFileAttributes  file_attributes)
{
    Request request;

    nautilus_directory_remove_file_from_work_queue (directory, file);

    request = nautilus_directory_set_up_request (file_attributes);

    if (REQUEST_WANTS_TYPE (request, REQUEST_DIRECTORY_COUNT))
    {
        cancel_directory_count_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_DEEP_COUNT))
    {
        cancel_deep_counts_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_MIME_LIST))
    {
        cancel_mime_list_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_FILE_INFO))
    {
        cancel_file_info_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_FILESYSTEM_INFO))
    {
        cancel_filesystem_info_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_LINK_INFO))
    {
        cancel_link_info_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_THUMBNAIL))
    {
        cancel_thumbnail_for_file (directory, file);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_MOUNT))
    {
        cancel_mount_for_file (directory, file);
    }

    nautilus_directory_async_state_changed (directory);
}
