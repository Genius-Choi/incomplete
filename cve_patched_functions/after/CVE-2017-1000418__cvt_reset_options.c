void _cvt_reset_options (void) {
    _WM_Lock(&WM_ConvertOptions.lock);
    WM_ConvertOptions.xmi_convert_type = 0;
    WM_ConvertOptions.frequency = 0;
    _WM_Unlock(&WM_ConvertOptions.lock);
}
