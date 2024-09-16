testExternalEntityLoader(const char *URL, const char *ID,
			 xmlParserCtxtPtr ctxt) {
    xmlParserInputPtr ret;

    if (checkTestFile(URL)) {
	ret = xmlNoNetExternalEntityLoader(URL, ID, ctxt);
    } else {
	int memused = xmlMemUsed();
	ret = xmlNoNetExternalEntityLoader(URL, ID, ctxt);
	extraMemoryFromResolver += xmlMemUsed() - memused;
    }

    return(ret);
}
