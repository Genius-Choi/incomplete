http_PutResponse(struct worker *w, int fd, const struct http *to,
    const char *response)
{

	http_PutField(w, fd, to, HTTP_HDR_RESPONSE, response);
	if (to->hd[HTTP_HDR_RESPONSE].b == NULL)
		http_SetH(to, HTTP_HDR_RESPONSE, "Lost Response");
	Tcheck(to->hd[HTTP_HDR_RESPONSE]);
}
