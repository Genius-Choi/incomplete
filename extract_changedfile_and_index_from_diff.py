import re
import requests
import json


allowed_extensions = ('.c', '.cpp', '.cc', '.php', '.py', '.java', '.rb')

with open('cve_commit.json', 'r') as f:
    cve_commits = json.load(f)

output = {}

# diff 파일의 각 라인에서 파일명과 인덱스 값을 추출하는 정규식
diff_pattern = re.compile(r'^diff --git a/(.*) b/.*\nindex ([0-9a-f]+)\.\.([0-9a-f]+)')

# 각 CVE에 대해 diff 파일 분석
for cve, commit_urls in cve_commits.items():
    output[cve] = []
    
    for commit_url in commit_urls:
        # diff 파일을 다운로드
        diff_url = commit_url + ".diff"
        response = requests.get(diff_url)
        if response.status_code != 200:
            print(f"Failed to download diff for {commit_url}")
            continue
        
        diff_content = response.text.splitlines()
        patch_info = {
            "commit_url": commit_url,
            "index_commits": []
        }

        # diff 내용 분석
        for i in range(len(diff_content)):
            # diff --git a/ 경로, 인덱스 추출 부분
            if diff_content[i].startswith('diff --git a/'):
                match = diff_pattern.match('\n'.join(diff_content[i:i+2]))
                if match:
                    file_path, before_index, after_index = match.groups()
                    
                    # 파일 확장자 필터링
                    if file_path.endswith(allowed_extensions):
                        patch_info["index_commits"].append({
                            "file": file_path,
                            "before": before_index,
                            "after": after_index
                        })

        # 해당 커밋에 대해 추출된 패치 정보 저장
        output[cve].append(patch_info)

# 결과를 JSON 파일로 저장
with open('cve_patchfile_and_index_1012.json', 'w') as json_file:
    json.dump(output, json_file, indent=2)

print("Patch information saved to cve_patch_info.json")


