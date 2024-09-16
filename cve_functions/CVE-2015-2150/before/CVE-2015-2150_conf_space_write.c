static int conf_space_write(struct pci_dev *dev,
			    const struct config_field_entry *entry,
			    int offset, u32 value)
{
	int ret = 0;
	const struct config_field *field = entry->field;

	switch (field->size) {
	case 1:
		if (field->u.b.write)
			ret = field->u.b.write(dev, offset, (u8) value,
					       entry->data);
		break;
	case 2:
		if (field->u.w.write)
			ret = field->u.w.write(dev, offset, (u16) value,
					       entry->data);
		break;
	case 4:
		if (field->u.dw.write)
			ret = field->u.dw.write(dev, offset, value,
						entry->data);
		break;
	}
	return ret;
}
