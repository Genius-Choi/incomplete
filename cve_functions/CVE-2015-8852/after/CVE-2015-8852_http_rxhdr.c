http_rxhdr(struct http *hp)
{
	int i;
	char *p;

	CHECK_OBJ_NOTNULL(hp, HTTP_MAGIC);
	hp->prxbuf = 0;
	hp->body = NULL;
	while (1) {
		(void)http_rxchar(hp, 1, 0);
		p = hp->rxbuf + hp->prxbuf - 1;
		for (i = 0; p > hp->rxbuf; p--) {
			if (*p != '\n')
				break;
			if (p - 1 > hp->rxbuf && p[-1] == '\r')
				p--;
			if (++i == 2)
				break;
		}
		if (i == 2)
			break;
	}
	vtc_dump(hp->vl, 4, "rxhdr", hp->rxbuf, -1);
}
