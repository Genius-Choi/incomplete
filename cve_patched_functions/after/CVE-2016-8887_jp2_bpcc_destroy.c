static void jp2_bpcc_destroy(jp2_box_t *box)
{
	jp2_bpcc_t *bpcc = &box->data.bpcc;
	if (bpcc->bpcs) {
		jas_free(bpcc->bpcs);
		bpcc->bpcs = 0;
	}
}
