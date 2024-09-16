initializeLibxml2(void) {
    xmlGetWarningsDefaultValue = 0;
    xmlPedanticParserDefault(0);

    xmlMemSetup(xmlMemFree, xmlMemMalloc, xmlMemRealloc, xmlMemoryStrdup);
    xmlInitParser();
    xmlSetExternalEntityLoader(testExternalEntityLoader);
    xmlSetStructuredErrorFunc(NULL, testStructuredErrorHandler);
#ifdef LIBXML_SCHEMAS_ENABLED
    xmlSchemaInitTypes();
    xmlRelaxNGInitTypes();
#endif
}
