IFBW *ifbw_find(const char *dev) {
	assert(dev);
	int len = strlen(dev);
	assert(len);
	
	if (ifbw == NULL)
		return NULL;
	
	IFBW *ptr = ifbw;
	while (ptr) {
		if (strncmp(ptr->txt, dev, len) == 0 && ptr->txt[len] == ':')
			return ptr;
		ptr = ptr->next;
	}
	
	return NULL;
}
