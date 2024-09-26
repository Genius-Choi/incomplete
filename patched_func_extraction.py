# import subprocess
# import json
# import os
# import re
# import difflib
# import pprint

# missing_end_line_count = 0

# def get_file_extension(file_path):
#     _, extension = os.path.splitext(file_path)
#     return extension

# def sanitize_filename(filename, max_length=200):
#     # Remove or replace characters that are invalid in file names
#     filename = re.sub(r'[<>:"/\\|?*]', '_', filename)
#     filename = filename.replace(' ', '_')
#     return filename

# def run_ctags(file_path):
#     try:
#         result = subprocess.run(['ctags', '--fields=+ne', '-o', '-', '--sort=no', file_path],
#                                 capture_output=True, text=True, check=True)
#         # print(result.stdout)
#         return result.stdout

#     except subprocess.CalledProcessError as e:
#         print(f"Error running ctags on {file_path}: {e}")
#         return None

# def parse_ctags_output(ctags_output, file_path):
#     functions = []
#     for line in ctags_output.split('\n'):
#         if line.strip():
#             parts = line.split('\t')
#             # print(parts)
#             if len(parts) >= 4 and parts[3] == 'f':  # Only function
#                 # print(ctags_output)
#                 # print(parts)
#                 func_info = {
#                     'name': parts[0],
#                     'file': parts[1],
#                     # 'sig': parts[2].strip('/^').strip('$/'),
#                     'type': parts[3]
#                 }
#                 for field in parts[4:]:
#                     if field.startswith('line:'):
#                         func_info['start_line'] = int(field.split(':')[1])
#                     elif field.startswith('end:'):
#                         func_info['end_line'] = int(field.split(':')[1])
#                 functions.append(func_info)
#     return functions

# def get_functions_from_file(file_path):
#     functions=[]
#     global missing_end_line_count
#     ctags_output = run_ctags(file_path)
#     if ctags_output:
#         parsed_functions = parse_ctags_output(ctags_output, file_path)
#         # pprint.pprint(parsed_functions)
        
#         #  func ->
#         #  {'end_line': 2760,
#         #   'file': 'cve_code_changes/CVE-2018-16427/after/card-epass2003.c',
#         #   'name': 'sc_get_epass2003_driver',
#         #   'start_line': 2757,
#         #   'type': 'f'}
        
#         for func in parsed_functions:
#             # if 'CVE-2015-1792' in func['file']:
#             #     print(func)
#             if 'start_line' in func and 'end_line' in func:
#                 functions.append(func)
#             else:
#                 missing_end_line_count += 1
#                 # print(ctags_output)
#                 # print('\n')
#                 # print(func)
#                 # if 'CVE-2018-16427' in func['file']:
#                 #     print(parsed_functions)

#         # Sort functions by start_line
#         # functions.sort(key=lambda x: x['start_line'])
#     return functions

# def process_cve_folder(cve_folder): #cve_folder = cve_code_changes/CVE-2015-1792
#     results = {'before': {}, 'after': {}}
    
#     for state in ['before', 'after']:
#         state_dir = cve_folder + '/' + state
#         for file_name in os.listdir(state_dir):
#             file_path = state_dir + '/' + file_name
#             if os.path.isfile(file_path):
#                 functions = get_functions_from_file(file_path)
#                 if functions:
#                     results[state][file_name] = [
#                         {
#                             'name': func['name'],
#                             'start_line': func['start_line'],
#                             'end_line': func['end_line']
#                         }
#                         for func in functions
#                     ]
#     return results

# def find_affected_functions_b(cve_id, file_name, changed_lines, sline_eline_data):
#     affected_functions = []
#     # if file_name == 'arch/x86/kernel/traps.c' and cve_id == 'CVE-2013-4220':
#     #     print(changed_lines)
#     # if cve_id in sline_eline_data and 'before' in sline_eline_data[cve_id]:
#     if file_name.split('/')[-1] in sline_eline_data[cve_id]['before']:
#         for func in sline_eline_data[cve_id]['before'][file_name.split('/')[-1]]:
#             if all(func['start_line'] <= line <= func['end_line'] for line in changed_lines):
#                 affected_functions.append(func['name'])

#                 if 'CVE-2006-5331' in cve_id:
#                     print(func['name'])
#                     print(changed_lines)
                
#                 if 'trap_init' in file_name:
#                     print(file_name)
#                     print(changed_lines)

#     return affected_functions

# def find_affected_functions_a(cve_id, file_name, changed_lines, sline_eline_data):
#     affected_functions = []
#     # if file_name == 'arch/x86/kernel/traps.c' and cve_id == 'CVE-2013-4220':
#     #     print(changed_lines)
#     # if cve_id in sline_eline_data and 'before' in sline_eline_data[cve_id]:
#     if file_name.split('/')[-1] in sline_eline_data[cve_id]['after']:
#         for func in sline_eline_data[cve_id]['after'][file_name.split('/')[-1]]:
#             if all(func['start_line'] <= line <= func['end_line'] for line in changed_lines):
#                 affected_functions.append(func['name'])

#                 if 'CVE-2006-5331' in cve_id:
#                     print(func['name'])
#                     print(changed_lines)
                                    
#                 if 'trap_init' in file_name:
#                     print(file_name)
#                     print(changed_lines)

#     return affected_functions

# def extract_function_code(file_path, start_line, end_line):
#     with open(file_path, 'r') as file:
#         lines = file.readlines()
#         return ''.join(lines[start_line-1:end_line])

# def save_function_code(cve_id, file_name, function_name, code, state):
#     safe_file_name = file_name.replace('/', '_')
#     extension = get_file_extension(file_name)
#     # directory = f'./new_patched_functions/{state}/{cve_id}@@{safe_file_name}##{function_name}{extension}'
#     directory = f'./new_patched_functions/{state}'
#     os.makedirs(directory, exist_ok=True)
#     file_path = f'{directory}/{cve_id}@@{safe_file_name}##{function_name}{extension}'

#     # if os.path.exists(file_path):
#     #     print("@@@@@@@@@@@@@@@")
#     #     print(file_path)

#     # print(f'Saving: {function_name}')
#     with open(file_path, 'w') as file:
#         file.write(code)
    
#     # if 'CVE-2006-5331' in file_path:
#     #     print(file_path)
#     #     print(state)

# def main():
#     all_results = {}
    
#     for cve_folder in os.listdir('cve_code_changes'):
#         cve_path = 'cve_code_changes' + '/' + cve_folder # cve_code_changes/CVE-2015-1792
#         if os.path.isdir(cve_path):
#             all_results[cve_folder] = process_cve_folder(cve_path)

#     with open('./sline_eline_per_cve.json', 'w') as f:
#         json.dump(all_results, f, indent=2)

#     print("Analysis complete. Results saved to './sline_eline_per_cve.json'")

#     ### 여기서부터 diff파일보고 변경된 라인 찾아서 패치된 함수만 뽑아 저장하는 로직 ###

#     with open('sline_eline_per_cve.json', 'r') as ff:
#         sline_eline_data = json.load(ff)

#     affected_functions_per_file_b = {}
#     affected_functions_per_file_a = {}

#     def process_changed_lines_b(cve_id, file_name, changed_lines):
#         if len(changed_lines) > 6:
#             changed_lines = changed_lines[3:-3]
#         else:
#             changed_lines = [] # '+' 라인만 있어 -> before의 입장에선 바뀐 라인이 없는거잖아
        
#         if changed_lines:
#             affected_functions_b = find_affected_functions_b(cve_id, file_name, changed_lines, sline_eline_data)
#             if affected_functions_b:
#                 if file_name not in affected_functions_per_file_b:
#                     affected_functions_per_file_b[file_name] = set()
#                 affected_functions_per_file_b[file_name].update(affected_functions_b)

#     def process_changed_lines_a(cve_id, file_name, changed_lines):
#         # print(file_name)
#         # print(changed_lines)
#         if len(changed_lines) > 6:
#             changed_lines = changed_lines[3:-3]
#         else:
#             changed_lines = [] # '-' 라인만 있어 -> after의 입장에선 바뀐 라인이 없는거잖아
        
#         if changed_lines:
#             affected_functions_a = find_affected_functions_a(cve_id, file_name, changed_lines, sline_eline_data)
#             if affected_functions_a:
#                 if file_name not in affected_functions_per_file_a:
#                     affected_functions_per_file_a[file_name] = set()
#                 affected_functions_per_file_a[file_name].update(affected_functions_a)
    
#     for diff_folder_b in os.listdir('cve_diffs'):
#         diff_file_b = 'cve_diffs' + '/' + diff_folder_b + '/' + 'commit_1.diff'
#         with open(diff_file_b, 'r') as f_b:
#             current_file_b = None
#             before_start_b = None
#             line_count_b = 0
#             changed_lines_b = []

#             for line_b in f_b:
#                 if line_b.startswith('diff --git'):
#                     if current_file_b and changed_lines_b:
#                         process_changed_lines_b(diff_folder_b, current_file_b, changed_lines_b)
#                     current_file_b = line_b.split()[-1][2:]
#                     changed_lines_b = []
#                 elif line_b.startswith('@@'):
#                     if changed_lines_b:
#                         process_changed_lines_b(diff_folder_b, current_file_b, changed_lines_b)
#                         changed_lines_b = []
#                     match_b = re.match(r'@@ -(\d+),(\d+) \+(\d+),(\d+) @@', line_b)
#                     if match_b:
#                         before_start_b, before_len_b, after_start_b, after_len_b = map(int, match_b.groups())
#                         line_count_b = 0
#                 elif before_start_b is not None:
#                     if not line_b.startswith('+'):
#                         line_count_b += 1
#                         changed_lines_b.append(before_start_b + line_count_b - 1)

#             if current_file_b and changed_lines_b:
#                 process_changed_lines_b(diff_folder_b, current_file_b, changed_lines_b)

#     # pprint.pprint(affected_functions_per_file_b)



#     for diff_folder_a in os.listdir('cve_diffs'):
#         diff_file_a = 'cve_diffs' + '/' + diff_folder_a + '/' + 'commit_1.diff'
#         with open(diff_file_a, 'r') as f_a:
#             current_file_a = None
#             after_start_a = None
#             line_count_a = 0
#             changed_lines_a = []

#             for line_a in f_a:
#                 if line_a.startswith('diff --git'):
#                     if current_file_a and changed_lines_a:
#                         process_changed_lines_a(diff_folder_a, current_file_a, changed_lines_a)
#                     current_file_a = line_a.split()[-1][2:]
#                     changed_lines_a = []
#                 elif line_a.startswith('@@'):
#                     if changed_lines_a:
#                         process_changed_lines_a(diff_folder_a, current_file_a, changed_lines_a)
#                         changed_lines_a = []
#                     match_a = re.match(r'@@ -(\d+),(\d+) \+(\d+),(\d+) @@', line_a)
#                     if match_a:
#                         before_start_a, before_len_a, after_start_a, after_len_a = map(int, match_a.groups())
#                         line_count_a = 0
#                 elif after_start_a is not None:
#                     if not line_a.startswith('-'):
#                         # print(line_a)
#                         line_count_a += 1
#                         changed_lines_a.append(after_start_a + line_count_a - 1)

#             if current_file_a and changed_lines_a:
#                 process_changed_lines_a(diff_folder_a, current_file_a, changed_lines_a)

#     # pprint.pprint(affected_functions_per_file_a)

#     # print(affected_functions_per_file_b['arch/x86/kernel/traps.c'])
#     # print(affected_functions_per_file_a['arch/x86/kernel/traps.c'])


#     # 이제 파일로 저장하도록
#     for cve_id in sline_eline_data:
#         for filename, functions in affected_functions_per_file_b.items():
#             full_file_path = f'./cve_code_changes/{cve_id}/before/{filename.split("/")[-1]}'
#             # print(full_file_path)
#             # print(functions)
#             for function in functions:
#                 if filename.split('/')[-1] in sline_eline_data[cve_id]['before']:
#                     info = sline_eline_data[cve_id]['before'][filename.split('/')[-1]]
#                     # print(info)
#                     for func_info in info:
#                         if func_info['name'] == function:
#                             code = extract_function_code(full_file_path, func_info['start_line'], func_info['end_line'])
#                             # print(code)
#                             save_function_code(cve_id, filename, function, code, 'before')
    
#     for cve_id in sline_eline_data:
#         for filename, functions in affected_functions_per_file_a.items():
#             full_file_path = f'./cve_code_changes/{cve_id}/after/{filename.split("/")[-1]}'
#             # print(full_file_path)
#             # print(functions)
#             for function in functions:
#                 if filename.split('/')[-1] in sline_eline_data[cve_id]['after']:
#                     info = sline_eline_data[cve_id]['after'][filename.split('/')[-1]]
#                     # print(info)
#                     for func_info in info:
#                         if func_info['name'] == function:
#                             code = extract_function_code(full_file_path, func_info['start_line'], func_info['end_line'])
#                             # print(code)
#                             save_function_code(cve_id, filename, function, code, 'after')

#         # for state, affected_functions in [('before', affected_functions_per_file_b), ('after', affected_functions_per_file_a)]:
#         #     for file_name, functions in affected_functions.items():
#         #         full_file_path = f'./cve_code_changes/{cve_id}/{state}/{file_name.split("/")[-1]}'
#         #         # print(full_file_path)
#         #         if os.path.exists(full_file_path):
#         #             for function in functions:
#         #                 if file_name.split('/')[-1] in sline_eline_data[cve_id][state]:
#         #                     for func_info in sline_eline_data[cve_id][state][file_name.split('/')[-1]]:
#         #                         if func_info['name'] == function:
#         #                             code = extract_function_code(full_file_path, func_info['start_line'], func_info['end_line'])
#         #                             save_function_code(cve_id, file_name, function, code, state)
#         #                             break
#         #             # print('success')
#         #         else:
#         #             continue


#     print(f'Missing endline: {missing_end_line_count}')


# if __name__ == "__main__":
#     main()


# # /incomplete/new_patched_functions/after -> 4403 CVEs, 21025 (patched)functions
# # /incomplete/new_patched_functions/before -> 3901 CVEs, 16221 (patched)functions
# # 이슈: 같은 이름의 함수가 여러번 쓰이는 일이 많음.
# # 그래서 CVE폴더 안만들고 다이렉트로 저장하면 겹쳐쓰이는 일이 있는듯?

import subprocess
import json
import os
import re
import difflib
import pprint

missing_end_line_count = 0
no_body = 0

def get_file_extension(file_path):
    _, extension = os.path.splitext(file_path)
    return extension

def sanitize_filename(filename, max_length=200):
    filename = re.sub(r'[<>:"/\\|?*]', '_', filename)
    filename = filename.replace(' ', '_')
    return filename[:max_length]

def run_ctags(file_path):
    try:
        result = subprocess.run(['ctags', '--fields=+ne', '-o', '-', '--sort=no', file_path],
                                capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error running ctags on {file_path}: {e}")
        return None

def parse_ctags_output(ctags_output, file_path):
    functions = []
    for line in ctags_output.split('\n'):
        if line.strip():
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
                functions.append(func_info)
    return functions

def get_functions_from_file(file_path):
    global missing_end_line_count
    functions = []
    ctags_output = run_ctags(file_path)
    if ctags_output:
        parsed_functions = parse_ctags_output(ctags_output, file_path)
        for func in parsed_functions:
            if 'start_line' in func and 'end_line' in func:
                functions.append(func)
            else:
                missing_end_line_count += 1
    return functions

def process_cve_folder(cve_folder):
    results = {'before': {}, 'after': {}}
    for state in ['before', 'after']:
        state_dir = os.path.join(cve_folder, state)
        for file_name in os.listdir(state_dir):
            file_path = os.path.join(state_dir, file_name)
            if os.path.isfile(file_path):
                functions = get_functions_from_file(file_path)
                if functions:
                    results[state][file_name] = [
                        {
                            'name': func['name'],
                            'start_line': func['start_line'],
                            'end_line': func['end_line']
                        }
                        for func in functions
                    ]
    return results

def find_affected_functions(cve_id, file_name, changed_lines, sline_eline_data, state):
    affected_functions = []
    if file_name.split('/')[-1] in sline_eline_data[cve_id][state]:
        for func in sline_eline_data[cve_id][state][file_name.split('/')[-1]]:
            if any(func['start_line'] <= line <= func['end_line'] for line in changed_lines):
                affected_functions.append(func['name'])

                if 'CVE-2006-5331' in cve_id:
                    print(func['name'])
                    print(changed_lines)
                        
                if 'trap_init' in file_name:
                    print(file_name)
                    print(changed_lines)

    return affected_functions

def extract_function_code(file_path, start_line, end_line):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        return ''.join(lines[start_line-1:end_line])

def save_function_code(cve_id, file_name, function_name, code, state):
    safe_file_name = sanitize_filename(file_name.replace('/', '_'))
    extension = get_file_extension(file_name)
    directory = f'./new_patched_functions/{state}'
    os.makedirs(directory, exist_ok=True)
    file_path = f'{directory}/{cve_id}@@{safe_file_name}##{function_name}{extension}'
    with open(file_path, 'w') as file:
        file.write(code)


def process_changed_lines(cve_id, file_name, changed_lines, state, sline_eline_data, affected_functions_per_file):
    if len(changed_lines) > 6:
        changed_lines = changed_lines[3:-3]
    else:
        changed_lines = []
    
    if changed_lines:
        affected_functions = find_affected_functions(cve_id, file_name, changed_lines, sline_eline_data, state)
        if affected_functions:
            if file_name not in affected_functions_per_file:
                affected_functions_per_file[file_name] = set()
            affected_functions_per_file[file_name].update(affected_functions)

def process_diff_file(diff_file, cve_id, state, sline_eline_data, affected_functions_per_file):
    with open(diff_file, 'r') as f:
        current_file = None
        start_line = None
        line_count = 0
        changed_lines = []
        allowed_extensions = ('.c', '.cc', '.cpp')

        for line in f:
            if line.startswith('diff --git'):
                current_file = line.split()[-1][2:]
                if current_file and changed_lines and current_file.endswith(allowed_extensions):
                    print(current_file)
                    process_changed_lines(cve_id, current_file, changed_lines, state, sline_eline_data, affected_functions_per_file)

                # print(current_file)

                changed_lines = []
            elif line.startswith('@@'):
                match = re.match(r'@@ -(\d+),(\d+) \+(\d+),(\d+) @@', line)

                if changed_lines: # 첫번째 헝크가 아님
                    process_changed_lines(cve_id, current_file, changed_lines, state, sline_eline_data, affected_functions_per_file)
                    changed_lines = []
                
                if match:
                    before_start, before_len, after_start, after_len = map(int, match.groups())
                    start_line = before_start if state == 'before' else after_start
                    line_count = 0

            elif start_line is not None:
                if (state == 'before' and not line.startswith('+')) or (state == 'after' and not line.startswith('-')):
                    line_count += 1
                    changed_lines.append(start_line + line_count - 1)

        if current_file and changed_lines:
            process_changed_lines(cve_id, current_file, changed_lines, state, sline_eline_data, affected_functions_per_file)

def save_affected_functions(cve_id, affected_functions_per_file, sline_eline_data, state):
    global no_body
    for filename, functions in affected_functions_per_file.items():
        full_file_path = f'./cve_code_changes/{cve_id}/{state}/{filename.split("/")[-1]}'
        if os.path.exists(full_file_path):
            for function in functions:
                if filename.split('/')[-1] in sline_eline_data[cve_id][state]:
                    info = sline_eline_data[cve_id][state][filename.split('/')[-1]]
                    for func_info in info:
                        if func_info['name'] == function:
                            code = extract_function_code(full_file_path, func_info['start_line'], func_info['end_line'])
                            if len(code.strip()) > 0:
                                save_function_code(cve_id, filename, function, code, state)
                            else:
                                no_body += 1

def main():
    all_results = {}
    
    for cve_folder in os.listdir('cve_code_changes'):
        cve_path = os.path.join('cve_code_changes', cve_folder)
        if os.path.isdir(cve_path):
            all_results[cve_folder] = process_cve_folder(cve_path)

    with open('./sline_eline_per_cve.json', 'w') as f:
        json.dump(all_results, f, indent=2)

    print("Analysis complete. Results saved to './sline_eline_per_cve.json'")

    with open('sline_eline_per_cve.json', 'r') as ff:
        sline_eline_data = json.load(ff)

    affected_functions_per_file_b = {}
    affected_functions_per_file_a = {}

    for diff_folder in os.listdir('cve_diffs'):
        diff_file = os.path.join('cve_diffs', diff_folder, 'commit_1.diff')
        process_diff_file(diff_file, diff_folder, 'before', sline_eline_data, affected_functions_per_file_b)
        process_diff_file(diff_file, diff_folder, 'after', sline_eline_data, affected_functions_per_file_a)

    for cve_id in sline_eline_data:
        save_affected_functions(cve_id, affected_functions_per_file_b, sline_eline_data, 'before')
        save_affected_functions(cve_id, affected_functions_per_file_a, sline_eline_data, 'after')

    print(f'Missing endline: {missing_end_line_count}')
    print(f'No body: {no_body}')

if __name__ == "__main__":
    main()