NameValueParserGetData(void * d, const char * datas, int l)
{
    struct NameValueParserData * data = (struct NameValueParserData *)d;
	if(strcmp(data->curelt, "NewPortListing") == 0)
	{
		/* specific case for NewPortListing which is a XML Document */
		data->portListing = malloc(l + 1);
		if(!data->portListing)
		{
			/* malloc error */
#ifdef DEBUG
			fprintf(stderr, "%s: error allocating memory",
			        "NameValueParserGetData");
#endif /* DEBUG */
			return;
		}
		memcpy(data->portListing, datas, l);
		data->portListing[l] = '\0';
		data->portListingLength = l;
	}
	else
	{
		/* standard case. */
		data->cdata = datas;
		data->cdatalen = l;
	}
}
