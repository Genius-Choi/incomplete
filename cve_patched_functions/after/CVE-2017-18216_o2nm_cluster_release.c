static void o2nm_cluster_release(struct config_item *item)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster(item);

	kfree(cluster);
}
