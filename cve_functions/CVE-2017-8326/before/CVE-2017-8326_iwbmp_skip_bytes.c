static int iwbmp_skip_bytes(struct iwbmprcontext *rctx, size_t n)
{
	iw_byte buf[1024];
	size_t still_to_read;
	size_t num_to_read;

	still_to_read = n;
	while(still_to_read>0) {
		num_to_read = still_to_read;
		if(num_to_read>1024) num_to_read=1024;
		if(!iwbmp_read(rctx,buf,num_to_read)) {
			return 0;
		}
		still_to_read -= num_to_read;
	}
	return 1;
}
