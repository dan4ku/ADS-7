// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;
  Car* currentCar = first->next;

  while (currentCar != first) {
    Car* temporaryCar = currentCar;
    currentCar = currentCar->next;
    delete temporaryCar;
  }

  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car(light);

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* lastCar = first->prev;
    lastCar->next = newCar;
    newCar->prev = lastCar;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  countOp = 0;
  if (!first) return 0;
  const Car* currentPtr = first;
  bool isLightFound = false;

  do {
    if (currentPtr->light) {
      isLightFound = true;
      break;
    }
    currentPtr = currentPtr->next;
  } while (currentPtr != first);

  if (!isLightFound) {
    first->light = true;
    const Car* walker = first->next;
    ++countOp;
    int length = 1;
    while (walker != first) {
      walker = walker->next;
      ++countOp;
      ++length;
    }
    for (int64_t counter = 0; counter < length; ++counter) {
      walker = walker->prev;
      ++countOp;
    }
    first->light = false;
    return length;
  } else {
    const Car* walker = first->next;
    ++countOp;
    int64_t totalLength = 1;
    while (walker != first) {
      walker = walker->next;
      ++countOp;
      ++totalLength;
    }
    countOp += totalLength * totalLength;
    return totalLength;
  }
}
