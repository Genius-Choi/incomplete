expat_start_cb(void *userData, const XML_Char *name, const XML_Char **atts)
{
	struct expat_userData *ud = (struct expat_userData *)userData;
	struct archive_read *a = ud->archive;
	struct xmlattr_list list;
	int r;

	r = expat_xmlattr_setup(a, &list, atts);
	if (r == ARCHIVE_OK)
		r = xml_start(a, (const char *)name, &list);
	xmlattr_cleanup(&list);
	ud->state = r;
}
