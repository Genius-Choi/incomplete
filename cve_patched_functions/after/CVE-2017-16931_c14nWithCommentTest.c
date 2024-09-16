c14nWithCommentTest(const char *filename,
                    const char *resul ATTRIBUTE_UNUSED,
		    const char *err ATTRIBUTE_UNUSED,
		    int options ATTRIBUTE_UNUSED) {
    return(c14nCommonTest(filename, 1, XML_C14N_1_0, "with-comments"));
}
