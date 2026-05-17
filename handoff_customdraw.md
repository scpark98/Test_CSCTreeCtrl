# CSCTreeCtrl NM_CUSTOMDRAW 자체 paint 시도 — 다른 Claude 세션에서 이어서 진행

## 배경

Endorphin2 의 BookmarkEditDlg 의 CSCTreeCtrl 사용 시 Win11 환경에서 selection 양옆에 system accent color (light blue/cyan) box border 가 그려지는 문제 발생.

- 원인: 이전 세션에서 dark scrollbar 위해 `SetWindowTheme(L"DarkMode_Explorer")` 호출했더니 native 트리뷰가 selection 시 accent border 도 함께 그림.
- 시도한 옵션들:
  - Explorer theme — light theme 으로 되돌아감 (arrow 검정 + light gray scrollbar). 띠 그대로.
  - SetWindowTheme 호출 제거 — 결과 미관측.
  - 결국 DarkMode_Explorer 복원 후 *그 위에 selection accent 만 차단* 시도.
- 검색 결론 (Catch22, MS public.win32 forum): native theme 의 accent border 는 visual style 패키지 단위라 부분 차단 불가. **`CDRF_SKIPDEFAULT` 로 native item paint 전체 차단 후 우리가 모든 paint 책임** 이 정공.

## 현재 코드 상태

파일: `D:\1.projects_c++\Common\CTreeCtrl\SCTreeCtrl\SCTreeCtrl.cpp`

- ~line 3205 의 `OnNMCustomDraw` — **새 본문 (자체 paint)**:
  - `CDDS_PREPAINT` → `CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYPOSTPAINT`
  - `CDDS_ITEMPREPAINT` → state (drop/hot/selected) 색 결정 + row fill (TVS_FULLROWSELECT 시 client 좌우 끝, 아니면 text rect) + ▶▼ glyph (TVS_HASBUTTONS + 자식 있는 노드만, 위치 `rcText.left - 10`) + icon (image list) + text → `CDRF_SKIPDEFAULT`
  - `CDDS_POSTPAINT` → 기존 insert mark draw 유지
- ~line 3349 의 `OnNMCustomDraw_old` — 기존 NOTIFYPOSTPAINT 본문. `#if 0 ... #endif` 비활성, 비교/복원용 보존. 헤더 declaration 없음.
- `SCTreeCtrl.h` 는 변경 없음.
- `SetWindowTheme` 호출은 *현재 코드에 없음* — 이전 세션 마지막에 `git checkout HEAD` 로 가로 스크롤바 시도 직전 commit `6a6d97f` 상태로 원복 후 `OnNMCustomDraw` 만 다시 손댄 상태.

## 확인 항목 (Test_CSCTreeCtrl 빌드 + 실행)

1. selection 시 양옆 형광 띠 사라졌는지
2. ▶ ▼ glyph 위치 — `rcText.left - 10` 추정값이 native default 와 매칭되는지. 어긋나면 expand 클릭 hit-test (native 가 처리, paint 와 별개) 와 시각이 안 맞아 사용자 혼란. `iLevel` + `TVM_GETINDENT` 기반 정확 계산 필요할 수도.
3. icon 위치 — 현재 `rcText.left - icon_w - 2` 로 그림. native 와 매칭되는지.
4. text 색 / 위치
5. drag & drop highlight (`m_use_drag_and_drop` + `GetDropHilightItem`)
6. edit-in-place 시 paint 동작
7. hover (CDIS_HOT) 색 적용
8. selection active / inactive 색 둘 다 정상

## 미처리 (필요 시 추가)

- indent guide line (TVS_HASLINES)
- checkbox (TVS_CHECKBOXES)

## 저장소

- Common: `D:\1.projects_c++\Common` (github.com/scpark98/Common, branch main, 마지막 push `df7053c`)
  - `SCTreeCtrl.cpp` 만 working dir 변경 (uncommitted), 다른 파일 변경 없음.
- Test: `D:\1.projects_c++\1.test\Test_CSCTreeCtrl`
- Common 의 .vcxproj 가 ClCompile 직접 참조 구조 — Common 수정 시 Test 빌드에 즉시 반영.

## 진행

- 빌드 + Test 프로젝트 실행 + 위 1~8 항목 확인.
- 시각 어긋나는 부분 / 동작 누락 부분 미세 조정.
- 사용자 검증 후 commit + push.

**100% 완벽 보장 X** — 시도 단계, 반복 다듬기 예상. native default 와 픽셀 정확 매칭이 어려울 수 있음.

## 사용자가 알려줄 수 있으면 도움 되는 정보

- Test_CSCTreeCtrl 의 트리에 어떤 스타일 비트가 켜져 있는지 (TVS_HASLINES, TVS_HASBUTTONS, TVS_LINESATROOT, TVS_FULLROWSELECT, TVS_CHECKBOXES 등). 모르면 `.rc` 파일 직접 확인 가능.
