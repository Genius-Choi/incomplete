static void __rtc_irq_eoi_tracking_restore_one(struct kvm_vcpu *vcpu)
{
	bool new_val, old_val;
	struct kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;
	struct dest_map *dest_map = &ioapic->rtc_status.dest_map;
	union kvm_ioapic_redirect_entry *e;

	e = &ioapic->redirtbl[RTC_GSI];
	if (!kvm_apic_match_dest(vcpu, NULL, 0,	e->fields.dest_id,
				e->fields.dest_mode))
		return;

	new_val = kvm_apic_pending_eoi(vcpu, e->fields.vector);
	old_val = test_bit(vcpu->vcpu_id, dest_map->map);

	if (new_val == old_val)
		return;

	if (new_val) {
		__set_bit(vcpu->vcpu_id, dest_map->map);
		dest_map->vectors[vcpu->vcpu_id] = e->fields.vector;
		ioapic->rtc_status.pending_eoi++;
	} else {
		__clear_bit(vcpu->vcpu_id, dest_map->map);
		ioapic->rtc_status.pending_eoi--;
		rtc_status_pending_eoi_check_valid(ioapic);
	}
}
