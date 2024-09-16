fetch_next_email(smtp_t * smtp)
{
	return list_element(global_data->email, smtp->email_it);
}
