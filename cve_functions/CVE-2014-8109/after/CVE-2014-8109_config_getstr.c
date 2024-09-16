static apr_size_t config_getstr(ap_configfile_t *cfg, char *buf,
                                size_t bufsiz)
{
    apr_size_t i = 0;

    if (cfg->getstr) {
        apr_status_t rc = (cfg->getstr) (buf, bufsiz, cfg->param);
        if (rc == APR_SUCCESS) {
            i = strlen(buf);
            if (i && buf[i - 1] == '\n')
                ++cfg->line_number;
        }
        else {
            buf[0] = '\0';
            i = 0;
        }
    }
    else {
        while (i < bufsiz) {
            char ch;
            apr_status_t rc = (cfg->getch) (&ch, cfg->param);
            if (rc != APR_SUCCESS)
                break;
            buf[i++] = ch;
            if (ch == '\n') {
                ++cfg->line_number;
                break;
            }
        }
    }
    return i;
}
