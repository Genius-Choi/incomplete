ExecuteSoapAction(struct upnphttp * h, const char * action, int n)
{
	char * p;
	char * p2;
	int i, len, methodlen;
	char namespace[256];

	/* SoapAction example :
	 * urn:schemas-upnp-org:service:WANIPConnection:1#GetStatusInfo */
	p = strchr(action, '#');
	if(p && (p - action) < n) {
		for(i = 0; i < ((int)sizeof(namespace) - 1) && (action + i) < p; i++)
			namespace[i] = action[i];
		namespace[i] = '\0';
		p++;
		p2 = strchr(p, '"');
		if(p2 && (p2 - action) <= n)
			methodlen = p2 - p;
		else
			methodlen = n - (p - action);
		/*syslog(LOG_DEBUG, "SoapMethod: %.*s %d %d %p %p %d",
		       methodlen, p, methodlen, n, action, p, (int)(p - action));*/
		for(i = 0; soapMethods[i].methodName; i++) {
			len = strlen(soapMethods[i].methodName);
			if((len == methodlen) && memcmp(p, soapMethods[i].methodName, len) == 0) {
#ifdef DEBUG
				syslog(LOG_DEBUG, "Remote Call of SoapMethod '%s' %s",
				       soapMethods[i].methodName, namespace);
#endif /* DEBUG */
				soapMethods[i].methodImpl(h, soapMethods[i].methodName, namespace);
				return;
			}
		}
		syslog(LOG_NOTICE, "SoapMethod: Unknown: %.*s %s", methodlen, p, namespace);
	} else {
		syslog(LOG_NOTICE, "cannot parse SoapAction");
	}

	SoapError(h, 401, "Invalid Action");
}
