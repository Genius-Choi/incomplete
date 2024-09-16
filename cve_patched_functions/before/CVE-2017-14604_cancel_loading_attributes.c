cancel_loading_attributes (NautilusDirectory      *directory,
                           NautilusFileAttributes  file_attributes)
{
    Request request;

    request = nautilus_directory_set_up_request (file_attributes);

    if (REQUEST_WANTS_TYPE (request, REQUEST_DIRECTORY_COUNT))
    {
        directory_count_cancel (directory);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_DEEP_COUNT))
    {
        deep_count_cancel (directory);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_MIME_LIST))
    {
        mime_list_cancel (directory);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_FILE_INFO))
    {
        file_info_cancel (directory);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_FILESYSTEM_INFO))
    {
        filesystem_info_cancel (directory);
    }
    if (REQUEST_WANTS_TYPE (request, REQUEST_LINK_INFO))
    {
        link_info_cancel (directory);
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_EXTENSION_INFO))
    {
        extension_info_cancel (directory);
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_THUMBNAIL))
    {
        thumbnail_cancel (directory);
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_MOUNT))
    {
        mount_cancel (directory);
    }

    nautilus_directory_async_state_changed (directory);
}
