static int conf__attempt_resolve(const char *host, const char *text, int log, const char *msg)
{
	struct addrinfo gai_hints;
	struct addrinfo *gai_res;
	int rc;

	memset(&gai_hints, 0, sizeof(struct addrinfo));
	gai_hints.ai_family = AF_UNSPEC;
	gai_hints.ai_socktype = SOCK_STREAM;
	gai_res = NULL;
	rc = getaddrinfo(host, NULL, &gai_hints, &gai_res);
	if(gai_res){
		freeaddrinfo(gai_res);
	}
	if(rc != 0){
#ifndef WIN32
		if(rc == EAI_SYSTEM){
			if(errno == ENOENT){
				log__printf(NULL, log, "%s: Unable to resolve %s %s.", msg, text, host);
			}else{
				log__printf(NULL, log, "%s: Error resolving %s: %s.", msg, text, strerror(errno));
			}
		}else{
			log__printf(NULL, log, "%s: Error resolving %s: %s.", msg, text, gai_strerror(rc));
		}
#else
		if(rc == WSAHOST_NOT_FOUND){
			log__printf(NULL, log, "%s: Error resolving %s.", msg, text);
		}
#endif
		return MOSQ_ERR_INVAL;
	}
	return MOSQ_ERR_SUCCESS;
}
