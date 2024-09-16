static void __net_exit hwsim_exit_net(struct net *net)
{
	struct mac80211_hwsim_data *data, *tmp;

	spin_lock_bh(&hwsim_radio_lock);
	list_for_each_entry_safe(data, tmp, &hwsim_radios, list) {
		if (!net_eq(wiphy_net(data->hw->wiphy), net))
			continue;

		/* Radios created in init_net are returned to init_net. */
		if (data->netgroup == hwsim_net_get_netgroup(&init_net))
			continue;

		list_del(&data->list);
		rhashtable_remove_fast(&hwsim_radios_rht, &data->rht,
				       hwsim_rht_params);
		INIT_WORK(&data->destroy_work, destroy_radio);
		schedule_work(&data->destroy_work);
	}
	spin_unlock_bh(&hwsim_radio_lock);
}
