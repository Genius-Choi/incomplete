void AutoParallel::AddSharedNodes(GraphDef* graph) {
  string prefix = strings::StrCat(kAutoParallelPrefix, "-Replica-", 0);
  for (const auto& node : shared_nodes_) {
    auto new_node = graph->add_node();
    *new_node = *all_nodes_[node];
    for (int i = 0; i < new_node->input_size(); i++) {
      if (NotSharedNode(NodeName(new_node->input(i)))) {
        string new_name = AddPrefixToNodeName(new_node->input(i), prefix);
        *new_node->mutable_input(i) = new_name;
      }
    }
  }
}
