# Linked List 테스트 안내

## 1. 문서 목적

이 문서는 `Linked_List/tests` 디렉터리에 있는 테스트 파일들의 역할과
로컬 실행 방법을 설명합니다. 앞으로 GitHub Actions 기반 CI를 붙일 때도
이 디렉터리의 테스트 흐름을 기준으로 사용하게 됩니다.

## 2. 디렉터리 구성

- `Q1_A_LL_test.c` ~ `Q7_A_LL_test.c`
  각 문제별 테스트 파일입니다.
- `ll_test_common.h`
  공통 테스트 매크로, 리스트 검증 도우미, 타임아웃 처리 로직이 들어 있습니다.
- `README.md`
  테스트 사용법과 운영 원칙을 정리한 문서입니다.

각 테스트 파일은 상위 디렉터리의 문제 파일을 직접 `#include` 해서
대상 함수를 함수 단위로 검증합니다.

## 3. 테스트 대상

- `Q1_A_LL.c`: `insertSortedLL`
- `Q2_A_LL.c`: `alternateMergeLinkedList`
- `Q3_A_LL.c`: `moveOddItemsToBack`
- `Q4_A_LL.c`: `moveEvenItemsToBack`
- `Q5_A_LL.c`: `frontBackSplitLinkedList`
- `Q6_A_LL.c`: `moveMaxToFront`
- `Q7_A_LL.c`: `RecursiveReverse`

공통적으로 아래 항목을 확인합니다.

- 리스트 순서가 기대값과 일치하는지
- `head`, `size`, 노드 연결 상태가 유지되는지
- 빈 리스트나 단일 노드 같은 경계 상황에서도 안전한지
- 문제 요구사항에 맞는 동작을 수행하는지

## 4. 테스트 범위

### 포함하는 범위

- 각 문제 함수의 정상 동작
- 빈 리스트, 단일 노드, 홀수/짝수 길이 등 기본 경계 조건
- 보조 함수(`insertNode`, `removeAllItems`)를 활용한 입력 구성과 정리

### 제외하는 범위

- 메뉴 기반 `main()`의 입력 흐름 자체
- `printf` 출력 문자열 형식의 상세 비교
- 성능 측정
- 대규모 랜덤 테스트

이 테스트는 Linked List 실습 문제의 핵심 로직을 빠르게 자동 검증하는 데
초점을 둡니다.

## 5. 문제별 검증 기준

| 테스트 파일 | 검증 내용 |
|---|---|
| `Q1_A_LL_test.c` | 정렬 삽입 결과, 반환 index, 중복값 처리, `NULL` 입력 처리 |
| `Q2_A_LL_test.c` | 두 리스트의 alternate merge 결과와 남은 노드 처리 |
| `Q3_A_LL_test.c` | 홀수를 뒤로 이동한 뒤의 stable partition 결과 |
| `Q4_A_LL_test.c` | 짝수를 뒤로 이동한 뒤의 stable partition 결과 |
| `Q5_A_LL_test.c` | front/back 분할 결과와 홀수 길이에서 front 우선 분할 |
| `Q6_A_LL_test.c` | 최대값을 head로 이동시키는지 여부 |
| `Q7_A_LL_test.c` | 재귀 reverse 이후 리스트 순서 역전 |

## 6. 빌드 및 실행 방법

이 저장소는 devcontainer 환경에서 `/usr/bin/gcc` 사용을 기준으로
실습한다고 가정합니다.

테스트 디렉터리로 이동합니다.

```bash
cd Data-Structures/Linked_List/tests
```

개별 테스트를 직접 컴파일하려면 다음처럼 실행합니다.

```bash
gcc -std=c11 -Wall -Wextra -g Q1_A_LL_test.c -o Q1_A_LL_test.out
```

실행 예시는 아래와 같습니다.

```bash
./Q1_A_LL_test.out
```

메모리 검사까지 함께 보고 싶다면 다음처럼 실행할 수 있습니다.

```bash
valgrind --leak-check=full ./Q1_A_LL_test.out
```

여러 테스트를 반복해서 돌릴 예정이라면 `run_all_tests.sh`를 사용하는 편이 더 편합니다.

```bash
./run_all_tests.sh
```

특정 문제만 실행할 수도 있습니다.

```bash
./run_all_tests.sh --suite Q3_A_LL_test
```

이 스크립트는 빌드 결과물을 `tests/build/` 아래에 모아 두므로,
실습 중 생성 파일이 테스트 소스와 섞이지 않도록 도와줍니다.

## 7. 결과 해석 방법

각 테스트는 여러 개의 check를 수행하고, 각 항목마다 `PASS` 또는 `FAIL`을
출력합니다.

- `PASS`: 현재 구현이 기대 동작을 만족합니다.
- `FAIL`: 반환값, 리스트 순서, 크기, 연결 상태 중 하나 이상이 기대와 다릅니다.

마지막에는 테스트 파일별 총 검사 수와 실패 수를 요약하며,
실패 수가 0이면 종료 코드 0을 반환합니다.

## 8. GitHub Actions 연습

이 저장소에는 GitHub Actions용 워크플로 파일
`/.github/workflows/linked-list-ci.yml`이 추가됩니다.

이 워크플로는 아래 순서로 동작합니다.

1. GitHub의 Ubuntu 러너에서 저장소를 checkout 합니다.
2. `gcc`와 `valgrind`를 설치합니다.
3. `Q1_A_LL_test`부터 `Q7_A_LL_test`까지를 matrix job으로 나누어 실행합니다.
4. 컴파일 또는 테스트 실행이 실패하면 해당 job과 workflow를 실패로 표시합니다.

처음 학습할 때는 다음 순서로 보는 것을 추천합니다.

1. GitHub 저장소에서 `Actions` 기능을 활성화합니다.
2. 이 브랜치를 push 합니다.
3. GitHub 저장소의 `Actions` 탭에서 `Linked List CI` workflow를 엽니다.
4. `Run workflow`로 수동 실행해 봅니다.
5. 이후 `push`, `pull_request` 때 자동으로 다시 도는지 확인합니다.

## 9. 유지보수 원칙

- 문제 파일의 기대 동작이 바뀌면 해당 테스트도 함께 갱신합니다.
- 버그를 발견하면 먼저 실패하는 테스트를 추가하거나 보강한 뒤 수정합니다.
- 수동 확인보다 자동 테스트 결과를 우선 기준으로 삼습니다.
- 공통 규칙은 `ll_test_common.h`에 모으고, 문제별 기대 결과는 각 테스트 파일에서 관리합니다.

## 10. 현재 테스트가 두는 전제

현재 테스트는 각 문제 설명과 기존 메인 프레임을 기준으로 다음 전제를 사용합니다.

- `Q2`
  merge 결과는 `ll1`에 반영되고, `ll2`에는 남은 노드만 유지된다고 봅니다.
- `Q3`, `Q4`
  홀수/짝수 이동은 상대 순서를 유지하는 stable partition 방식으로 봅니다.
- `Q5`
  홀수 개 노드일 때 front list가 하나 더 가진다고 봅니다.
- `Q6`
  최대값 하나를 앞으로 이동시키고 나머지 상대 순서는 유지된다고 봅니다.
- `Q7`
  리스트 전체를 역순으로 뒤집는 재귀 reverse를 기대합니다.

문제 해석이나 구현 기준이 달라지면, 문서와 테스트 기준도 함께 조정해야 합니다.
