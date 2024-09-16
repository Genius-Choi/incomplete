static void inode_tree_add(struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_inode *entry;
	struct rb_node **p;
	struct rb_node *parent;
	u64 ino = btrfs_ino(inode);
again:
	p = &root->inode_tree.rb_node;
	parent = NULL;

	if (inode_unhashed(inode))
		return;

	spin_lock(&root->inode_lock);
	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct btrfs_inode, rb_node);

		if (ino < btrfs_ino(&entry->vfs_inode))
			p = &parent->rb_left;
		else if (ino > btrfs_ino(&entry->vfs_inode))
			p = &parent->rb_right;
		else {
			WARN_ON(!(entry->vfs_inode.i_state &
				  (I_WILL_FREE | I_FREEING)));
			rb_erase(parent, &root->inode_tree);
			RB_CLEAR_NODE(parent);
			spin_unlock(&root->inode_lock);
			goto again;
		}
	}
	rb_link_node(&BTRFS_I(inode)->rb_node, parent, p);
	rb_insert_color(&BTRFS_I(inode)->rb_node, &root->inode_tree);
	spin_unlock(&root->inode_lock);
}
