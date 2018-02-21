/**
 * @file   workspace.h
 * @author DGolgovsky
 * @date   2018
 * @brief  Workspace class for OTUS C++ homework #5
 *
 * @details Contain objects in workspace image area
 */

#pragma once

#include <iostream>
#include <string>
#include <map>

#include "shape.h"

/**
 * @brief Workspace Class
 *
 * Contain objects and their places
 *
 * @tparam m_id - id number of every object
 * @tparam m_name - name of every object
 * @tparam objects - std::map container
 * @returns print actions into cerr
 */
class WorkSpace
{
    using ws_map = std::map<unsigned int, Shape *>;
private:
    unsigned int m_id = 0;
    std::string m_name;
    ws_map objects;

public:
    /**
     * @brief Constructor
     * Assign name of workspace
     */
    WorkSpace(std::string const name) :m_name(name) {}

    /**
     * @brief Getter
     * Return container for future interaction
     */
    ws_map get_objects() const {
        return objects;
    }

    /**
     * @brief Setter
     * Used for importing new elements from image-file
     */
    void set_objects(ws_map &n_obj) {
        objects = n_obj;
        /// TODO maybe better importing by element
    }

    /**
     * @brief Creation
     * Create new shape
     */
    void create_shape(Shape *object) {
        ++m_id;
        objects[m_id] = object->create(m_id);
        std::cerr << "[WS]\tDraw: " << object->name() << std::endl;
    }

    /**
     * @brief Removing
     * Remove element from area
     */
    void remove_shape(Shape *object) {
        auto it = objects.find(object->id());
        if (it != objects.end()) {
            std::cerr << "[WS]\tErase: " << object->name()<< std::endl;
            object->remove();
            objects.erase(it);
        }
    }

    /**
     * @brief Name getter
     * return name of workspace
     */
    auto name() const {
        return m_name;
    }
};