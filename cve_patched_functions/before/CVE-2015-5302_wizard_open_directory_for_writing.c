struct dump_dir *wizard_open_directory_for_writing(const char *dump_dir_name)
{
    struct dump_dir *dd = open_directory_for_writing(dump_dir_name,
                                                     ask_continue_before_steal);

    if (dd && strcmp(g_dump_dir_name, dd->dd_dirname) != 0)
    {
        char *old_name = g_dump_dir_name;
        g_dump_dir_name = xstrdup(dd->dd_dirname);
        update_window_title();
        free(old_name);
    }

    return dd;
}
