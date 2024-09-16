static void ocfs2_free_unwritten_list(struct inode *inode,
				 struct list_head *head)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_unwritten_extent *ue = NULL, *tmp = NULL;

	list_for_each_entry_safe(ue, tmp, head, ue_node) {
		list_del(&ue->ue_node);
		spin_lock(&oi->ip_lock);
		list_del(&ue->ue_ip_node);
		spin_unlock(&oi->ip_lock);
		kfree(ue);
	}
}
