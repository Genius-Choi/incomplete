static void o2nm_cluster_group_drop_item(struct config_group *group, struct config_item *item)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster(item);

	BUG_ON(o2nm_single_cluster != cluster);
	o2nm_single_cluster = NULL;

	configfs_remove_default_groups(&cluster->cl_group);
	config_item_put(item);
}
