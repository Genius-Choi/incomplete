http_PutStatus(struct http *to, uint16_t status)
{

	assert(status >= 100 && status <= 999);
	to->status = status;
}
