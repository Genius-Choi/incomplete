static void jp2_cdef_destroy(jp2_box_t *box)
{
	jp2_cdef_t *cdef = &box->data.cdef;
	if (cdef->ents) {
		jas_free(cdef->ents);
		cdef->ents = 0;
	}
}
