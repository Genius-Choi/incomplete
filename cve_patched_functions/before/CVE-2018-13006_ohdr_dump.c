GF_Err ohdr_dump(GF_Box *a, FILE * trace)
{
	GF_OMADRMCommonHeaderBox *ptr = (GF_OMADRMCommonHeaderBox *)a;
	gf_isom_box_dump_start(a, "OMADRMCommonHeaderBox", trace);

	fprintf(trace, "EncryptionMethod=\"%d\" PaddingScheme=\"%d\" PlaintextLength=\""LLD"\" ",
	        ptr->EncryptionMethod, ptr->PaddingScheme, ptr->PlaintextLength);
	if (ptr->RightsIssuerURL) fprintf(trace, "RightsIssuerURL=\"%s\" ", ptr->RightsIssuerURL);
	if (ptr->ContentID) fprintf(trace, "ContentID=\"%s\" ", ptr->ContentID);
	if (ptr->TextualHeaders) {
		u32 i, offset;
		char *start = ptr->TextualHeaders;
		fprintf(trace, "TextualHeaders=\"");
		i=offset=0;
		while (i<ptr->TextualHeadersLen) {
			if (start[i]==0) {
				fprintf(trace, "%s ", start+offset);
				offset=i+1;
			}
			i++;
		}
		fprintf(trace, "%s\"  ", start+offset);
	}

	fprintf(trace, ">\n");
	gf_isom_box_dump_done("OMADRMCommonHeaderBox", a, trace);
	return GF_OK;
}
