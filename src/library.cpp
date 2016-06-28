//
// Created by Markus Klemm on 27.06.16.
//

#include "library.h"

#include <utility>

void library::register_person(std::shared_ptr<person> p) {
    this->persons_.emplace(p);
}


void library::register_person(const person &p) {
    this->persons_.emplace(std::make_shared<person>(p));
}


void library::register_medium(std::shared_ptr<medium> m) {
    this->mediums_.emplace(m);
}


bool library::lend_medium(std::shared_ptr<medium> m, std::shared_ptr<person> p) {
    auto currently_lent_to = this->lent_to_person(m);
    if (currently_lent_to == p) {
        return true;
    } else if (currently_lent_to != std::shared_ptr<person>{}) {
        return false;
    }

    this->lent_mediums_by_person_[p].emplace(m);
    this->lent_to_person_by_medium_.emplace(m, p);

    return true;
}


std::shared_ptr<person> library::lent_to_person(std::shared_ptr<medium> m) {
    return this->lent_to_person_by_medium_[m];
}


const std::set<std::shared_ptr<medium>> &library::lent_mediums(std::shared_ptr<person> p) const {
    return this->lent_mediums_by_person_.at(p);
}


void library::give_back(std::shared_ptr<medium> m) {
    auto p = lent_to_person(m);
    this->lent_mediums_by_person_.at(p).erase(m);
    this->lent_to_person_by_medium_.erase(m);
}









