void kvm_register_irq_ack_notifier(struct kvm *kvm,
				   struct kvm_irq_ack_notifier *kian)
{
	mutex_lock(&kvm->irq_lock);
	hlist_add_head_rcu(&kian->link, &kvm->irq_ack_notifier_list);
	mutex_unlock(&kvm->irq_lock);
	kvm_arch_post_irq_ack_notifier_list_update(kvm);
}
