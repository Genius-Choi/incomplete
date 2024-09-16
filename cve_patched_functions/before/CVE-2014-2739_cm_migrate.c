static int cm_migrate(struct ib_cm_id *cm_id)
{
	struct cm_id_private *cm_id_priv;
	unsigned long flags;
	int ret = 0;

	cm_id_priv = container_of(cm_id, struct cm_id_private, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	if (cm_id->state == IB_CM_ESTABLISHED &&
	    (cm_id->lap_state == IB_CM_LAP_UNINIT ||
	     cm_id->lap_state == IB_CM_LAP_IDLE)) {
		cm_id->lap_state = IB_CM_LAP_IDLE;
		cm_id_priv->av = cm_id_priv->alt_av;
	} else
		ret = -EINVAL;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	return ret;
}
