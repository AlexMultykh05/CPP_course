#ifndef INC_5TH_HW_MOVIE_H
#define INC_5TH_HW_MOVIE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>

class Movie {
private:
    std::string name_;
    unsigned short year_;
    std::string genre_;
    unsigned short rating_;
    std::set<std::string> actors_;

public:
    const std::string& name() const;

    unsigned short year() const;

    const std::string& genre() const;

    unsigned short rating() const;

    const std::set<std::string>& actors() const;

    Movie(const std::string &name, unsigned short year, const std::string &genre, unsigned short rating,
          const std::set<std::string> &actors);

    Movie(std::string&& name, unsigned short year, std::string&& genre, unsigned short rating,
          std::set<std::string>&& actors);

    void print_json(std::ostream& out) const;

};

inline const std::string& Movie::name() const {
    return name_;
}

inline unsigned short Movie::year() const {
    return year_;
}

inline const std::string& Movie::genre() const {
    return genre_;
}

inline unsigned short Movie::rating() const {
    return rating_;
}

inline const std::set<std::string>& Movie::actors() const {
    return actors_;
}


#endif //INC_5TH_HW_MOVIE_H
