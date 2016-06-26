//
// Created by Markus Klemm on 26.06.16.
//

#ifndef PROG2BELEG_PERSON_H
#define PROG2BELEG_PERSON_H

#include <vector>
#include <memory>

#include "medium.h"

class person {
public:
    const std::vector<std::shared_ptr<medium>> &lent_mediums() const;

    /*! @brief Tries to lend the given medium
     * @param m Medium which is trying to be lend
     * @return False if the person is not allowed or able to lend the medium
     * */
    bool lend_medium(std::shared_ptr<medium> m);

    uint8_t id;

private:
    std::vector<std::shared_ptr<medium>> lent_mediums_;
};


#endif //PROG2BELEG_PERSON_H
