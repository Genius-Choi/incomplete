z_triple(const char *class, const char *inst, const char *recipient)
{
    if (!*recipient)
	recipient = "*";
    snprintf(z_buf, sizeof(z_buf), "<%s,%s,%s>", class, inst, recipient);
    z_buf[sizeof(z_buf)-1] = '\0';
    return z_buf;
}
