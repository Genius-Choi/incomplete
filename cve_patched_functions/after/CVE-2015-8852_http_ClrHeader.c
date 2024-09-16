http_ClrHeader(struct http *to)
{

	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	to->nhd = HTTP_HDR_FIRST;
	to->status = 0;
	to->protover = 0;
	to->conds = 0;
	memset(to->hd, 0, sizeof *to->hd * to->shd);
}
