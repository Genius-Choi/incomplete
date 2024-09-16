static void jp2_cdef_dumpdata(jp2_box_t *box, FILE *out)
{
	jp2_cdef_t *cdef = &box->data.cdef;
	unsigned int i;
	for (i = 0; i < cdef->numchans; ++i) {
		fprintf(out, "channo=%d; type=%d; assoc=%d\n",
		  cdef->ents[i].channo, cdef->ents[i].type, cdef->ents[i].assoc);
	}
}
