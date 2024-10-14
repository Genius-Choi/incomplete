#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
# 여기가 중복제거 있는 헬프미존
CHECKPOINT_FILE = './checkpoint.json'

import json
import os
import glob
import subprocess
import re
import sys
import shutil
from cpgqls_client import CPGQLSClient

# file_path = "/home/youngjaechoi/incomplete_temp/final_patched_functions/before"
server_endpoint = "localhost:8080"
client = CPGQLSClient(server_endpoint)

def help_me_joren(output_file_path):
    file_name = output_file_path.rsplit('.', 1)[0]

    if 'before' in output_file_path:
        version = 'before'
        file_path = "/home/youngjaechoi/incomplete/final_patched_functions/before"
    elif 'after' in output_file_path:
        version = 'after'
        file_path = "/home/youngjaechoi/incomplete/final_patched_functions/after"

    import_path = os.path.join(file_path, os.path.relpath(output_file_path, f'./final_patched_functions/{version}'))
    # print(import_path)
    # print('@@@@@@')
    # print(file_path)
    # print(output_file_path)

    import_query = f'importCode("{import_path}")'
    # print(f'Query: {import_query}')
    client.execute(import_query)
    # time.sleep(1)

    client.execute('run.ossdataflow')
    # print("Query: run.ossdataflow")
    # time.sleep(1)


    cveid_match = re.search(r'CVE-\d{4}-\d{4,}', file_name)
    # cve_id = file_name.split('@@')[0]
    cve_id = cveid_match.group()
    # print(cve_id)
    function_name = file_name.rsplit('##', 1)[-1]
    # print('function name')
    # print(function_name)
    analysis_query = f'cpg.method("{function_name}").dotCpg14.l'
    result = client.execute(analysis_query)
    # time.sleep(1)

    # print(f"DDG edges for function '{function_name}':")
    # pprint.pprint(result['stdout'])
    if not os.path.exists('dotCpg14'):
        os.makedirs('dotCpg14')

    if os.path.exists(f"./dotCpg14/{file_name.split('/')[-1]}$${version}"):
        print('&&&&&&&&&')
        print(f"./dotCpg14/{file_name.split('/')[-1]}$${version} Already exists.", 'w')

    with open(f"./dotCpg14/{file_name.split('/')[-1]}$${version}", 'w') as f:
        f.write(result['stdout'])
    # f"{cve_folder}@{short_hash}@{safe_file_name}##{func['name']}{extension}"

    ddg_pattern = re.compile(r'(\d+)"\s+->\s+"(\d+)"\s+\[\s*label\s*=\s*"DDG:\s*([^"]*)"')
    ddg_edges = ddg_pattern.findall(result['stdout'])

    # Form: ('30064773051', '128849018905', 'BIO_pop(f)'); (Source, Target, Code); "30064773051" -> "128849018905"  [ label = "DDG: BIO_pop(f)"]
    # pprint.pprint(ddg_edges)

    # [('146028888104', '128849018903', '&lt;RET&gt;'),...]
    # print(ddg_edges)

    #이제 몇번째 라인이 취약했는지 (패치에서 삭제되었는지) 를 미리 알아보고, 그 라인 정보를 가져와야함!!!
    #그렇게 가져온 라인 넘버를 line_numbers에서 찾고, 몇번째 항목인지 확인
    #지금의 경우 12번째 줄이니까, 12를 찾고, 이경우 첫번째 항목
    #cpg.method("{function_name}").call.id.l 실행


    #----------------------------------------call-----------------------------------------------------#
    # call_query = f'cpg.method("{function_name}").call.l'

    # print(f'Query: cpg.method("{function_name}").call.l')
    # call_result = client.execute(call_query)

    # line_number_pattern = re.compile(r'lineNumber\s*=\s*Some\(value\s*=\s*(\d+)\)')
    # line_numbers = line_number_pattern.findall(call_result['stdout'])
    # int_line_numbers = list(map(int, line_numbers))

    # print(f'linenums with Call: {int_line_numbers}')

    #----------------------------------------call(9/23)-----------------------------------------------------#
    
    # 일단 cpg.call.code.l 쿼리를 쓰면, lineNumber쿼리와 정확히 매핑되어 코드가 나옴. (인덱스 같음)

    call_query = f'cpg.method("{function_name}").call.lineNumber.l'
    # print(f'Qurey : {call_query}')
    call_result = client.execute(call_query)
    call_result = call_result['stdout']
    # time.sleep(1)
    
    # pattern = r'List\(([\d, ]+)\)'
    # match = re.search(pattern, call_result)
    # # if match:
    # numbers_str = match.group(1)
    # int_line_numbers = [int(num.strip()) for num in numbers_str.split(',')]
    # print(f'linenums with Call: {int_line_numbers}')


    pattern = r'List\(\s*([\d,\s]+)\s*\)'
    match = re.search(pattern, call_result, re.DOTALL)
    if match:
        numbers_str = match.group(1)
        int_line_numbers = [int(num.strip()) for num in numbers_str.split(',')]
        # print(f'linenums with Call -> {int_line_numbers}')
    
    #----------------------------------------call.id(9/30)-----------------------------------------------------#

        # call.id.l과 call.lineNumber.l은 같은 인덱스. call.code.l도 같은 인덱슨걸로 봐서 call.somtehing.l 은 모두 같은 인덱스를 가질 것으로 추정

        call_id_query = f'cpg.method("{function_name}").call.id.l'
        # print(f'Query : {call_id_query}')
        call_id_result = client.execute(call_id_query)
        # time.sleep(1)

        # print(call_id_result['stdout'])
        labels = re.findall(r'(\d+)L', call_id_result['stdout'])
        label_list = [int(num) for num in labels]
        # print(f'linenums with Call(label) -> {label_list}')

        # todo.
        # importCode된 함수의 취약한 라인 (패치에서 삭제된) 을 미리 파악
        # 해당라인에서 Call이 발생하는지? -> DDG edge에서 해당 라인의 label을 찾을 수 있는지?
        # pre / post 모두 저장.
        label_to_line = dict(zip(label_list, int_line_numbers))

        results = {
            'before': {'pre': [], 'post': []},
            'after': {'pre': [], 'post': []}
        }

        pre_entries = {}
        post_entries = {}

        for label in label_list:
            label_str = str(label)
            line_number = label_to_line.get(label, None)

            if line_number is not None:
                try:
                    with open(import_path, 'r') as file:
                        lines = file.readlines()
                        if 1 <= line_number <= len(lines):
                            fullcodeline = lines[line_number - 1].strip()
                        else:
                            fullcodeline = None
                except Exception as e:
                    print("ㅠㅠ")
                    fullcodeline = None
            else:
                fullcodeline = None

            for edge in ddg_edges:
                source_label, target_id, code = edge
                if label_str == source_label:
                    key = (label, int(target_id), line_number)
                    entry = {
                        'source_id': label,
                        'target_id': int(target_id),
                        'line': line_number,
                        # 'pp': 'pre'
                        'code': code,
                        'fullcodeline': fullcodeline
                    }
                    existing_entry = pre_entries.get(key)
                    if existing_entry:
                        if len(code) > len(existing_entry['code']):
                            pre_entries[key] = entry
                    else:
                        pre_entries[key] = entry
                    
            for edge in ddg_edges:
                source_id, target_label, code = edge
                if label_str == target_label:
                    key = (int(source_id), label, line_number)
                    entry = {
                        'target_id': label,
                        'source_id': int(source_id),
                        'line': line_number,
                        # 'pp': 'post',
                        'code': code,
                        'fullcodeline': fullcodeline
                    }
                    existing_entry = post_entries.get(key)
                    if existing_entry:
                        if len(code) > len(existing_entry['code']):
                            post_entries[key] = entry
                    else:
                        post_entries[key] = entry

        results[version]['pre'] = list(pre_entries.values())
        results[version]['post'] = list(post_entries.values())
        save_results_as_directory_structure(cve_id, function_name, version, pre_entries, post_entries)


        # print(json.dumps(results, indent=4))
        json_file_path = './found_dependency.json'
        if not os.path.exists(json_file_path):
            with open(json_file_path, 'w') as f:
                json.dump({}, f, indent=4)

        with open(json_file_path, 'r') as f:
            data = json.load(f)

        if cve_id not in data:
            data[cve_id] = {}
        if function_name not in data[cve_id]:
            data[cve_id][function_name] = {'before': {'pre': [], 'post': []}, 'after': {'pre': [], 'post': []}}

        for pp in ['pre', 'post']:
            data[cve_id][function_name][version][pp].extend(results[version][pp])

        with open(json_file_path, 'w') as f:
            json.dump(data, f, indent=4)


        # 메모리 관리!! 개꿀!!
        # delete_query = f'delete("{os.path.basename(import_path)}")'
        # delete_result = client.execute(delete_query)
        # print('@@@@@')
        # print(delete_result['stdout'])

        # if os.path.exists('./workspace'):
        #     shutil.rmtree('./workspace')
        #     print("Workspace Cleaned.")



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#


import os
import glob
import subprocess
import re


def save_results_as_directory_structure(cve_id, function_name, version, pre_entries, post_entries):
    base_directory = './found_dependencies'

    # 기본 디렉토리가 존재하지 않으면 생성
    if not os.path.exists(base_directory):
        os.makedirs(base_directory)

    # 각 CVE ID에 대한 디렉토리 생성
    cve_directory = os.path.join(base_directory, cve_id)
    if not os.path.exists(cve_directory):
        os.makedirs(cve_directory)

    # 함수별 하위 디렉토리 생성
    function_directory = os.path.join(cve_directory, function_name)
    if not os.path.exists(function_directory):
        os.makedirs(function_directory)

    # 버전별(before/after) 디렉토리 생성
    version_directory = os.path.join(function_directory, version)
    if not os.path.exists(version_directory):
        os.makedirs(version_directory)

    # pre 및 post에서 중복 라인 번호를 제거하여 저장
    def remove_duplicates(entries):
        seen_lines = set()
        filtered_entries = []
        for entry in entries.values():
            line = entry['line']
            if line not in seen_lines:
                seen_lines.add(line)
                filtered_entry = {
                    'line': entry['line'],
                    'fullcodeline': entry['fullcodeline']
                }
                filtered_entries.append(filtered_entry)
        return filtered_entries

    # pre 및 post 결과에서 중복 라인 번호 제거
    pre_filtered_entries = remove_duplicates(pre_entries)
    post_filtered_entries = remove_duplicates(post_entries)

    # pre 및 post 결과를 각각 JSON 파일로 저장
    pre_file_path = os.path.join(version_directory, 'pre.json')
    post_file_path = os.path.join(version_directory, 'post.json')

    with open(pre_file_path, 'w') as pre_file:
        json.dump(pre_filtered_entries, pre_file, indent=4)

    with open(post_file_path, 'w') as post_file:
        json.dump(post_filtered_entries, post_file, indent=4)

    print(f"결과가 {version_directory}에 저장되었습니다.")

def run_ctags(file_path):
    try:
        # print(f"Running ctags on: {file_path}")
        result = subprocess.run(['ctags', '--fields=+ne', '-o', '-', '--sort=no', file_path],
                                capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error running ctags on {file_path}: {e}")
        return None

def parse_ctag_line(line):
    parts = line.split('\t')
    if len(parts) >= 4 and parts[3] == 'f':
        func_info = {
            'name': parts[0],
            'file': parts[1],
            'type': parts[3]
        }
        for field in parts[4:]:
            if field.startswith('line:'):
                func_info['start_line'] = int(field.split(':')[1])
            elif field.startswith('end:'):
                func_info['end_line'] = int(field.split(':')[1])
        return func_info
    return None

def load_checkpoint():
    if os.path.exists(CHECKPOINT_FILE):
        with open(CHECKPOINT_FILE, 'r') as f:
            checkpoint = json.load(f)
            return checkpoint.get('last_output_path')
    return None

def save_checkpoint(last_output_path):
    with open(CHECKPOINT_FILE, 'w') as f:
        json.dump({'last_output_path': last_output_path}, f)
    print(f"Checkpoint saved: {last_output_path}")


def main():

    last_output_path = load_checkpoint()
    start_processing = False if last_output_path else True
    call_count = 0

    cve_folders = os.listdir('new_cve_code_changes')
    missing_end_line_count = 0
    for cve_folder in cve_folders:
        cve_path = os.path.join('new_cve_code_changes', cve_folder)
        affected_functions = []

        # print(f"\n\nProcessing CVE folder: {cve_folder}")

        diff_files = glob.glob(f'./cve_diffs/{cve_folder}/commit_*.diff')
        for diff_path in diff_files:
            # print(f"Processing diff file: {diff_path}")
            with open(diff_path, 'r') as diff_file:
                lines = diff_file.readlines()

            file_diffs = []
            current_file_diff = []
            for line in lines:
                if line.startswith('diff --git'):
                    if current_file_diff:
                        file_diffs.append(current_file_diff)
                        current_file_diff = []
                current_file_diff.append(line)
            if current_file_diff:
                file_diffs.append(current_file_diff)

            for file_diff in file_diffs:
                processing_file = False
                file_name = ''
                before_hash = ''
                after_hash = ''
                changed_lines_onlyPM = []
                start_line = None
                line_count = 0

                for line in file_diff:
                    if line.startswith('diff --git'):
                        # 파일 경로
                        parts = line.strip().split()
                        if len(parts) >= 3:
                            a_file = parts[2][2:]  # 'a/...'에서 a/삭제
                            b_file = parts[3][2:]
                            file_name = os.path.basename(a_file)
                            processing_file = True

                    elif processing_file and line.startswith('index'):

                        parts = line.strip().split()
                        if len(parts) >= 2:
                            hashes = parts[1].split('..')
                            if len(hashes) == 2:
                                before_hash = hashes[0]
                                after_hash = hashes[1]

                    elif processing_file and line.startswith('@@ '):
                        match = re.match(r'@@ -(\d+)(?:,\d+)? \+(\d+)(?:,\d+)? @@', line)

                        if match:
                            before_start = int(match.group(1))
                            after_start = int(match.group(2))
                            start_line = before_start  # before 상태의 라인 번호 사용
                            line_count = 0

                    elif processing_file and start_line is not None:
                        line_count += 1
                        if line.startswith('-') and not line.startswith('---'):
                            # 삭제된 라인
                            changed_lines_onlyPM.append(start_line + line_count - 1)
                        elif line.startswith('+') and not line.startswith('+++'):
                            # 추가된 라인
                            changed_lines_onlyPM.append(start_line + line_count - 1)
                        else:
                            pass

                if not before_hash or not after_hash or not file_name:
                    continue  # 필요한 정보가 없으면 스킵

                # print(f"Processing file: {file_name}")
                # print(f"Before hash: {before_hash}, After hash: {after_hash}")

                # before와 after 파일 경로 설정
                before_file_name = f"{before_hash}_{file_name}"
                after_file_name = f"{after_hash}_{file_name}"

                before_file_path = os.path.join(cve_path, 'before', before_file_name)
                after_file_path = os.path.join(cve_path, 'after', after_file_name)

                # 상태별로 반복
                for state, file_path, hash_pair in [('before', before_file_path, (before_hash, after_hash)), ('after', after_file_path, (before_hash, after_hash))]:
                    if not os.path.exists(file_path):
                        print(f"File not found: {file_path}")
                        continue
                    # if file_path.rsplit('.', 1)[-1] not in ['c', 'cc', 'cpp']:
                    #     print(f"Skipping non C/C++ file: {file_path}")
                    #     continue

                    # print(f"Analyzing file: {file_path}")

                    ctags_output = run_ctags(file_path)
                    if not ctags_output:
                        continue

                    functions = []
                    for line in ctags_output.strip().split('\n'):
                        func_info = parse_ctag_line(line)
                        if func_info:
                            functions.append(func_info)

                    for func in functions:
                        if 'start_line' in func and 'end_line' in func:
                            if any(func['start_line'] <= line <= func['end_line'] for line in changed_lines_onlyPM):
                                # print(f"Function {func['name']} affected by changes.")
                                # print(f'changed_lineNum -> {changed_lines_onlyPM}')
                                # print(f"SL: {func['start_line']}, EL: {func['end_line']}")
                                print(func)
                                short_hash = hash_pair[0][:3] + hash_pair[1][:3]

                                with open(file_path, 'r') as file:
                                    lines = file.readlines()
                                    func_code = ''.join(lines[func['start_line'] - 1:func['end_line']])

                                extension = os.path.splitext(file_path)[-1]
                                output_dir = f'./final_patched_functions/{state}'
                                os.makedirs(output_dir, exist_ok=True)
                                safe_file_name = file_name.replace('/', '$')
                                safe_func_name = func['name'].replace('/', '')
                                output_file_name = f"{cve_folder}@{short_hash}@{safe_file_name}##{safe_func_name}{extension}"
                                output_file_path = os.path.join(output_dir, output_file_name)

                                with open(output_file_path, 'w') as f:
                                    f.write(func_code)
                                # print(f"Saved function {func['name']} to {output_file_path}")

                                if last_output_path and not start_processing:
                                    if output_file_path == last_output_path:
                                        start_processing = True
                                    continue

                                if not last_output_path or start_processing:
                                    # Affected functions management
                                    if f"{func['name']}@@{state}" not in affected_functions:
                                        affected_functions.append(f"{func['name']}@@{state}")
                                        print(f'affected_functions -> {affected_functions}')

                                        # Call help_me_joren and manage checkpointing
                                        print(f'output_file_path -> {output_file_path}')

                                        if 'belle_sip_messageParser' not in output_file_path:
                                            help_me_joren(output_file_path)

                                        call_count += 1
                                        if call_count >= 500:
                                            save_checkpoint(output_file_path)
                                            print("Reached 500 calls to help_me_joren. Exiting.")
                                            sys.exit(0)
                                        print(call_count)


                        else:
                            missing_end_line_count += 1

        # print(f"CVE {cve_folder} - Affected Functions: {affected_functions}\n")

    print(f"Total missing end lines: {missing_end_line_count}")

if __name__ == "__main__":
    
    # if os.path.exists('./found_dependency.json'):
    #     os.remove('./found_dependency.json')
    main()

    # 5230 CVEs



#-----------------------------------changedlinenum_onlyPM추가-----------------------------#
# def main():

#     # last_output_path = load_checkpoint()
#     # start_processing = False if last_output_path else True
#     # call_count = 0

#     cve_folders = os.listdir('new_cve_code_changes')
#     missing_end_line_count = 0

#     function_changes = {'before': {}, 'after': {}}

#     for cve_folder in cve_folders:
#         cve_path = os.path.join('new_cve_code_changes', cve_folder)
#         affected_functions = []

#         # print(f"\n\nProcessing CVE folder: {cve_folder}")

#         diff_files = glob.glob(f'./cve_diffs/{cve_folder}/commit_*.diff')
#         for diff_path in diff_files:
#             # print(f"Processing diff file: {diff_path}")
#             with open(diff_path, 'r') as diff_file:
#                 lines = diff_file.readlines()

#             file_diffs = []
#             current_file_diff = []
#             for line in lines:
#                 if line.startswith('diff --git'):
#                     if current_file_diff:
#                         file_diffs.append(current_file_diff)
#                         current_file_diff = []
#                 current_file_diff.append(line)
#             if current_file_diff:
#                 file_diffs.append(current_file_diff)

#             for file_diff in file_diffs:
#                 processing_file = False
#                 file_name = ''
#                 before_hash = ''
#                 after_hash = ''
#                 changed_lines_onlyPM = []
#                 start_line = None
#                 line_count = 0

#                 for line in file_diff:
#                     if line.startswith('diff --git'):
#                         # 파일 경로
#                         parts = line.strip().split()
#                         if len(parts) >= 3:
#                             a_file = parts[2][2:]  # 'a/...'에서 a/삭제
#                             b_file = parts[3][2:]
#                             file_name = os.path.basename(a_file)
#                             processing_file = True

#                     elif processing_file and line.startswith('index'):

#                         parts = line.strip().split()
#                         if len(parts) >= 2:
#                             hashes = parts[1].split('..')
#                             if len(hashes) == 2:
#                                 before_hash = hashes[0]
#                                 after_hash = hashes[1]

#                     elif processing_file and line.startswith('@@ '):
#                         match = re.match(r'@@ -(\d+)(?:,\d+)? \+(\d+)(?:,\d+)? @@', line)

#                         if match:
#                             before_start = int(match.group(1))
#                             after_start = int(match.group(2))
#                             start_line = before_start  # before 상태의 라인 번호 사용
#                             line_count = 0

#                     elif processing_file and start_line is not None:
#                         line_count += 1
#                         if line.startswith('-') and not line.startswith('---'):
#                             # 삭제된 라인
#                             changed_lines_onlyPM.append(start_line + line_count - 1)
#                         elif line.startswith('+') and not line.startswith('+++'):
#                             # 추가된 라인
#                             changed_lines_onlyPM.append(start_line + line_count - 1)
#                         else:
#                             pass

#                 if not before_hash or not after_hash or not file_name:
#                     continue  # 필요한 정보가 없으면 스킵

#                 # print(f"Processing file: {file_name}")
#                 # print(f"Before hash: {before_hash}, After hash: {after_hash}")

#                 # before와 after 파일 경로 설정
#                 before_file_name = f"{before_hash}_{file_name}"
#                 after_file_name = f"{after_hash}_{file_name}"

#                 before_file_path = os.path.join(cve_path, 'before', before_file_name)
#                 after_file_path = os.path.join(cve_path, 'after', after_file_name)

#                 # 상태별로 반복
#                 for state, file_path, hash_pair in [('before', before_file_path, (before_hash, after_hash)), ('after', after_file_path, (before_hash, after_hash))]:
#                     if not os.path.exists(file_path):
#                         print(f"File not found: {file_path}")
#                         continue
#                     # if file_path.rsplit('.', 1)[-1] not in ['c', 'cc', 'cpp']:
#                     #     print(f"Skipping non C/C++ file: {file_path}")
#                     #     continue

#                     # print(f"Analyzing file: {file_path}")

#                     ctags_output = run_ctags(file_path)
#                     if not ctags_output:
#                         continue

#                     functions = []
#                     for line in ctags_output.strip().split('\n'):
#                         func_info = parse_ctag_line(line)
#                         if func_info:
#                             functions.append(func_info)

#                     for func in functions:
#                         if 'start_line' in func and 'end_line' in func:
#                             if any(func['start_line'] <= line <= func['end_line'] for line in changed_lines_onlyPM):
#                                 # print(f"Function {func['name']} affected by changes.")
#                                 # print(f'changed_lineNum -> {changed_lines_onlyPM}')
#                                 # print(f"SL: {func['start_line']}, EL: {func['end_line']}")
#                                 print(func)
#                                 short_hash = hash_pair[0][:3] + hash_pair[1][:3]

#                                 with open(file_path, 'r') as file:
#                                     lines = file.readlines()
#                                     func_code = ''.join(lines[func['start_line'] - 1:func['end_line']])

#                                 extension = os.path.splitext(file_path)[-1]
#                                 output_dir = f'./final_patched_functions/{state}'
#                                 os.makedirs(output_dir, exist_ok=True)
#                                 safe_file_name = file_name.replace('/', '$')
#                                 safe_func_name = func['name'].replace('/', '')
#                                 output_file_name = f"{cve_folder}@{short_hash}@{safe_file_name}##{safe_func_name}{extension}"
#                                 output_file_path = os.path.join(output_dir, output_file_name)

#                                 # with open(output_file_path, 'w') as f:
#                                 #     f.write(func_code)

               
#                                 affected_lines = [line for line in changed_lines_onlyPM if func['start_line'] <= line <= func['end_line']]
#                                 function_changes[state][output_file_name] = affected_lines


#                         else:
#                             missing_end_line_count += 1

#         # print(f"CVE {cve_folder} - Affected Functions: {affected_functions}\n")

#     with open('function_changes.json', 'w') as json_file:
#         json.dump(function_changes, json_file)

#     print(f"Total missing end lines: {missing_end_line_count}")

# if __name__ == "__main__":
    
#     # if os.path.exists('./found_dependency.json'):
#     #     os.remove('./found_dependency.json')
#     main()