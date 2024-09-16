static int emulator_pio_in_emulated(int size, unsigned short port, void *val,
			     unsigned int count, struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.pio.count)
		goto data_avail;

	trace_kvm_pio(0, port, size, 1);

	vcpu->arch.pio.port = port;
	vcpu->arch.pio.in = 1;
	vcpu->arch.pio.count  = count;
	vcpu->arch.pio.size = size;

	if (!kernel_pio(vcpu, vcpu->arch.pio_data)) {
	data_avail:
		memcpy(val, vcpu->arch.pio_data, size * count);
		vcpu->arch.pio.count = 0;
		return 1;
	}

	vcpu->run->exit_reason = KVM_EXIT_IO;
	vcpu->run->io.direction = KVM_EXIT_IO_IN;
	vcpu->run->io.size = size;
	vcpu->run->io.data_offset = KVM_PIO_PAGE_OFFSET * PAGE_SIZE;
	vcpu->run->io.count = count;
	vcpu->run->io.port = port;

	return 0;
}
