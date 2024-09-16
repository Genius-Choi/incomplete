custom_mount_to_string (char    *format,
                        va_list  va)
{
    GMount *mount;

    mount = va_arg (va, GMount *);
    return g_mount_get_name (mount);
}
