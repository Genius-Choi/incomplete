c14nExcWithoutCommentTest(const char *filename,
                    const char *resul ATTRIBUTE_UNUSED,
		    const char *err ATTRIBUTE_UNUSED,
		    int options ATTRIBUTE_UNUSED) {
    return(c14nCommonTest(filename, 0, XML_C14N_EXCLUSIVE_1_0, "exc-without-comments"));
}
