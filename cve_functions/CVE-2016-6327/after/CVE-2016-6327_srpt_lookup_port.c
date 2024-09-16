static struct srpt_port *srpt_lookup_port(const char *name)
{
	struct srpt_port *sport;

	spin_lock(&srpt_dev_lock);
	sport = __srpt_lookup_port(name);
	spin_unlock(&srpt_dev_lock);

	return sport;
}
