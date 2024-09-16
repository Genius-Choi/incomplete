xml_log(int priority, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    qb_log_from_external_source_va(__FUNCTION__, __FILE__, fmt, priority, __LINE__, 0, ap);
    va_end(ap);
}
