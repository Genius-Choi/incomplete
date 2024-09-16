xmlAttrNormalizeSpace2(xmlParserCtxtPtr ctxt, xmlChar *src, int *len)
{
    int i;
    int remove_head = 0;
    int need_realloc = 0;
    const xmlChar *cur;

    if ((ctxt == NULL) || (src == NULL) || (len == NULL))
        return(NULL);
    i = *len;
    if (i <= 0)
        return(NULL);

    cur = src;
    while (*cur == 0x20) {
        cur++;
	remove_head++;
    }
    while (*cur != 0) {
	if (*cur == 0x20) {
	    cur++;
	    if ((*cur == 0x20) || (*cur == 0)) {
	        need_realloc = 1;
		break;
	    }
	} else
	    cur++;
    }
    if (need_realloc) {
        xmlChar *ret;

	ret = xmlStrndup(src + remove_head, i - remove_head + 1);
	if (ret == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    return(NULL);
	}
	xmlAttrNormalizeSpace(ret, ret);
	*len = (int) strlen((const char *)ret);
        return(ret);
    } else if (remove_head) {
        *len -= remove_head;
        memmove(src, src + remove_head, 1 + *len);
	return(src);
    }
    return(NULL);
}
