char *stristr_full(const char *data, const char *key)
{
        return strstr_full_case(data, key, TRUE);
}
