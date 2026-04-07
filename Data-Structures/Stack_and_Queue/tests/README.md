# Stack_and_Queue 테스트 안내

## 1. 문서 목적

이 디렉터리는 `Data-Structures/Stack_and_Queue`에 있는 Section C Stack and Queue 문제들을 자동으로 검증하기 위한 테스트 파일들을 포함합니다.

구성 방식은 `Linked_List/tests`와 맞춰 두어서, 같은 방식으로 빌드하고 실행하고 유지보수할 수 있습니다.

## 2. 디렉터리 구성

- `Q1_C_SQ_test.c` ~ `Q7_C_SQ_test.c`
  각 문제 파일에 대응하는 개별 테스트 스위트입니다.
- `sq_test_common.h`
  공통 assertion, 리스트 비교 함수, timeout 처리 로직이 들어 있습니다.
- `run_all_tests.sh`
  하나의 테스트 또는 전체 테스트를 컴파일하고 실행하는 스크립트입니다.
- `README.md`
  테스트 사용 방법과 유지보수 기준을 설명하는 문서입니다.

각 테스트 파일은 원본 문제 파일의 `main()`을 다른 이름으로 바꾼 뒤 직접 `#include`하여, 메뉴 입력 없이 대상 함수만 단위 테스트할 수 있도록 구성되어 있습니다.

## 3. 테스트 대상

- `Q1_C_SQ.c`: `createQueueFromLinkedList`, `removeOddValues`
- `Q2_C_SQ.c`: `createStackFromLinkedList`, `removeEvenValues`
- `Q3_C_SQ.c`: `isStackPairwiseConsecutive`
- `Q4_C_SQ.c`: `reverse`
- `Q5_C_SQ.c`: `recursiveReverse`
- `Q6_C_SQ.c`: `removeUntil`
- `Q7_C_SQ.c`: `balanced`

공통적으로 아래 항목을 확인합니다.

- 결과 원소 순서가 기대와 일치하는지
- `head`, `size` 상태가 정상적으로 유지되는지
- 빈 자료구조, 원소 1개인 경우 같은 경계 조건에서 안전하게 동작하는지
- 기존 queue 또는 stack에 값이 이미 들어 있을 때 재생성 전에 비우는지
- 문제별 요구사항에 맞는 동작을 수행하는지

## 4. 테스트 가정

현재 테스트는 아래 가정을 기준으로 작성되어 있습니다.

- `createQueueFromLinkedList`
  queue가 비어 있지 않으면 먼저 비우고, linked list의 첫 번째 노드부터 마지막 노드까지 순서대로 enqueue합니다. 원본 linked list는 변경하지 않는 것으로 봅니다.
- `createStackFromLinkedList`
  stack이 비어 있지 않으면 먼저 비우고, linked list의 첫 번째 노드부터 마지막 노드까지 순서대로 push합니다. 따라서 최종 stack의 top은 원래 linked list의 마지막 값이 됩니다.
- `isStackPairwiseConsecutive`
  stack의 top부터 두 개씩 짝을 지어 검사하며, 원소 개수가 홀수이면 즉시 0을 반환한다고 가정합니다. 짝수 개수인 경우 각 pair의 차이 절댓값이 1인지 검사하고, 하나라도 조건을 만족하지 않으면 0, 모두 통과하면 1을 반환하며 검사 후 stack 순서는 원래대로 복원된다고 가정합니다.
- `removeUntil`
  top부터 pop하다가 선택한 값이 처음으로 나타나면 멈추며, 그 값 자체는 stack에 남겨 둡니다. 값이 없으면 stack은 비게 됩니다.
- `balanced`
  balanced한 식이면 `0`, unbalanced한 식이면 0이 아닌 값을 반환한다고 가정합니다. 이는 제공된 `main()`의 출력 방식에 맞춘 기준입니다.

문제 해석이나 채점 기준이 달라지면, 해당 테스트 파일과 이 문서를 함께 수정해야 합니다.

## 5. 빌드 및 실행 방법

먼저 테스트 디렉터리로 이동합니다.

```bash
cd Data-Structures/Stack_and_Queue/tests
```

개별 테스트를 직접 컴파일하고 실행하려면 다음과 같이 사용할 수 있습니다.

```bash
gcc -std=c11 -Wall -Wextra -g Q1_C_SQ_test.c -o Q1_C_SQ_test.out
./Q1_C_SQ_test.out
```

메모리 누수까지 확인하려면 다음처럼 Valgrind를 사용할 수 있습니다.

```bash
valgrind --leak-check=full ./Q1_C_SQ_test.out
```

전체 테스트를 한 번에 실행하려면 스크립트를 사용합니다.

```bash
./run_all_tests.sh
```

특정 테스트만 실행할 수도 있습니다.

```bash
./run_all_tests.sh --suite Q4_C_SQ_test
```

특정 테스트를 Valgrind 모드로 실행할 수도 있습니다.

```bash
./run_all_tests.sh --mode valgrind --suite Q2_C_SQ_test
```

컴파일 결과물은 `tests/build/` 아래에 저장됩니다.

## 6. CI

저장소에는 `/.github/workflows/stack-and-queue-ci.yml` 워크플로가 추가되어 있으며, Stack and Queue 테스트를 Ubuntu 환경에서 자동 실행합니다.

동작 방식은 Linked List CI와 동일합니다.

1. 어떤 Stack and Queue 관련 파일이 변경되었는지 확인합니다.
2. 변경된 문제에 해당하는 테스트 스위트만 선택합니다.
3. 공통 헤더, 실행 스크립트, workflow 자체가 변경되면 전체 스위트를 실행합니다.
4. 선택된 테스트를 matrix job으로 각각 컴파일하고 실행합니다.

## 7. 유지보수 기준

- 테스트 파일 이름은 원본 문제 파일 이름과 일관되게 유지합니다.
- 문제 구현이 바뀌면 해당 테스트도 함께 갱신합니다.
- 여러 테스트에서 공통으로 쓰는 검증 로직은 `sq_test_common.h`에 두고, 문제별 기대 동작은 각 테스트 파일에서 관리합니다.
- 기대 동작 해석이 바뀌면 테스트 코드와 README의 가정 설명을 함께 수정합니다.
