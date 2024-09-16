conv_form_encoding(Str val, FormItemList *fi, Buffer *buf)
{
    wc_ces charset = SystemCharset;

    if (fi->parent->charset)
	charset = fi->parent->charset;
    else if (buf->document_charset && buf->document_charset != WC_CES_US_ASCII)
	charset = buf->document_charset;
    return wc_Str_conv_strict(val, InnerCharset, charset);
}
