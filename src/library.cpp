//
// Created by Markus Klemm on 27.06.16.
//

#include "library.h"


void library::register_person(std::shared_ptr<person> p) {
    this->persons_.emplace(p);
}


void library::register_person(const person &p) {
    this->persons_.emplace(std::make_shared<person>(p));
}


void library::register_medium(std::shared_ptr<book> b) {
    this->mediums_.emplace(b);
    this->books_.emplace(b);
}


void library::register_medium(std::shared_ptr<dvd> d) {
    this->mediums_.emplace(d);
    this->dvds_.emplace(d);
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
    auto medium_person = this->lent_to_person_by_medium_.find(m);
    if (medium_person == this->lent_to_person_by_medium_.end()) {
        return {};
    }
    return medium_person->second;
}


const std::set<std::shared_ptr<medium>> &library::lent_mediums(std::shared_ptr<person> p) const {
    return this->lent_mediums_by_person_.at(p);
}


void library::give_back(std::shared_ptr<medium> m) {
    auto p = lent_to_person(m);
    this->lent_mediums_by_person_.at(p).erase(m);
    this->lent_to_person_by_medium_.erase(m);
}


std::set<std::shared_ptr<person>> library::all_persons() const {
    return this->persons_;
}


std::set<std::shared_ptr<medium>> library::all_mediums() const {
    return this->mediums_;
}


bool library::erase_person(std::shared_ptr<person> p) {
    if(this->lent_mediums(p).empty()){
        this->persons_.erase(p);
        return true;
    }
    return false;
}


void library::erase_medium(std::shared_ptr<medium> m) {
    if(this->lent_to_person(m)){
        this->give_back(m);
    }
    this->mediums_.erase(m);
}


std::set<std::shared_ptr<book>> library::all_books() const {
    return this->books_;
}


std::set<std::shared_ptr<dvd>> library::all_dvds() const {
    return this->dvds_;
}

















