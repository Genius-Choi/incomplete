http_StatusMessage(unsigned status)
{
	struct http_msg *mp;

	assert(status >= 100 && status <= 999);
	for (mp = http_msg; mp->nbr != 0 && mp->nbr <= status; mp++)
		if (mp->nbr == status)
			return (mp->txt);
	return ("Unknown Error");
}
