void socket_seq_show(struct seq_file *seq)
{
	int cpu;
	int counter = 0;

	for_each_possible_cpu(cpu)
	    counter += per_cpu(sockets_in_use, cpu);

	/* It can be negative, by the way. 8) */
	if (counter < 0)
		counter = 0;

	seq_printf(seq, "sockets: used %d\n", counter);
}
