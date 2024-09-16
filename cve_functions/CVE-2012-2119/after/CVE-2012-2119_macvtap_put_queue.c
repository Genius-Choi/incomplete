static void macvtap_put_queue(struct macvtap_queue *q)
{
	struct macvlan_dev *vlan;

	spin_lock(&macvtap_lock);
	vlan = rcu_dereference_protected(q->vlan,
					 lockdep_is_held(&macvtap_lock));
	if (vlan) {
		int index = get_slot(vlan, q);

		RCU_INIT_POINTER(vlan->taps[index], NULL);
		RCU_INIT_POINTER(q->vlan, NULL);
		sock_put(&q->sk);
		--vlan->numvtaps;
	}

	spin_unlock(&macvtap_lock);

	synchronize_rcu();
	sock_put(&q->sk);
}
