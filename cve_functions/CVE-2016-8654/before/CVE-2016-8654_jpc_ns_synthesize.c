int jpc_ns_synthesize(jpc_fix_t *a, int xstart, int ystart, int width,
  int height, int stride)
{

	int numrows = height;
	int numcols = width;
	int rowparity = ystart & 1;
	int colparity = xstart & 1;
	int maxcols;
	jpc_fix_t *startptr;
	int i;

	startptr = &a[0];
	for (i = 0; i < numrows; ++i) {
		jpc_ns_invlift_row(startptr, numcols, colparity);
		jpc_qmfb_join_row(startptr, numcols, colparity);
		startptr += stride;
	}

	maxcols = (numcols / JPC_QMFB_COLGRPSIZE) * JPC_QMFB_COLGRPSIZE;
	startptr = &a[0];
	for (i = 0; i < maxcols; i += JPC_QMFB_COLGRPSIZE) {
		jpc_ns_invlift_colgrp(startptr, numrows, stride, rowparity);
		jpc_qmfb_join_colgrp(startptr, numrows, stride, rowparity);
		startptr += JPC_QMFB_COLGRPSIZE;
	}
	if (maxcols < numcols) {
		jpc_ns_invlift_colres(startptr, numrows, numcols - maxcols, stride,
		  rowparity);
		jpc_qmfb_join_colres(startptr, numrows, numcols - maxcols, stride,
		  rowparity);
	}

	return 0;

}
