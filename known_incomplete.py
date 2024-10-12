import os
import json
import re

# CVE JSON 파일들이 저장된 디렉토리 경로
cve_directory = "../nvdcve/"

# 키워드를 정의 (정규 표현식을 사용)
keywords_patterns = [
    r"incomplete fix for CVE-\d{4}-\d+",
    r"incorrect fix for CVE-\d{4}-\d+",
    r"(exist|exists) because of a CVE-\d{4}-\d+ regression",
    r"CVE-\d{4}-\d+ (was|is) incomplete|was not complete"
]

# 특정 키워드가 description에 포함되어 있는지 확인하는 함수
def matches_keywords(description):
    for pattern in keywords_patterns:
        if re.search(pattern, description, re.IGNORECASE):
            return True
    return False

# 원하는 데이터를 추출하는 함수
def extract_commit_references(cve_file):
    results = []
    with open(cve_file, 'r', encoding='utf-8') as file:
        cve_data = json.load(file)
        for item in cve_data.get("CVE_Items", []):
            cve_id = item["cve"]["CVE_data_meta"]["ID"]
            
            # CWE-ID가 없는 경우를 처리 (None으로 설정)
            cwe_data = item["cve"]["problemtype"]["problemtype_data"]
            if cwe_data and cwe_data[0]["description"]:
                cwe_id = cwe_data[0]["description"][0]["value"]
            else:
                cwe_id = None

            # description의 value에서 키워드 패턴 확인
            description_data = item["cve"]["description"]["description_data"]
            if any(matches_keywords(desc["value"]) for desc in description_data):
                references = item["cve"]["references"]["reference_data"]
                
                # 'github'와 'commit'이 포함된 URL 추출
                for ref in references:
                    url = ref["url"]
                    if 'github' in url and 'commit' in url:
                        results.append({
                            "CVE_ID": cve_id,
                            "CWE_ID": cwe_id,
                            "Commit_URL": url
                        })
    return results

# 디렉토리 내 모든 파일을 처리하는 메인 함수
def parse_cve_files(directory):
    all_results = []
    for filename in os.listdir(directory):
        if filename.endswith(".json"):
            cve_file = os.path.join(directory, filename)
            all_results.extend(extract_commit_references(cve_file))
    
    return all_results

# 실행 예시
if __name__ == "__main__":
    results = parse_cve_files(cve_directory)
    # 추출된 결과 출력
    for result in results:
        print(result)
        # print(len(result))
        
    print(len(results))
