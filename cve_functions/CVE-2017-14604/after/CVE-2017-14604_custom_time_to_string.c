custom_time_to_string (char    *format,
                       va_list  va)
{
    int secs;

    secs = va_arg (va, int);
    return format_time (secs);
}
