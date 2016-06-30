//
// Created by Markus Klemm on 27.06.16.
//

#ifndef PROG2BELEG_LIBRARY_H
#define PROG2BELEG_LIBRARY_H

#include <memory>
#include <map>
#include <set>

#include "medium.h"
#include "person.h"
#include "book.h"
#include "dvd.h"

template <typename F>
class library_file;

class library {
public:
    const std::set<std::shared_ptr<medium>> &lent_mediums(
            std::shared_ptr<person> p) const;

    /*! @brief Returns the person that this medium is lent to
     * @return The person which lent this medium or iff not lent to anyone, a default constructed shared_ptr
     * */
    std::shared_ptr<person> lent_to_person(std::shared_ptr<medium> m);

    /*! @brief Tries to lend the given medium
     * @param m Medium which is trying to be lend
     * @return False if the person is not allowed or able to lend the medium
     * */
    bool lend_medium(std::shared_ptr<medium> m, std::shared_ptr<person> p);

    /*! @brief To give back the lent medium
     * @notice This function is idempotent
     * */
    void give_back(std::shared_ptr<medium> m);

    void register_medium(std::shared_ptr<book> b);

    void register_medium(std::shared_ptr<dvd> d);

    void register_person(std::shared_ptr<person> p);

    void register_person(const person &p);

    /*! @return False if person still has e.g. mediums lent out, otherwise true
     * */
    bool erase_person(std::shared_ptr<person> p);

    void erase_medium(std::shared_ptr<medium> m);

    std::set<std::shared_ptr<person>> all_persons() const;
    std::set<std::shared_ptr<medium>> all_mediums() const;

    std::set<std::shared_ptr<book>> all_books() const;

    std::set<std::shared_ptr<dvd>> all_dvds() const;

private:
    template<typename F>
    friend class library_file;
    std::set<std::shared_ptr<person>> persons_;
    std::set<std::shared_ptr<medium>> mediums_;
    std::set<std::shared_ptr<book>> books_;
    std::set<std::shared_ptr<dvd>> dvds_;
    std::map<std::shared_ptr<person>,
            std::set<std::shared_ptr<medium>>> lent_mediums_by_person_;
    std::map<std::shared_ptr<medium>, std::shared_ptr<person>> lent_to_person_by_medium_;
};


#endif //PROG2BELEG_LIBRARY_H
