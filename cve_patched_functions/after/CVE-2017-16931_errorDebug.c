errorDebug(void *ctx ATTRIBUTE_UNUSED, const char *msg, ...)
{
    va_list args;

    callbacks++;
    if (quiet)
	return;
    va_start(args, msg);
    fprintf(SAXdebug, "SAX.error: ");
    vfprintf(SAXdebug, msg, args);
    va_end(args);
}
