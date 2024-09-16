GF_Err odtt_dump(GF_Box *a, FILE * trace)
{
	GF_OMADRMTransactionTrackingBox *ptr = (GF_OMADRMTransactionTrackingBox *)a;
	gf_isom_box_dump_start(a, "OMADRMTransactionTrackingBox", trace);

	fprintf(trace, "TransactionID=\"");
	dump_data(trace, ptr->TransactionID, 16);
	fprintf(trace, "\">\n");
	gf_isom_box_dump_done("OMADRMTransactionTrackingBox", a, trace);
	return GF_OK;
}
