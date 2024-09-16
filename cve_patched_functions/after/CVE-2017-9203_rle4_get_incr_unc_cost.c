static int rle4_get_incr_unc_cost(struct rle_context *rlectx)
{
	int n;
	int m;

	n = (int)rlectx->unc_len;

	if(n==2 || n==255 || n==257 || n==507 || n==510) return 2;
	if(n==256 || n==508) return 0;

	if(n>=759) {
		m = n%252;
		if(m==3 || m==6 || m==9) return 2;
		if(m==4 || m==8) return 0;
	}

	return (n%4)?0:2;
}
