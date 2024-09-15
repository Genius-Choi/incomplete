import json
import os
import subprocess
import shutil
from collections import defaultdict
from urllib.parse import urlparse
import time

# def clone_repo(repo_url, temp_dir):
#     repo_name = os.path.basename(urlparse(repo_url).path)
#     clone_path = os.path.join(temp_dir, repo_name)
#     if not os.path.exists(clone_path):
#         subprocess.run(['git', 'clone', repo_url, clone_path], check=True)
#     return clone_path

def clone_repo(repo_url, temp_dir, max_retries=3):
    repo_name = os.path.basename(urlparse(repo_url).path)
    clone_path = os.path.join(temp_dir, repo_name)
    if os.path.exists(clone_path):
        return clone_path

    for attempt in range(max_retries):
        try:
            print(f"Attempting to clone {repo_url} (Attempt {attempt + 1}/{max_retries})")
            subprocess.run(['git', 'clone', repo_url, clone_path], check=True)
            return clone_path
        except subprocess.CalledProcessError as e:
            print(f"Clone failed: {e}")
            if attempt < max_retries - 1:
                print(f"Retrying in 10 seconds...")
                time.sleep(10)
            else:
                raise

    raise Exception(f"Failed to clone repository after {max_retries} attempts")


def get_file_content(repo_path, commit_hash):
    current_dir = os.getcwd()
    os.chdir(repo_path)
    try:
        result = subprocess.run(['git', 'show', f'{commit_hash}'], 
                                capture_output=True, text=True, check=True)
        return result.stdout
    finally:
        os.chdir(current_dir)

def process_cve(cve, commit_data, repo_path, root_folder):
    cve_folder = os.path.join(root_folder, cve)
    os.makedirs(os.path.join(cve_folder, 'before'), exist_ok=True)
    os.makedirs(os.path.join(cve_folder, 'after'), exist_ok=True)
    
    for commit in commit_data:
        for file_change in commit['index_commits']:
            file_name = os.path.basename(file_change['file'])
            
            before_content = get_file_content(repo_path, file_change['before'])
            after_content = get_file_content(repo_path, file_change['after'])
            
            with open(os.path.join(cve_folder, 'before', file_name), 'w') as f:
                f.write(before_content)
            
            with open(os.path.join(cve_folder, 'after', file_name), 'w') as f:
                f.write(after_content)

def get_repo_url(commit_url):
    parsed_url = urlparse(commit_url)
    path_parts = parsed_url.path.split('/')
    
    # GitHub 레포지토리 URL 형식: /{owner}/{repo}
    if len(path_parts) >= 3:
        repo_path = '/'.join(path_parts[:3])
    else:
        raise ValueError(f"Invalid GitHub URL: {commit_url}")
    
    return f"{parsed_url.scheme}://{parsed_url.netloc}{repo_path}"

def group_cves_by_repo(cve_data):
    repo_to_cves = defaultdict(list)
    for cve, commit_data in cve_data.items():
        repo_url = get_repo_url(commit_data[0]['commit_url'])
        repo_to_cves[repo_url].append((cve, commit_data))
    return repo_to_cves

def main():
    with open('cpp_index_commits.json', 'r') as f:
        cve_data = json.load(f)
    
    root_folder = 'cve_code_changes'
    os.makedirs(root_folder, exist_ok=True)
    
    temp_dir = 'temp_repos'
    os.makedirs(temp_dir, exist_ok=True)
    
    repo_to_cves = group_cves_by_repo(cve_data)
    
    total_cves = sum(len(cve_list) for cve_list in repo_to_cves.values())
    processed_cves = 0

    print(f"Total CVEs to process: {total_cves}")

    for repo_url, cve_list in repo_to_cves.items():
        print(f"\nProcessing repository: {repo_url}")
        repo_path = clone_repo(repo_url, temp_dir)
        
        for cve, commit_data in cve_list:
            processed_cves += 1
            print(f"Processing CVE {processed_cves}/{total_cves}: {cve}")
            try:
                process_cve(cve, commit_data, repo_path, root_folder)
                print(f"  Completed processing {cve}")
            except Exception as e:
                print(f"  Error processing {cve}: {str(e)}")

            progress = (processed_cves / total_cves) * 100
            print(f"Overall progress: {progress:.2f}% ({processed_cves}/{total_cves} CVEs processed)")

        shutil.rmtree(repo_path)

    shutil.rmtree(temp_dir)

    print(f"\nAll {total_cves} CVEs have been processed.")

if __name__ == "__main__":
    main()