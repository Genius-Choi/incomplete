get_control_selector_name(guint8 entity_id, guint8 control_sel, usb_conv_info_t *usb_conv_info)
{
    const gchar      *control_name = NULL;
    value_string_ext *selectors = NULL;

    selectors = get_control_selector_values(entity_id, usb_conv_info);

    if (selectors)
        control_name = try_val_to_str_ext(control_sel, selectors);

    return control_name;
}
