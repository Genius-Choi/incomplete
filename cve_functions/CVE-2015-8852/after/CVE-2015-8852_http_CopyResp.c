http_CopyResp(struct http *to, const struct http *fm)
{

	CHECK_OBJ_NOTNULL(fm, HTTP_MAGIC);
	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	http_SetH(to, HTTP_HDR_PROTO, "HTTP/1.1");
	to->status = fm->status;
	http_copyh(to, fm, HTTP_HDR_RESPONSE);
}
