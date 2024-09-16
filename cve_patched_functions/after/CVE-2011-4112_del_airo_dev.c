static void del_airo_dev(struct airo_info *ai)
{
	if (!ai->pci)
		list_del(&ai->dev_list);
}
