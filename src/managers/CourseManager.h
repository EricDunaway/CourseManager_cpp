//
// Created by Eric Dunaway on 4/10/20.
//
#pragma once
#ifndef COURSE_UI_COURSE_MANAGER_H
#define COURSE_UI_COURSE_MANAGER_H


#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>
#include "StudentManager.h"

using namespace std;

/// Basic course class
class Course {
private:

    int64_t id_ = 0; /**< course ID */
    int capacity_ = 0; ///< capacity of course
    list<shared_ptr<Student>> roster_; ///< Student roster
public:
    string title; ///< Course title

    /**
     * Course Constructor
     * @param id int
     * @param course_title string
     * @param capacity int
     */
    Course(int64_t id, string course_title, int capacity) :id_(id), capacity_(capacity),title(std::move(course_title)){};

    /**
     * Constructor
     * @param c - Course Object
     */
    Course(Course &c) :id_(c.get_id()), capacity_(c.get_capacity()), title(c.title) {};

    /**
     * @return int - course id
     */
    [[nodiscard]] int64_t get_id() const;

    /**
     * @return int Course Capacity
     */
    [[nodiscard]] int get_capacity() const;
    /**
     *  Adds a student to the course
     *
     * @param student Student - student to be added
     * @return bool - True if successful
     */
    bool add_student(Student student);


};

/// Course Manager
class CourseManager {
private:
    int64_t next_id_ = 0; ///< next id to use when creating a course
    unordered_map<int64_t ,shared_ptr<Course>> courses_; ///< HashMap of courses keyed by course id
public:
    CourseManager(); ///< Constructor
    int64_t add_course(string title, int capacity); ///< Adds a Course with the course id prepopulated
    vector<shared_ptr<Course>> list_courses(); ///< @return List of courses
};

#endif //COURSE_UI_COURSE_MANAGER_H