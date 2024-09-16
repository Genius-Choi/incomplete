http_swallow_body(struct http *hp, char * const *hh, int body)
{
	char *p;
	int i, l, ll;

	ll = 0;
	p = http_find_header(hh, "content-length");
	if (p != NULL) {
		l = strtoul(p, NULL, 0);
		(void)http_rxchar(hp, l, 0);
		vtc_dump(hp->vl, 4, "body", hp->body, l);
		hp->bodyl = l;
		sprintf(hp->bodylen, "%d", l);
		return;
	}
	p = http_find_header(hh, "transfer-encoding");
	if (p != NULL && !strcmp(p, "chunked")) {
		while (http_rxchunk(hp) != 0)
			continue;
		vtc_dump(hp->vl, 4, "body", hp->body, ll);
		ll = hp->rxbuf + hp->prxbuf - hp->body;
		hp->bodyl = ll;
		sprintf(hp->bodylen, "%d", ll);
		return;
	}
	if (body) {
		hp->body = hp->rxbuf + hp->prxbuf;
		do  {
			i = http_rxchar(hp, 1, 1);
			ll += i;
		} while (i > 0);
		vtc_dump(hp->vl, 4, "rxeof", hp->body, ll);
	}
	hp->bodyl = ll;
	sprintf(hp->bodylen, "%d", ll);
}
