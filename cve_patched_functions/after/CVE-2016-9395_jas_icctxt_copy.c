static int jas_icctxt_copy(jas_iccattrval_t *attrval,
  jas_iccattrval_t *othattrval)
{
	jas_icctxt_t *txt = &attrval->data.txt;
	jas_icctxt_t *othtxt = &othattrval->data.txt;
	if (!(txt->string = jas_strdup(othtxt->string)))
		return -1;
	return 0;
}
