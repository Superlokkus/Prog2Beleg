//
// Created by Markus Klemm on 27.06.16.
//

#ifndef PROG2BELEG_LIBRARY_FILE_H
#define PROG2BELEG_LIBRARY_FILE_H

template <typename F>
class library_file {
public:
    library_file() = delete;

    library_file(F &&file_stream) :
            file_stream(std::move(file_stream)) { }


private:
    F file_stream;
};


#endif //PROG2BELEG_LIBRARY_FILE_H
