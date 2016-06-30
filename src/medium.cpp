//
// Created by Markus Klemm on 22.06.16.
//

#include "medium.h"

medium::medium(id_t id)
        : id_(id) {
    id_t saved_highest = last_seen_max_id;
    if (saved_highest < id_) {
        last_seen_max_id.compare_exchange_strong(saved_highest, id_);
    }

}

std::atomic<medium::id_t> medium::last_seen_max_id;

