NodeDef* AutoParallel::AddNodeDivConst() {
  NodeDef* node = graph_.add_node();
  node->set_name(strings::StrCat(kAutoParallelPrefix, "-Div-Const"));
  node->set_op("Const");

  AttrValue attr_data_type;
  attr_data_type.set_type(DT_FLOAT);
  node->mutable_attr()->insert({"dtype", attr_data_type});

  AttrValue attr_tensor;
  auto tensor = attr_tensor.mutable_tensor();
  tensor->add_float_val(static_cast<float>(num_replicas_));
  tensor->set_dtype(DT_FLOAT);
  node->mutable_attr()->insert({"value", attr_tensor});
  return node;
}
