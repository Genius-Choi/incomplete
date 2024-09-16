static void jp2_cdef_dumpdata(jp2_box_t *box, FILE *out)
{
	jp2_cdef_t *cdef = &box->data.cdef;
	unsigned int i;
	for (i = 0; i < cdef->numchans; ++i) {
		fprintf(out,
		  "channo=%"PRIuFAST16"; type=%"PRIuFAST16"; assoc=%"PRIuFAST16"\n",
		  cdef->ents[i].channo, cdef->ents[i].type, cdef->ents[i].assoc);
	}
}
