dump_head(Buffer *buf)
{
    TextListItem *ti;

    if (buf->document_header == NULL) {
	if (w3m_dump & DUMP_EXTRA)
	    printf("\n");
	return;
    }
    for (ti = buf->document_header->first; ti; ti = ti->next) {
#ifdef USE_M17N
	printf("%s",
	       wc_conv_strict(ti->ptr, InnerCharset,
			      buf->document_charset)->ptr);
#else
	printf("%s", ti->ptr);
#endif
    }
    puts("");
}
