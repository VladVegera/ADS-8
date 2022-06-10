// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() :countOp(0), first(nullptr), tail(nullptr) {}

Train::Cage* Train::create(bool light) {
  Cage *cage = new Cage;
  cage->light = light;
  cage->next = nullptr;
  cage->prev = nullptr;
  return cage;
}

int Train::getOpCount() {
  return countOp;
}

void Train::addCage(bool light) {
  if (last && first) {
    last->next = create(light);
    last->next->prev = last;
    last = last->next;
    if (!last->next) last->next = first;
    if (!first->prev) first->prev = last;
  } else {
      first = create(light);
      last = first;
  }
}

int Train::getLength() {
  first->light = true;
  Cage *temp = first;
  int tempCount = 0, length = 0;
  while (true) {
    ++countOp;
    ++tempCount;
    temp = temp->next;
    if (temp->light) {
      int tmp = tempCount;
      temp->light = false;
      for (int i = tempCount; tempCount; --tempCount, ++countOp) {
        temp = temp->prev;
      }
      if (!temp->light) {
        length = tmp;
        break;
      }
    }
  }
  return length;
}
