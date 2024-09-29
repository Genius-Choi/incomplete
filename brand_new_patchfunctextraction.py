import os
import glob
import subprocess
import re

def run_ctags(file_path):
    try:
        print(f"Running ctags on: {file_path}")
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

def main():
    cve_folders = os.listdir('cve_code_changes')
    missing_end_line_count = 0
    for cve_folder in cve_folders:
        cve_path = './cve_code_changes/' + cve_folder # ./cve_code_changes/CVE-2017-18249
        affected_functions = []

        print(f"Processing CVE folder: {cve_folder}") # CVE-2017-18249

        for state in ['before', 'after']:
            state_dir = os.path.join(cve_path, state)
            print(f"Processing {state} state in: {state_dir}") # ./cve_code_changes/CVE-2017-18249/before
            
            for file_name in os.listdir(state_dir):
                file_path = os.path.join(state_dir, file_name)
                if file_path.rsplit('.')[-1] not in ['c', 'cc', 'cpp']:
                    print(f"Skipping non C/C++ file: {file_path}")
                    continue

                print(f"Analyzing file: {file_path}") #./cve_code_changes/CVE-2017-18249/before/node.c

                ctags_output = run_ctags(file_path)
                functions = []
                
                for line in ctags_output.split('\n'):
                    func_info = parse_ctag_line(line)
                    if func_info:
                        functions.append(func_info)
                
                # CVE하나에 diff여러개인거 고려해야함
                diff_files = glob.glob(f'./cve_diffs/{cve_folder}/commit_*.diff')
                for diff_path in diff_files:
                    print(f"Processing diff file: {diff_path}")
                    changed_lines, changed_lines_onlyPM = [], []
                    processing_file = False

                    if os.path.exists(diff_path):
                        with open(diff_path, 'r') as f:
                            start_line = None
                            line_count = 0

                            for line in f:
                                # diff --git으로 시작하며 file_name이 포함된 라인을 찾음
                                if line.startswith('diff --git'):
                                    processing_file = file_name in line
                                    if processing_file:
                                        print(f"Found target file {file_name} in diff: {line.strip()}")

                                if processing_file:
                                    if line.startswith('@@ '):

                                        match = re.match(r'@@ -(\d+),(\d+) \+(\d+),(\d+) @@', line)
                                        if match:
                                            before_start, before_len, after_start, after_len = map(int, match.groups())
                                            start_line = before_start if state == 'before' else after_start
                                            line_count = 0 # 새로운 헝크!!
                                            print(f"Found change chunk for {file_name}: start_line={start_line}")

                                    elif start_line is not None:
                                        if (state == 'before' and not line.startswith('+')) or (state == 'after' and not line.startswith('-')):
                                            line_count += 1
                                            changed_lines.append(start_line + line_count - 1)

                                        if state == 'before' and line.startswith('-'):
                                            changed_lines_onlyPM.append(start_line + line_count - 1)
                                        elif state == 'after' and line.startswith('+'):
                                            changed_lines_onlyPM.append(start_line + line_count - 1)

                    # 바뀐라인분석, diff에서 diff --git으로 시작하는줄 찾아서 파일경로추출, 분석한바뀐라인활용해서 패치된 함수 식별, 저장
                    if len(changed_lines) > 6:
                        changed_lines = changed_lines[3:-3]
                    print(f"Changed lines: {changed_lines}")
                    print(f"Changed lines onlyPM: {changed_lines_onlyPM}")


                    diff_git_path = None
                    with open(diff_path, 'r') as f:
                        for line in f:
                            if line.startswith('diff --git'):
                                diff_git_path = line.split()[2][2:]  # 'a/...'에서 '...'만 추출
                                break


                    for func in functions:
                        if 'start_line' in func and 'end_line' in func:
                            if any(func['start_line'] <= line <= func['end_line'] for line in changed_lines_onlyPM):
                                print(f"Function {func['name']} affected by changes.")
                                if func['name'] not in affected_functions:
                                    affected_functions.append(func['name'])
                                

                                with open(file_path, 'r') as file:
                                    lines = file.readlines()
                                    func_code = ''.join(lines[func['start_line']-1:func['end_line']])
                                

                                extension = os.path.splitext(file_path)[-1]
                                output_dir = f'./final_patched_functions/{state}'
                                os.makedirs(output_dir, exist_ok=True)
                                safe_diff_git_path = diff_git_path.replace('/', '$')
                                output_file_path = os.path.join(output_dir, f"{cve_folder}@@{safe_diff_git_path}##{func['name']}{extension}")

                                with open(output_file_path, 'w') as f:
                                    f.write(func_code)
                                print(f"Saved function {func['name']} to {output_file_path}")
                        else:
                            missing_end_line_count += 1

        print(f"CVE {cve_folder} - Affected Functions: {affected_functions}\n")

    print(f"Total missing end lines: {missing_end_line_count}")

if __name__ == "__main__":
    main()

# 13170 patched functions (after)
# 9628 patched functions (before)
# 4770 CVEs
# 14 missing endlines