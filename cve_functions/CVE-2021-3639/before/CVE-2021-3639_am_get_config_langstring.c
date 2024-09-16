const char *am_get_config_langstring(apr_hash_t *h, const char *lang)
{
    char *string;

    if (lang == NULL) {
        lang = "";
    }

    string = (char *)apr_hash_get(h, lang, APR_HASH_KEY_STRING);

    return string;
}
