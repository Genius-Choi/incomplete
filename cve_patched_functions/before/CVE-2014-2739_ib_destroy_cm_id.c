void ib_destroy_cm_id(struct ib_cm_id *cm_id)
{
	cm_destroy_id(cm_id, 0);
}
