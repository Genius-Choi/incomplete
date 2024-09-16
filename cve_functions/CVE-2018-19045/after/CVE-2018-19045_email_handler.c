email_handler(vector_t *strvec)
{
	vector_t *email_vec = read_value_block(strvec);
	unsigned int i;
	char *str;

	if (!email_vec) {
		report_config_error(CONFIG_GENERAL_ERROR, "Warning - empty notification_email block");
		return;
	}

	for (i = 0; i < vector_size(email_vec); i++) {
		str = vector_slot(email_vec, i);
		alloc_email(str);
	}

	free_strvec(email_vec);
}
