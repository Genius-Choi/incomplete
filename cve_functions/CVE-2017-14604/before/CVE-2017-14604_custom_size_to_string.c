custom_size_to_string (char    *format,
                       va_list  va)
{
    goffset size;

    size = va_arg (va, goffset);
    return g_format_size (size);
}
