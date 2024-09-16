nautilus_directory_check_if_ready_internal (NautilusDirectory      *directory,
                                            NautilusFile           *file,
                                            NautilusFileAttributes  file_attributes)
{
    Request request;

    g_assert (NAUTILUS_IS_DIRECTORY (directory));

    request = nautilus_directory_set_up_request (file_attributes);
    return request_is_satisfied (directory, file, request);
}
