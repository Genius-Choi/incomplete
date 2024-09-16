xmlAttrNormalizeSpace(const xmlChar *src, xmlChar *dst)
{
    if ((src == NULL) || (dst == NULL))
        return(NULL);

    while (*src == 0x20) src++;
    while (*src != 0) {
	if (*src == 0x20) {
	    while (*src == 0x20) src++;
	    if (*src != 0)
		*dst++ = 0x20;
	} else {
	    *dst++ = *src++;
	}
    }
    *dst = 0;
    if (dst == src)
       return(NULL);
    return(dst);
}
