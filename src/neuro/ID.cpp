#include"ID.hpp"

ID::ID() {
    id=0;
}

uint64_t ID::GetNewID() {
    return id++;
}