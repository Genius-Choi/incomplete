smtphelo_handler(vector_t *strvec)
{
	char *helo_name;

	if (vector_size(strvec) < 2)
		return;

	helo_name = MALLOC(strlen(strvec_slot(strvec, 1)) + 1);
	if (!helo_name)
		return;

	strcpy(helo_name, strvec_slot(strvec, 1));
	global_data->smtp_helo_name = helo_name;
}
