static int jas_icccurv_getsize(jas_iccattrval_t *attrval)
{
	jas_icccurv_t *curv = &attrval->data.curv;
	return 4 + 2 * curv->numents;
}
