//
// Created by Eric Dunaway on 4/11/20.
//
#pragma once
#ifndef COURSE_UI_STUDENT_MANAGER_H
#define COURSE_UI_STUDENT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


using namespace std;

struct Student { // represent Student structure for use in roster_
    int64_t id;
    string name;
};

class StudentManager {
private:
    int64_t id_ = 0;
    unordered_map<int64_t, shared_ptr<Student>> students_;
public:
    StudentManager()= default;;

    auto add_student(string name);
    bool remove_student(int64_t id);
    auto list_students();
};


#endif //COURSE_UI_STUDENT_MANAGER_H
