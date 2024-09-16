str_to_lower(const char *string)
{
    char *zb_string;

    strncpy(z_buf, string, sizeof(z_buf));
    z_buf[sizeof(z_buf)-1] = '\0';

    zb_string = z_buf;
    while (*zb_string) {
	*zb_string = tolower((unsigned char)(*zb_string));
	zb_string++;
    }

    return z_buf;
}
