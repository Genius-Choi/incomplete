void jp2_box_destroy(jp2_box_t *box)
{
	if (box->ops->destroy) {
		(*box->ops->destroy)(box);
	}
	jas_free(box);
}
