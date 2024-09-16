set_default_router_id(data_t *data, char *new_id)
{
	if (!new_id || !new_id[0])
		return;

	data->router_id = MALLOC(strlen(new_id)+1);
	strcpy(data->router_id, new_id);
}
