http_GetReq(const struct http *hp)
{

	Tcheck(hp->hd[HTTP_HDR_REQ]);
	return (hp->hd[HTTP_HDR_REQ].b);
}
