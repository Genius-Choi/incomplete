HTTP_Copy(struct http *to, const struct http * const fm)
{

	to->conds = fm->conds;
	to->logtag = fm->logtag;
	to->status = fm->status;
	to->protover = fm->protover;
	to->nhd = fm->nhd;
	assert(fm->nhd <= to->shd);
	memcpy(to->hd, fm->hd, fm->nhd * sizeof *to->hd);
	memcpy(to->hdf, fm->hdf, fm->nhd * sizeof *to->hdf);
}
