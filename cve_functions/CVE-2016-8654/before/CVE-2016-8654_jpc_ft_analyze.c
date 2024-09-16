int jpc_ft_analyze(jpc_fix_t *a, int xstart, int ystart, int width, int height,
  int stride)
{
	int numrows = height;
	int numcols = width;
	int rowparity = ystart & 1;
	int colparity = xstart & 1;
	int i;
	jpc_fix_t *startptr;
	int maxcols;

	maxcols = (numcols / JPC_QMFB_COLGRPSIZE) * JPC_QMFB_COLGRPSIZE;
	startptr = &a[0];
	for (i = 0; i < maxcols; i += JPC_QMFB_COLGRPSIZE) {
		jpc_qmfb_split_colgrp(startptr, numrows, stride, rowparity);
		jpc_ft_fwdlift_colgrp(startptr, numrows, stride, rowparity);
		startptr += JPC_QMFB_COLGRPSIZE;
	}
	if (maxcols < numcols) {
		jpc_qmfb_split_colres(startptr, numrows, numcols - maxcols, stride,
		  rowparity);
		jpc_ft_fwdlift_colres(startptr, numrows, numcols - maxcols, stride,
		  rowparity);
	}

	startptr = &a[0];
	for (i = 0; i < numrows; ++i) {
		jpc_qmfb_split_row(startptr, numcols, colparity);
		jpc_ft_fwdlift_row(startptr, numcols, colparity);
		startptr += stride;
	}

	return 0;

}
