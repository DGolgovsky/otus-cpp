/**
 * @file   shape.h
 * @author DGolgovsky
 * @date   2018
 * @brief  Shape class for OTUS C++ homework #5
 *
 * @details Contain primitives of shapes
 */

#pragma once

/**
 * @brief Parent class
 */
class Shape
{
public:
    virtual Shape *create(unsigned int) = 0;
    virtual void remove() = 0;
    std::string name() const {
        return s_name;
    }
    unsigned int id() const {
        return s_id;
    }
    virtual ~Shape() = default;
protected:
    std::string s_name;
    unsigned int s_id;
};

/**
 * @brief Child class of circle
 */
class Circle : public Shape
{
public:
    Circle *create(unsigned int id_) override {
        s_name = "circle";
        s_id = id_;
        return this;
    }

    void remove() override {
        this->~Circle();
    }
};

/**
 * @brief Child class of triangle
 */
class Triangle : public Shape
{
public:
    Triangle *create(unsigned int id_) override {
        s_name = "triangle";
        s_id = id_;
        return this;
    }
    void remove() override {
        this->~Triangle();
    }
};

/**
 * @brief Child class of rectangle
 */
class Rectangle : public Shape
{
public:
    Rectangle *create(unsigned int id_) override {
        s_name = "rectangle";
        s_id = id_;
        return this;
    }
    void remove() override {
        this->~Rectangle();
    }
};