void netif_napi_del(struct napi_struct *napi)
{
	might_sleep();
	if (napi_hash_del(napi))
		synchronize_net();
	list_del_init(&napi->dev_list);
	napi_free_frags(napi);

	kfree_skb_list(napi->gro_list);
	napi->gro_list = NULL;
	napi->gro_count = 0;
}
