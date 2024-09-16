HTTP_create(void *p, uint16_t nhttp)
{
	struct http *hp;

	hp = p;
	hp->magic = HTTP_MAGIC;
	hp->hd = (void*)(hp + 1);
	hp->shd = nhttp;
	hp->hdf = (void*)(hp->hd + nhttp);
	return (hp);
}
