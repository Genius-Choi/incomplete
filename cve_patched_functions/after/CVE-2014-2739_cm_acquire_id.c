static struct cm_id_private * cm_acquire_id(__be32 local_id, __be32 remote_id)
{
	struct cm_id_private *cm_id_priv;

	spin_lock_irq(&cm.lock);
	cm_id_priv = cm_get_id(local_id, remote_id);
	spin_unlock_irq(&cm.lock);

	return cm_id_priv;
}
