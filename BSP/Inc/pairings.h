/*
 * pairings.h
 *
 *  Created on: 15 Jan 2023
 *      Author: Roy Ratcliffe
 */

#pragma once

struct pairing {
  void *left, *right;
  struct pairing *pairing;
};

struct pairing *push_pairing(struct pairing **top, void *left, void *right);
void *for_left_and_right_pairing(struct pairing **top,
                                 void *(*func)(void *left, void *right,
                                               void *arg),
                                 void *arg);
void *right_for_left_pairing(struct pairing **top, void *left);
void *right_for_left_stricmp_pairing(struct pairing **top, const char *left);
void *left_for_right_pairing(struct pairing **top, void *right);
void free_pairings(struct pairing **top);
