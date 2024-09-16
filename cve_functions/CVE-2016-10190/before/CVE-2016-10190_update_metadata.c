static void update_metadata(HTTPContext *s, char *data)
{
    char *key;
    char *val;
    char *end;
    char *next = data;

    while (*next) {
        key = next;
        val = strstr(key, "='");
        if (!val)
            break;
        end = strstr(val, "';");
        if (!end)
            break;

        *val = '\0';
        *end = '\0';
        val += 2;

        av_dict_set(&s->metadata, key, val, 0);

        next = end + 2;
    }
}
