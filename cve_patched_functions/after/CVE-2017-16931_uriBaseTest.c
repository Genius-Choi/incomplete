uriBaseTest(const char *filename,
             const char *result,
             const char *err,
             int options ATTRIBUTE_UNUSED) {
    return(uriCommonTest(filename, result, err,
                         "http://foo.com/path/to/index.html?orig#help"));
}
