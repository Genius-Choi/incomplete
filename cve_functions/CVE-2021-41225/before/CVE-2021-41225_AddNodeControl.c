NodeDef* AutoParallel::AddNodeControl(const string& name,
                                      const std::set<string>& deps,
                                      GraphDef* graph) {
  NodeDef* node = graph->add_node();
  node->set_name(name);
  node->set_op("NoOp");
  for (const auto& dep : deps) {
    node->add_input(strings::StrCat("^", dep));
  }
  return node;
}
