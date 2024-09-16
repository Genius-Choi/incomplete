xmlCleanSpecialAttr(xmlParserCtxtPtr ctxt)
{
    if (ctxt->attsSpecial == NULL)
        return;

    xmlHashScanFull(ctxt->attsSpecial, xmlCleanSpecialAttrCallback, ctxt);

    if (xmlHashSize(ctxt->attsSpecial) == 0) {
        xmlHashFree(ctxt->attsSpecial, NULL);
        ctxt->attsSpecial = NULL;
    }
    return;
}
