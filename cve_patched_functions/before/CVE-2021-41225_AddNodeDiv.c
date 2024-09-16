NodeDef* AutoParallel::AddNodeDiv(const string& name, const string& input_a,
                                  const string& input_b) {
  NodeDef* node = graph_.add_node();
  node->set_name(strings::StrCat(kAutoParallelPrefix, "-Div-", name));
  node->set_op("RealDiv");
  node->add_input(input_a);
  node->add_input(input_b);
  AttrValue attr_type;
  attr_type.set_type(DT_FLOAT);
  node->mutable_attr()->insert({"T", attr_type});
  return node;
}
