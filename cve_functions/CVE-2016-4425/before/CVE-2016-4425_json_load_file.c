json_t *json_load_file(const char *path, size_t flags, json_error_t *error)
{
    json_t *result;
    FILE *fp;

    jsonp_error_init(error, path);

    if (path == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    fp = fopen(path, "rb");
    if(!fp)
    {
        error_set(error, NULL, "unable to open %s: %s",
                  path, strerror(errno));
        return NULL;
    }

    result = json_loadf(fp, flags, error);

    fclose(fp);
    return result;
}
