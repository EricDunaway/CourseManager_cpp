//
// Created by Eric Dunaway on 4/10/20.
//

#include "CourseManager.h"

int64_t Course::get_id() const {
    return id_;
}

bool Course::add_student(Student student) {
    int size = roster_.size();
    if(size < capacity_){
        roster_.push_back(make_shared<Student>(student));
    }
    return size <= capacity_;
}

int Course::get_capacity() const {
    return capacity_;
}

CourseManager::CourseManager() = default;;

int64_t CourseManager::add_course(string title, int capacity) {
    int64_t id = ++next_id_;
    courses_.insert(make_pair(id,make_shared<Course>(id, std::move(title), capacity)));
    return id;
}

vector<shared_ptr<Course>> CourseManager::list_courses() {
    vector<shared_ptr<Course>> courses(courses_.size());
    transform(courses_.begin(), courses_.end(), courses.begin(), [](auto pair){return pair.second;});
    sort(courses.begin(),courses.end(),[](const auto& a, const auto& b)->bool{return a->get_id() < b->get_id();});
    return courses;
}
