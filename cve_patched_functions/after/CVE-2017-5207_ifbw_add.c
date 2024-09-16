static void ifbw_add(IFBW *ptr) {
	assert(ptr);

	if (ifbw != NULL)
		ptr->next = ifbw;
	ifbw = ptr;
}
