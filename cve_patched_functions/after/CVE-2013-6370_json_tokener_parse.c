struct json_object* json_tokener_parse(const char *str)
{
    enum json_tokener_error jerr_ignored;
    struct json_object* obj;
    obj = json_tokener_parse_verbose(str, &jerr_ignored);
    return obj;
}
