enum json_tokener_error json_tokener_get_error(json_tokener *tok)
{
	return tok->err;
}
