#include "Detection.h"
#include "Detection.h"

Detection::Detection(){
    // default parameters
    this->u1 = 0; // detection location
    this->v1 = 0;
    this->u2 = 0;
    this->v2 = 0;
    this->ide = 0;  // detection identifier
    this->score = 0;  // detection score
}

Detection::~Detection() = default;

void Detection::set_u1(int ua) {
    this->u1 = ua;
}

void Detection::set_v1(int va) {
    this->v1 = va;
}

void Detection::set_u2(int ub) {
    this->u2 = ub;
}

void Detection::set_v2(int vb) {
    this->v2 = vb;
}

void Detection::set_score(float scoreToSet) {
    this->score = scoreToSet;
}

void Detection::set_ide(int ideToSet) {
    this->ide = ideToSet;
}

int Detection::get_u1() {
    return this->u1;
}

int Detection::get_v1() {
    return this->v1;
}

int Detection::get_u2() {
    return this->u2;
}

int Detection::get_v2() {
    return this->v2;
}

float Detection::get_score() {
    return this->score;
}

int Detection::get_ide() {
    return this->ide;
}
