import re
import requests
import json
import time
from requests.exceptions import ConnectionError

# 파일 확장자 필터 리스트
allowed_extensions = ('.c', '.cpp', '.cc', '.php', '.py', '.java', '.rb')

with open('cve_commit.json', 'r') as f:
    cve_commits = json.load(f)

# 패치 정보를 저장할 딕셔너리
output = {}

# diff 파일의 각 라인에서 파일명과 인덱스 값을 추출하는 정규식
diff_pattern = re.compile(r'^diff --git a/(.*) b/(.*)\nindex ([0-9a-f]+)\.\.([0-9a-f]+)')

# 재시도 관련 설정
MAX_RETRIES = 3  # 최대 재시도 횟수
RETRY_DELAY = 3  # 재시도 전 대기 시간 (초)

def fetch_diff_content(url, retries=MAX_RETRIES):
    """
    diff 파일을 다운로드하고, 재시도할 수 있는 함수
    404 에러가 발생할 경우 즉시 실패로 처리하고, 다른 오류는 재시도함.
    """
    for attempt in range(retries):
        try:
            response = requests.get(url)
            response.raise_for_status()  # HTTP 오류 발생 시 예외 발생
            return response.text.splitlines()  # 성공 시 diff 내용을 반환
        except requests.exceptions.HTTPError as e:
            # 404 에러일 경우 재시도하지 않고 바로 실패 처리
            if response.status_code == 404:
                print(f"404 Error for {url}: {e}")
                return None
            print(f"HTTP error for {url} (attempt {attempt + 1}/{retries}): {e}")
        except (ConnectionError, requests.exceptions.RequestException) as e:
            print(f"Connection error for {url} (attempt {attempt + 1}/{retries}): {e}")
        if attempt + 1 < retries:
            print(f"Retrying in {RETRY_DELAY} seconds...")
            time.sleep(RETRY_DELAY)  # 잠시 대기 후 재시도
    print(f"Failed to retrieve {url} after {retries} attempts.")
    return None

# 각 CVE에 대해 diff 파일 분석
for cve, commit_urls in cve_commits.items():
    output[cve] = []
    
    for commit_url in commit_urls:
        # 커밋 URL에서 .diff 또는 .patch 처리
        if commit_url.endswith(".diff"):
            diff_url = commit_url  # 이미 .diff인 경우 그대로 사용
        elif commit_url.endswith(".patch"):
            diff_url = commit_url.replace(".patch", ".diff")  # .patch는 .diff로 교체
        else:
            diff_url = commit_url + ".diff"  # .diff를 추가
        
        # diff 파일을 다운로드하고 재시도 처리
        diff_content = fetch_diff_content(diff_url)
        if diff_content is None:
            continue  # 다운로드에 실패한 경우 다음 커밋으로 넘어감

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
                    before_file, after_file, before_index, after_index = match.groups()
                    
                    # 파일 확장자 필터링
                    if before_file.endswith(allowed_extensions) or after_file.endswith(allowed_extensions):
                        patch_info["index_commits"].append({
                            "before_file": before_file,
                            "after_file": after_file,
                            "before": before_index,
                            "after": after_index
                        })

        # 해당 커밋에 대해 추출된 패치 정보 저장
        output[cve].append(patch_info)

# 결과를 JSON 파일로 저장
with open('cve_patchfile_index.json', 'w') as json_file:
    json.dump(output, json_file, indent=2)

print("Patch information saved to cve_patchfile_index.json")
