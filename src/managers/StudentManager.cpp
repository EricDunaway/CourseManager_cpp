//
// Created by Eric Dunaway on 4/11/20.
//

#include "StudentManager.h"

#include <utility>


auto StudentManager::add_student(string name) {
    int64_t newId = ++id_;
    students_.insert(make_pair(newId, make_shared<Student>( Student{newId,std::move(name)})));
    return newId;
}

auto StudentManager::list_students() {
    vector<shared_ptr<Student>> students(students_.size());
    transform(students_.begin(), students_.end(), students.begin(), [](auto pair){return pair.second;});
    return students;
}

bool StudentManager::remove_student(int64_t id) {
    return students_.erase(id);
}