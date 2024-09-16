mailimap_body_type_1part_free(struct mailimap_body_type_1part * bt1p)
{
  switch (bt1p->bd_type) {
  case MAILIMAP_BODY_TYPE_1PART_BASIC:
    mailimap_body_type_basic_free(bt1p->bd_data.bd_type_basic);
    break;
  case MAILIMAP_BODY_TYPE_1PART_MSG:
    mailimap_body_type_msg_free(bt1p->bd_data.bd_type_msg);
    break;
  case MAILIMAP_BODY_TYPE_1PART_TEXT:
    mailimap_body_type_text_free(bt1p->bd_data.bd_type_text);
    break;
  }
  if (bt1p->bd_ext_1part)
    mailimap_body_ext_1part_free(bt1p->bd_ext_1part);

  free(bt1p);
}
