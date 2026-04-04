# Linked List Tests README

## 1. 문서 목적

이 문서는 `Linked_List/tests` 디렉토리에 있는 테스트 파일들의 목적, 범위, 실행 방법을 설명한다.

## 2. 디렉토리 구성

- `Q1_A_LL_test.c` ~ `Q7_A_LL_test.c`: 각 문제별 테스트 파일
- `ll_test_common.h`: 공통 테스트 매크로와 리스트 검증 도우미
- `README.md`: 테스트 폴더 전체에 대한 공통 문서

각 테스트 파일은 상위 디렉토리의 원본 문제 파일을 직접 include 하여 함수 단위로 검증한다.

## 3. 테스트 대상

- `Q1_A_LL.c`: `insertSortedLL`
- `Q2_A_LL.c`: `alternateMergeLinkedList`
- `Q3_A_LL.c`: `moveOddItemsToBack`
- `Q4_A_LL.c`: `moveEvenItemsToBack`
- `Q5_A_LL.c`: `frontBackSplitLinkedList`
- `Q6_A_LL.c`: `moveMaxToFront`
- `Q7_A_LL.c`: `RecursiveReverse`

공통적으로 아래 항목을 함께 확인한다.

- 리스트 순서가 기대한 결과와 일치하는가
- `head`, `size`, 노드 연결 상태가 깨지지 않는가
- 빈 리스트나 단일 노드 같은 경계 상황에서 안전하게 동작하는가
- 문제 설명상 핵심 변환 로직이 올바르게 수행되는가

## 4. 테스트 범위

### 포함하는 범위

- 문제별 핵심 함수의 정상 동작
- 대표 경계값 테스트
- 빈 리스트, 한 개 노드, 짝수/홀수 길이 같은 기본 예외 상황
- 보조 함수(`insertNode`, `removeAllItems`)를 활용한 입력 구성과 정리

### 제외하는 범위

- 메뉴 기반 `main()`의 사용자 입력 흐름 자체
- `printf` 출력 문자열 형식의 상세 비교
- 성능 측정
- 대규모 랜덤 테스트

이번 테스트는 학습용 Linked List 문제들의 핵심 로직을 자동 검증하는 데 집중한다.

## 5. 문제별 검증 기준

| 테스트 파일 | 핵심 검증 내용 |
|---|---|
| `Q1_A_LL_test.c` | 정렬 삽입 결과, 반환 index, 중복값 처리, `NULL` 입력 처리 |
| `Q2_A_LL_test.c` | 두 리스트 alternate merge 결과와 남은 노드 처리 |
| `Q3_A_LL_test.c` | 홀수를 뒤로 이동한 뒤의 stable partition 결과 |
| `Q4_A_LL_test.c` | 짝수를 뒤로 이동한 뒤의 stable partition 결과 |
| `Q5_A_LL_test.c` | front/back 분할 결과와 홀수 길이에서 front 우선 분할 |
| `Q6_A_LL_test.c` | 최대값을 head로 이동시키는지 여부 |
| `Q7_A_LL_test.c` | 재귀 reverse 이후 리스트 순서 역전 |

## 6. 빌드 및 실행 방법

이 저장소는 devcontainer 환경에서 `/usr/bin/gcc` 사용을 기준으로 설정되어 있다.

테스트 디렉토리로 이동:

```bash
cd Data-Structures/Linked_List/tests
```

개별 테스트 컴파일 예시:

```bash
gcc -std=c11 -Wall -Wextra -g Q1_A_LL_test.c -o Q1_A_LL_test.out
```

개별 테스트 실행 예시:

```bash
./Q1_A_LL_test.out
```

다른 문제도 같은 방식으로 파일명만 바꿔 실행한다.

가능하면 메모리 검증도 함께 수행한다.

```bash
valgrind --leak-check=full ./Q1_A_LL_test.out
```

## 7. 결과 해석 방법

각 테스트는 여러 개의 check를 수행하고, 각 check마다 PASS/FAIL을 출력한다.

- PASS: 현재 구현이 정의한 동작 기준을 만족함
- FAIL: 반환값, 리스트 순서, 크기, 연결 상태 중 하나 이상이 기대와 다름

마지막에는 테스트 파일별로 총 검사 수와 실패 수를 요약한다. 실패 수가 0이면 종료 코드 0을 반환하도록 구성했다.

## 8. 유지보수 원칙

- 문제 파일의 동작 기준이 바뀌면 대응하는 테스트도 함께 갱신한다.
- 버그를 발견하면 먼저 실패하는 테스트를 추가한 뒤 수정한다.
- 수동 확인보다 자동 테스트 결과를 우선 기준으로 삼는다.
- 공통 규칙은 `ll_test_common.h`에 모으고, 문제별 기대 결과는 각 테스트 파일에서 관리한다.

## 9. 테스트 작성 시 전제

현재 테스트는 각 문제 이름과 메인 프레임 문구를 기준으로 가장 자연스러운 기대 동작을 검증한다.

특히 아래 전제를 사용한다.

- `Q2`: merge 결과는 `ll1`에 누적되고, `ll2`에는 남은 노드만 유지된다.
- `Q3`, `Q4`: 홀수/짝수 이동은 상대 순서를 유지하는 stable partition 방식으로 본다.
- `Q5`: 홀수 개 노드는 front list가 하나 더 가진다고 본다.
- `Q6`: 최대값 하나를 앞으로 이동시키고 나머지 상대 순서는 유지된다고 본다.
- `Q7`: 리스트 전체를 역순으로 뒤집는 재귀 reverse를 기대한다.

문제 의도와 실제 구현 기준이 달라지면 이 문서와 테스트 기대값을 함께 조정한다.
