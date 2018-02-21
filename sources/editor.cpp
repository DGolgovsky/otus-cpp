/**
 * @file editor.cpp
 * @author DGolgovsky
 * @date 2018
 * @brief OTUS C++ homework #5
 *
 * Prototype of simple graphical vector editor.
 */

/**
 * @mainpage
 * Design a simple graphic vector editor.
 * Prepare class layouts reflecting the structure of the future project.
 *
 * Functional for prototyping the following:
 * - creating a new document
 * - importing a document from a file
 * - exporting a document to a file
 * - creating a graphic primitive
 * - delete a graphic primitive
 *
 * The main emphasis is on the controller template and polymorphism.
 */

#include "editor_ui.h"
/**
 * @brief App's main function
 *
 * Used with all c++ programs to init start
 * Main function to demonstrate print_ip
 */
int main(int, char **)
{
    UI editor;

    Shape* circ = new Circle();
    Shape* rect = new Rectangle();

    editor.import_img("imported_img.svg");
    editor.exec().create_shape(circ);
    editor.exec().create_shape(rect);

    editor.export_img("exported_img.svg");

    editor.exec().remove_shape(rect);
    editor.exec().remove_shape(circ);

    editor.close();

    delete circ;
    delete rect;

    return 0;
}