import json
import requests
from requests.adapters import HTTPAdapter
import urllib3
import re
from collections import defaultdict
import time
import os

def create_session_with_retries():
    session = requests.Session()
    retry = urllib3.util.Retry(
        total=5,
        backoff_factor=1,
        status_forcelist=[429, 500, 502, 503, 504],
        allowed_methods=["HEAD", "GET", "OPTIONS"]
    )
    adapter = HTTPAdapter(max_retries=retry)
    session.mount("https://", adapter)
    session.mount("http://", adapter)
    return session

session = create_session_with_retries()

def is_cpp_file(file_path):
    cpp_extensions = ('.c', '.cpp', '.cc', '.php', '.py', '.java', '.rb')
    return file_path.lower().endswith(cpp_extensions)

def get_diff_content(commit_url):
    diff_url = commit_url + '.diff'
    try:
        response = session.get(diff_url, timeout=30)  # 30초 타임아웃 설정
        response.raise_for_status()
        return response.text
    except requests.exceptions.RequestException as e:
        print(f"Error fetching diff for {commit_url}: {str(e)}")
        return None

def extract_index_commits(diff_content):
    index_commits = []
    current_file = None
    pattern = r'index ([a-f0-9]+)\.\.([a-f0-9]+)'
    for line in diff_content.split('\n'):
        if line.startswith('diff --git'):
            current_file = line.split()[-1][2:]  # Extract the file path
        elif line.startswith('index ') and current_file and is_cpp_file(current_file):
            match = re.search(pattern, line)
            if match:
                before, after = match.groups()
                index_commits.append({
                    'file': current_file,
                    'before': before,
                    'after': after
                })
    return index_commits

def process_commits():
    try:
        with open('cpp_index_commits_progress.json', 'r') as f:
            results = json.load(f)
        print("Resuming from previous progress...")
    except FileNotFoundError:
        results = defaultdict(list)

    with open('cve_commit.json', 'r') as f:
        cve_commits = json.load(f)

    total_cves = len(cve_commits)
    processed_cves = len(results)

    print(f"Starting to process {total_cves} CVEs...")

    for cve, commits in list(cve_commits.items())[processed_cves:]:
        print(f"\nProcessing {cve}...")
        for i, commit_url in enumerate(commits, 1):
            print(f"  Fetching diff for commit {i}/{len(commits)}: {commit_url}")
            diff_content = get_diff_content(commit_url)
            if diff_content:
                index_commits = extract_index_commits(diff_content)
                if index_commits:
                    results[cve].append({
                        'commit_url': commit_url,
                        'index_commits': index_commits
                    })
                    print(f"    Found {len(index_commits)} C/C++ file changes")
                else:
                    print(f"    No C/C++ file changes found in this commit")
            else:
                print(f"    Failed to fetch diff for {commit_url}")
            
            time.sleep(0.5)  # GitHub API 사용 제한 고려

        processed_cves += 1
        progress = (processed_cves / total_cves) * 100
        print(f"Progress: {progress:.2f}% ({processed_cves}/{total_cves} CVEs processed)")

        # 중간 결과 저장
        with open('c_index_commits_progress.json', 'w') as f:
            json.dump(results, f, indent=2)

    return results

# 실행
results = process_commits()

# 최종 결과를 파일로 저장
print("\nSaving final results to 'cpp_index_commits.json'...")
with open('cpp_index_commits.json', 'w') as f:
    json.dump(results, f, indent=2)

print("Processing completed successfully!")