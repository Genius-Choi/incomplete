base64Flush(message *m, unsigned char *buf)
{
	cli_dbgmsg("%d trailing bytes to export\n", m->base64chars);

	if(m->base64chars) {
		unsigned char *ret = decode(m, NULL, buf, base64, FALSE);

		m->base64chars = 0;

		return ret;
	}
	return NULL;
}
