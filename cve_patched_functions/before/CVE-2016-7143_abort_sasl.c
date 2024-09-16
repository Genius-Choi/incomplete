abort_sasl(struct Client *data)
{
	if(data->localClient->sasl_out == 0 || data->localClient->sasl_complete)
		return;

	data->localClient->sasl_out = data->localClient->sasl_complete = 0;
	ServerStats.is_sbad++;

	if(!IsClosing(data))
		sendto_one(data, form_str(ERR_SASLABORTED), me.name, EmptyString(data->name) ? "*" : data->name);

	if(*data->localClient->sasl_agent)
	{
		struct Client *agent_p = find_id(data->localClient->sasl_agent);
		if(agent_p)
		{
			sendto_one(agent_p, ":%s ENCAP %s SASL %s %s D A", me.id, agent_p->servptr->name,
					data->id, agent_p->id);
			return;
		}
	}

	sendto_server(NULL, NULL, CAP_TS6|CAP_ENCAP, NOCAPS, ":%s ENCAP * SASL %s * D A", me.id,
			data->id);
}
