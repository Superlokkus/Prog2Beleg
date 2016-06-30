/*! @file medium.h
 * */

#ifndef PROG2BELEG_MEDIUM_H
#define PROG2BELEG_MEDIUM_H

#include <string>
#include <atomic>

class medium {
public:
    using id_t = uint8_t;

    id_t get_id() const {
        return this->id_;
    }

    bool operator==(const medium &r) const {
        return this->id_ == r.id_;
    }

    bool operator<(const medium &r) const {
        return this->id_ < r.id_;
    }

    virtual std::wstring get_description() const = 0;

    medium() = delete;

    medium(id_t id);

    virtual ~medium() { }

    static id_t get_next_id() {
        return last_seen_max_id += 1;
    }

protected:
    id_t id_;
private:
    static std::atomic<id_t> last_seen_max_id;
};


#endif //PROG2BELEG_MEDIUM_H
