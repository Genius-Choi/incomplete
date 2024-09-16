static bool event_need_review(const char *event_name)
{
    event_config_t *event_cfg = get_event_config(event_name);
    return !event_cfg || !event_cfg->ec_skip_review;
}
