xmlParseEnumerationType(xmlParserCtxtPtr ctxt) {
    xmlChar *name;
    xmlEnumerationPtr ret = NULL, last = NULL, cur, tmp;

    if (RAW != '(') {
	xmlFatalErr(ctxt, XML_ERR_ATTLIST_NOT_STARTED, NULL);
	return(NULL);
    }
    SHRINK;
    do {
        NEXT;
	SKIP_BLANKS;
        name = xmlParseNmtoken(ctxt);
	if (name == NULL) {
	    xmlFatalErr(ctxt, XML_ERR_NMTOKEN_REQUIRED, NULL);
	    return(ret);
	}
	tmp = ret;
	while (tmp != NULL) {
	    if (xmlStrEqual(name, tmp->name)) {
		xmlValidityError(ctxt, XML_DTD_DUP_TOKEN,
	  "standalone: attribute enumeration value token %s duplicated\n",
				 name, NULL);
		if (!xmlDictOwns(ctxt->dict, name))
		    xmlFree(name);
		break;
	    }
	    tmp = tmp->next;
	}
	if (tmp == NULL) {
	    cur = xmlCreateEnumeration(name);
	    if (!xmlDictOwns(ctxt->dict, name))
		xmlFree(name);
	    if (cur == NULL) {
                xmlFreeEnumeration(ret);
                return(NULL);
            }
	    if (last == NULL) ret = last = cur;
	    else {
		last->next = cur;
		last = cur;
	    }
	}
	SKIP_BLANKS;
    } while (RAW == '|');
    if (RAW != ')') {
	xmlFatalErr(ctxt, XML_ERR_ATTLIST_NOT_FINISHED, NULL);
	return(ret);
    }
    NEXT;
    return(ret);
}
