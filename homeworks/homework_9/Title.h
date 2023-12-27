#ifndef INC_5TH_HW_TITLE_H
#define INC_5TH_HW_TITLE_H

#include <iostream>
#include <string>
#include <set>
#include "Actor.h"

enum class Type {
    MOVIE,
    SERIES
};

class Title {
protected:
    std::string name_;
    unsigned short year_;
    std::string genre_;
    unsigned short rating_;
    std::set<Actor> actors_;

public:
    void print_json(std::ostream &os = std::cout) const;

    virtual ~Title() = default;

    virtual Type type() const = 0;

    const std::string &name() const;

    unsigned short year() const;

    const std::string &genre() const;

    unsigned short rating() const;

    const std::set<Actor> &actors() const;

    Title(const std::string &name,
          unsigned short year,
          const std::string &genre,
          unsigned short rating,
          const std::set<Actor> &actors);

};

class Movie : public Title {
protected:
    unsigned short length_;

public:
    Movie(const std::string &name,
          unsigned short year,
          const std::string &genre,
          unsigned short rating,
          const std::set<Actor> &actors,
          unsigned short length);

    Movie(std::string &&name,
          unsigned short year,
          std::string &&genre,
          unsigned short rating,
          std::set<Actor> &&actors,
          unsigned short length);

    ~Movie() override = default;

    unsigned short length() const;

    Type type() const override;

    //void print_json(std::ostream &os = std::cout) const override;

};

class Series : public Title {
protected:
    unsigned short seasons_;
    unsigned short episodes_;

public:

    Series(const std::string &name,
           unsigned short year,
           const std::string &genre,
           unsigned short rating,
           const std::set<Actor> &actors,
           unsigned short seasons,
           unsigned short episodes);

    Series(std::string &&name,
           unsigned short year,
           std::string &&genre,
           unsigned short rating,
           std::set<Actor> &&actors,
           unsigned short seasons,
           unsigned short episodes);

    unsigned short seasons() const;

    unsigned short episodes() const;

    Type type() const override;

    //void print_json(std::ostream &os = std::cout) const override;

};

inline const std::string &Title::name() const {
    return name_;
}

inline unsigned short Title::year() const {
    return year_;
}

inline const std::string &Title::genre() const {
    return genre_;
}

inline unsigned short Title::rating() const {
    return rating_;
}

inline const std::set<Actor> &Title::actors() const {
    return actors_;
}

inline unsigned short Movie::length() const {
    return length_;
}

inline unsigned short Series::seasons() const {
    return seasons_;
}

inline unsigned short Series::episodes() const {
    return episodes_;
}


#endif //INC_5TH_HW_TITLE_H
