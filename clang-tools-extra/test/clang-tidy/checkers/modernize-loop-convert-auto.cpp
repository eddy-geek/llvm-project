// RUN: %check_clang_tidy %s modernize-loop-convert %t -- \
// RUN:   -config="{CheckOptions: [{key: modernize-loop-convert.AutoTypeNameLength, value: '22'}]}" \
// RUN:   -- -I %S/Inputs/modernize-loop-convert

#include "structures.h"

const int n = 10;
int arr[n];
int nums[n];

void autotype() {
  Val Teas[N];
  for (int I = 0; I < N; ++I) {
    Teas[I].g();
  }
  // CHECK-MESSAGES: :[[@LINE-3]]:3: warning: use range-based for loop instead
  // CHECK-FIXES: for (Tea & Tea : Teas)
  // CHECK-FIXES-NEXT: Tea.g();

  // NonTriviallyCopyable has length 21 < 22
  const NonTriviallyCopyable NonCopy[N]{};
  for (int I = 0; I < N; ++I) {
    printf("2 * %d = %d\n", NonCopy[I].X, NonCopy[I].X + NonCopy[I].X);
  }
  // CHECK-MESSAGES: :[[@LINE-3]]:3: warning: use range-based for loop instead
  // CHECK-FIXES: for (const NonTriviallyCopyable & I : NonCopy)
  // CHECK-FIXES-NEXT: printf("2 * %d = %d\n", I.X, I.X + I.X);

  // TriviallyCopyableButBig has length 23 > 22
  const TriviallyCopyableButBig Big[N]{};
  for (int I = 0; I < N; ++I) {
    printf("2 * %d = %d\n", Big[I].X, Big[I].X + Big[I].X);
  }
  // CHECK-MESSAGES: :[[@LINE-3]]:3: warning: use range-based for loop instead
  // CHECK-FIXES: for (const auto & I : Big)
  // CHECK-FIXES-NEXT: printf("2 * %d = %d\n", I.X, I.X + I.X);
}
