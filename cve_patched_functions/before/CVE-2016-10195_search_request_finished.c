search_request_finished(struct evdns_request *const handle) {
	ASSERT_LOCKED(handle->current_req->base);
	if (handle->search_state) {
		search_state_decref(handle->search_state);
		handle->search_state = NULL;
	}
	if (handle->search_origname) {
		mm_free(handle->search_origname);
		handle->search_origname = NULL;
	}
}
