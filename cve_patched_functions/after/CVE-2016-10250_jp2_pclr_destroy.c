static void jp2_pclr_destroy(jp2_box_t *box)
{
	jp2_pclr_t *pclr = &box->data.pclr;
	if (pclr->lutdata) {
		jas_free(pclr->lutdata);
	}
	if (pclr->bpc)
		jas_free(pclr->bpc);
}
