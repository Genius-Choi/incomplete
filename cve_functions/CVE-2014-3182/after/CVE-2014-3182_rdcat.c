static void rdcat(char *rdesc, unsigned int *rsize, const char *data, unsigned int size)
{
	memcpy(rdesc + *rsize, data, size);
	*rsize += size;
}
