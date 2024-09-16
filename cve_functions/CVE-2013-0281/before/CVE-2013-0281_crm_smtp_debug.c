crm_smtp_debug(const char *buf, int buflen, int writing, void *arg)
{
    char type = 0;
    int lpc = 0, last = 0, level = *(int *)arg;

    if (writing == SMTP_CB_HEADERS) {
        type = 'H';
    } else if (writing) {
        type = 'C';
    } else {
        type = 'S';
    }

    for (; lpc < buflen; lpc++) {
        switch (buf[lpc]) {
            case 0:
            case '\n':
                if (last > 0) {
                    do_crm_log(level, "   %.*s", lpc - last, buf + last);
                } else {
                    do_crm_log(level, "%c: %.*s", type, lpc - last, buf + last);
                }
                last = lpc + 1;
                break;
        }
    }
}
