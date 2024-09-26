# How to send Query to Joern Server : client.execute(your_query)

from cpgqls_client import CPGQLSClient
import os
import re
import pprint
import json

server_endpoint = "localhost:8080"
client = CPGQLSClient(server_endpoint)
file_path = "/home/youngjaechoi/incomplete/cve_patched_functions/before"


def process_file(file_name_withex):
    file_name = file_name_withex.split('.')[0]

    import_query = f'importCode("{file_path}", "{file_name_withex}")'
    print(f'Query: {import_query}')
    client.execute(import_query)

    client.execute('run.ossdataflow')
    print("Query: run.ossdataflow")

    cve_id = file_name.split('_')[0]
    function_name = file_name.split('_', 1)[-1]
    # print(function_name)
    analysis_query = f'cpg.method("{function_name}").dotCpg14.l'
    result = client.execute(analysis_query)

    print(f"DDG edges for function '{function_name}':")
    # pprint.pprint(result['stdout'])

    ddg_pattern = re.compile(r'(\d+)"\s+->\s+"(\d+)"\s+\[\s*label\s*=\s*"DDG:\s*([^"]*)"')
    ddg_edges = ddg_pattern.findall(result['stdout'])

    # Form: ('30064773051', '128849018905', 'BIO_pop(f)'); (Source, Target, Code); "30064773051" -> "128849018905"  [ label = "DDG: BIO_pop(f)"]
    # pprint.pprint(ddg_edges)

    # [('146028888104', '128849018903', '&lt;RET&gt;'),...]
    print(ddg_edges)

    #이제 몇번째 라인이 취약했는지 (패치에서 삭제되었는지) 를 미리 알아보고, 그 라인 정보를 가져와야함!!!
    #그렇게 가져온 라인 넘버를 line_numbers에서 찾고, 몇번째 항목인지 확인
    #지금의 경우 12번째 줄이니까, 12를 찾고, 이경우 첫번째 항목
    #cpg.method("{function_name}").call.id.l 실행


    #----------------------------------------call-----------------------------------------------------#
    call_query = f'cpg.method("{function_name}").call.l'

    print(f'Query: cpg.method("{function_name}").call.l')
    call_result = client.execute(call_query)

    line_number_pattern = re.compile(r'lineNumber\s*=\s*Some\(value\s*=\s*(\d+)\)')
    line_numbers = line_number_pattern.findall(call_result['stdout'])
    int_line_numbers = list(map(int, line_numbers))

    print(f'linenums with Call: {int_line_numbers}')

    with open('../json_data/patched_line_num.json', 'r') as f:
        patched_lines = json.load(f)

    matched_linenum = patched_lines.get(file_name_withex, [])
    print(f"linenums with Calls & Patched: {matched_linenum}")

    patched_idxs = []
    for linenum in matched_linenum:
        if linenum in int_line_numbers:
            whatidx_patched_line = int_line_numbers.index(linenum)
            # print(whatidx_patched_line)
            patched_idxs.append(whatidx_patched_line)
    print(f'idx of patched lines & with calls: {patched_idxs}')

    #------------------------------------------call.id-------------------------------------------------------#
    call_id_query = f'cpg.method("{function_name}").call.id.l'
    call_id_result = client.execute(call_id_query)

    calls_id_stdout = call_id_result['stdout']
    # print(calls_id_stdout)

    list_content = re.search(r'List\((.*?)\)', calls_id_stdout, re.DOTALL)
    if list_content:
        list_of_labels = re.findall(r'\d+L', list_content.group(1))
        list_of_labels = [num.rstrip('L') for num in list_of_labels]
        # pprint.pprint(f'label_with_call: {list_of_labels}')
        # print(type(list_of_labels))
        print(list_of_labels)

    matched_label = []
    for matched_idx in patched_idxs:
        matched_label.append(list_of_labels[matched_idx])
    
    print(matched_label)

    source_group = {}
    target_group = {}

    for label in matched_label:
        source_group[label] = []
        target_group[label] = []

    for edge in ddg_edges:
        source_id, target_id, code = edge
        if source_id in matched_label:
            source_group[source_id].append(edge)
        if target_id in matched_label:
            target_group[target_id].append(edge)

    for label in matched_label:
        print(f"Label: {label}")
        print("Source group:")
        for edge in source_group[label]:
            print(f"  {edge}")
        print("Target group:")
        for edge in target_group[label]:
            print(f"  {edge}")
        print()

    dep_result = {}
    for label in matched_label:
        dep_result[label] = {
            "source_group": source_group[label],
            "target_group": target_group[label]
        }

    return dep_result

all_results = {}
for filename in os.listdir(file_path):
    print(f"Processing file: {filename}")
    dep_result = process_file(filename)
    all_results[filename] = dep_result

    # client.execute('project.close')

with open('../json_data/found_dependency.json', 'w') as f:
    json.dump(all_results, f, indent=2)