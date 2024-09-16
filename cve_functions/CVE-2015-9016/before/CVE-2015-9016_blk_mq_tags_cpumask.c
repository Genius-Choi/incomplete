struct cpumask *blk_mq_tags_cpumask(struct blk_mq_tags *tags)
{
	return tags->cpumask;
}
