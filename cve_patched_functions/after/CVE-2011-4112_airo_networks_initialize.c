static void airo_networks_initialize(struct airo_info *ai)
{
	int i;

	INIT_LIST_HEAD(&ai->network_free_list);
	INIT_LIST_HEAD(&ai->network_list);
	for (i = 0; i < AIRO_MAX_NETWORK_COUNT; i++)
		list_add_tail(&ai->networks[i].list,
			      &ai->network_free_list);
}
