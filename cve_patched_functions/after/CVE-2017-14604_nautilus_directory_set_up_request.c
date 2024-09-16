nautilus_directory_set_up_request (NautilusFileAttributes file_attributes)
{
    Request request;

    request = 0;

    if ((file_attributes & NAUTILUS_FILE_ATTRIBUTE_DIRECTORY_ITEM_COUNT) != 0)
    {
        REQUEST_SET_TYPE (request, REQUEST_DIRECTORY_COUNT);
    }

    if ((file_attributes & NAUTILUS_FILE_ATTRIBUTE_DEEP_COUNTS) != 0)
    {
        REQUEST_SET_TYPE (request, REQUEST_DEEP_COUNT);
    }

    if ((file_attributes & NAUTILUS_FILE_ATTRIBUTE_DIRECTORY_ITEM_MIME_TYPES) != 0)
    {
        REQUEST_SET_TYPE (request, REQUEST_MIME_LIST);
    }
    if ((file_attributes & NAUTILUS_FILE_ATTRIBUTE_INFO) != 0)
    {
        REQUEST_SET_TYPE (request, REQUEST_FILE_INFO);
    }

    if (file_attributes & NAUTILUS_FILE_ATTRIBUTE_LINK_INFO)
    {
        REQUEST_SET_TYPE (request, REQUEST_FILE_INFO);
        REQUEST_SET_TYPE (request, REQUEST_LINK_INFO);
    }

    if ((file_attributes & NAUTILUS_FILE_ATTRIBUTE_EXTENSION_INFO) != 0)
    {
        REQUEST_SET_TYPE (request, REQUEST_EXTENSION_INFO);
    }

    if (file_attributes & NAUTILUS_FILE_ATTRIBUTE_THUMBNAIL)
    {
        REQUEST_SET_TYPE (request, REQUEST_THUMBNAIL);
        REQUEST_SET_TYPE (request, REQUEST_FILE_INFO);
    }

    if (file_attributes & NAUTILUS_FILE_ATTRIBUTE_MOUNT)
    {
        REQUEST_SET_TYPE (request, REQUEST_MOUNT);
        REQUEST_SET_TYPE (request, REQUEST_FILE_INFO);
    }

    if (file_attributes & NAUTILUS_FILE_ATTRIBUTE_FILESYSTEM_INFO)
    {
        REQUEST_SET_TYPE (request, REQUEST_FILESYSTEM_INFO);
    }

    return request;
}
