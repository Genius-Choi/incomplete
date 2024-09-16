gdImagePtr gdImageCreateFromJpegPtr (int size, void *data)
{
	return gdImageCreateFromJpegPtrEx(size, data, 1);
}
