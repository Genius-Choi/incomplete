void *dev_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct net_device *dev = (v == SEQ_START_TOKEN) ?
				  first_net_device(seq_file_net(seq)) :
				  next_net_device((struct net_device *)v);

	++*pos;
	return rcu_dereference(dev);
}
