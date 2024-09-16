void AutoParallel::AddOneReplica(GraphDef* graph, int number) {
  string prefix = strings::StrCat(kAutoParallelPrefix, "-Replica-", number);
  for (const auto& node : replica_nodes_) {
    auto new_node = graph->add_node();
    *new_node = *all_nodes_[node];
    if (NotSharedNode(new_node->name())) {
      new_node->set_name(AddPrefixToNodeName(new_node->name(), prefix));
      if (num_gpus_ > 0) {
        new_node->set_device(strings::StrCat("/gpu:", number % num_gpus_));
      }
      for (int i = 0; i < new_node->input_size(); i++) {
        if (NotSharedNode(NodeName(new_node->input(i)))) {
          string new_name = AddPrefixToNodeName(new_node->input(i), prefix);
          *new_node->mutable_input(i) = new_name;
        }
      }
    }
  }
}
