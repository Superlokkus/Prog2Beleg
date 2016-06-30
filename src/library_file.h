/*! @file library_file.h
 *
 * Lets say the file is encoded in utf16 format is,
 * <separator> = space
 * <file> = <header> \n (<person> \n)* (<book> \n)* (<dvd> \n)* (<lent_relation*>\n)
 * <header> = L"MK_Lib_Format" <separator> count_of_persons <separator> count_of_books <separator> count_of_dvds <separator> count_of_lent_relations>
 * <person> = id <separator> "name" <separator> "surname"
 * <book> = id <separator> "title" <separator> "author" <separator> "isbn"
 * <dvd> = id <separator> "title" <separator> "director"
 * <lent_relation> = id_person <separator> id_medium
 * */

#ifndef PROG2BELEG_LIBRARY_FILE_H
#define PROG2BELEG_LIBRARY_FILE_H

#include "library.h"
#include <string>
#include <fstream>

template<typename F = std::fstream>
class library_file {
public:
    library_file() = delete;

    library_file(F &&file_stream) :
            file_stream(std::move(file_stream)) {
        file_stream.exceptions(std::iostream::failbit | std::iostream::badbit);

    }

    std::shared_ptr<library> open() const {
        return {};
    }

    void save(const std::shared_ptr<library> lib) {
        if (file_stream.is_open() && file_stream.good()) {
            throw std::runtime_error("File not even open");
        }
//        file_stream << magic_number << separator;
//        file_stream << lib->persons_.size() << separator
//        << lib->books_.size() << separator
//        << lib->dvds_.size() << separator << lib->lent_to_person_by_medium_.size() << newline;

        file_stream.close();
        if (!file_stream.good()) {
            throw std::runtime_error("File is no good");
        }
    }


private:
    F file_stream;

    static constexpr auto magic_number = L"MK_Lib_Format";
    static constexpr auto separator = L" ";
    static constexpr auto newline = L"\n";
};


#endif //PROG2BELEG_LIBRARY_FILE_H
