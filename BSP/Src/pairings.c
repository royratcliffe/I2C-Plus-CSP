/*
 * pairings.c
 *
 *  Created on: 15 Jan 2023
 *      Author: Roy Ratcliffe
 */

#include <malloc.h>
#include <string.h>

#include "pairings.h"

struct pairing *push_pairing(struct pairing **top, void *left, void *right) {
  if (left == NULL || right == NULL)
    return NULL;
  struct pairing *push = malloc(sizeof(struct pairing));
  if (push == NULL)
    return NULL;
  push->pairing = *top;
  *top = push;
  push->left = left;
  push->right = right;
  return push;
}

void *for_left_and_right_pairing(struct pairing **top,
                                 void *(*func)(void *left, void *right,
                                               void *arg),
                                 void *arg) {
  for (struct pairing *pairing = *top; pairing; pairing = pairing->pairing) {
    void *result = (*func)(pairing->left, pairing->right, arg);
    if (result)
      return result;
  }
  return NULL;
}

static void *left_eq(void *left, void *right, void *arg) {
  return left == arg ? right : NULL;
}

void *right_for_left_pairing(struct pairing **top, void *left) {
  return for_left_and_right_pairing(top, left_eq, left);
}

static void *left_stricmp(void *left, void *right, void *arg) {
  return stricmp(left, arg) == 0 ? right : NULL;
}

void *right_for_left_stricmp_pairing(struct pairing **top, const char *left) {
  return for_left_and_right_pairing(top, left_stricmp, (void *)left);
}

static void *right_eq(void *left, void *right, void *arg) {
  return right == arg ? left : NULL;
}

void *left_for_right_pairing(struct pairing **top, void *right) {
  return for_left_and_right_pairing(top, right_eq, right);
}

void free_pairings(struct pairing **top) {
  struct pairing *pairing = *top;
  if (pairing == NULL)
    return;
  *top = NULL;
  while (pairing) {
    struct pairing *pop = pairing;
    pairing = pairing->pairing;
    free(pop);
  }
}
