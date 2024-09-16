http_ForceGet(const struct http *to)
{
	if (strcmp(http_GetReq(to), "GET"))
		http_SetH(to, HTTP_HDR_REQ, "GET");
}
