static int parse_location(HTTPContext *s, const char *p)
{
    char redirected_location[MAX_URL_SIZE], *new_loc;
    ff_make_absolute_url(redirected_location, sizeof(redirected_location),
                         s->location, p);
    new_loc = av_strdup(redirected_location);
    if (!new_loc)
        return AVERROR(ENOMEM);
    av_free(s->location);
    s->location = new_loc;
    return 0;
}
