int platform_device_add_properties(struct platform_device *pdev,
				   struct property_entry *properties)
{
	return device_add_properties(&pdev->dev, properties);
}
