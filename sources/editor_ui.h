/**
 * @file   editor_ui.h
 * @author DGolgovsky
 * @date   2018
 * @brief  User Interface class for OTUS C++ homework #5
 *
 * @details Contain methods for interrupt with workspace image area
 */

#pragma once

#include <iostream>
#include "workspace.h"

/**
 * @brief UI Class
 *
 * Contain main functions
 *
 * @tparam Workspace* - pointer to workspace object
 * @returns print actions into cerr
 */
class UI
{
public:
    /**
     * @brief Constructor
     * Create new ptr into workspace
     */
    UI() {
        img = new WorkSpace("Empty image");
        std::cerr << "[UI] Creating new empty workspace\n";
    }
    /**
     * @brief Destructor
     * Delete workspace object
     */
    ~UI() {
        delete(img);
        std::cerr << "[UI] Close workspace\n";
    }

    /**
     * @brief Emulate button exit
     * Call destructor
     */
    void close() {
        this->~UI();
    }

    /**
     * @brief Save file
     * Save workspace with new name
     */
    void save_as() {
        // Recieve new_name from GUI
        std::string new_name = "New workspace";
        std::cerr << "[UI] Save workspace as: " << new_name << std::endl;
    }

    /**
     * @brief Save file
     * Save workspace with same name or call save_as()
     */
    void save() {
        if (img->name() != "Empty image") {
            std::cerr << "[UI] Save workspace\n";
            return;
        }
        this->save_as();
    }

    /**
     * @brief Import image
     * Importing objects from image file
     */
    void import_img(std::string const &img_name) {
        // Filetype --> img->set_objects()

        std::cerr << "[UI] Importing image: " << img_name << std::endl;
        /**
         * Importing objects from image-file.
         * For example we import triangle object
         */
        img->create_shape(new Triangle());
    }

    /**
     * @brief Export image
     * Exporting objects to image file
     */
    void export_img(std::string const &img_name) {
        // Filetype <-- img->get_objects()
        std::cerr << "[UI] Exporting image: " << img_name << std::endl;
    }

    /**
     * @brief Workspace
     * Return pointer into main workspace object for interaction
     */
    WorkSpace &exec() {
        return *img;
    }
private:
    WorkSpace *img;
};