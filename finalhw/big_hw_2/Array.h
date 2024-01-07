#ifndef INC_11_12TH_HW_ARRAY_H
#define INC_11_12TH_HW_ARRAY_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <cstddef>
#include <iterator>

namespace lib {

    constexpr size_t DEFAULT_BLOCK_SIZE = 10;

    template<typename element>
    class Array {
    private:
        std::vector<element *> data_;
        size_t block_size_;
        size_t curr_capacity_;
        size_t curr_size_;

        void *add_block();

        void remove_block();

        void check_index(size_t index) const;

        void remove_block_condition();

        void add_block_condition();

        void try_push_all(const Array<element> &other);

    public:
        template<bool constant>
        class iterator_base;

        Array(size_t block_size = DEFAULT_BLOCK_SIZE);

        Array(std::initializer_list<element> list);

        Array(const Array<element> &other);

        Array(Array<element> &&other) noexcept;

        Array(size_t count, const element &value);

        ~Array() noexcept;

        size_t size() const;

        size_t capacity() const;

        void print(std::ostream &os = std::cout) const;

        void clear();

        void swap_all(Array<element> &other);

        void push_back(const element &item);

        void push_back(element &&item);

        void pop_back();

        element &at(size_t index);

        const element &at(size_t index) const;

        element &operator[](size_t index);

        const element &operator[](size_t index) const;

        Array<element> &operator=(Array<element> &other);

        Array<element> &operator=(Array<element> &&other) noexcept;

        using iterator = iterator_base<false>;
        using const_iterator = iterator_base<true>;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

    };

    template<typename element>
    Array<element>::Array(size_t block_size): block_size_(block_size), curr_capacity_(0), curr_size_(0) {}

    template<typename element>
    Array<element>::Array(std::initializer_list<element> list): Array(list.size()) {
        try {
            for (const auto &item: list) {
                push_back(item);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    template<typename element>
    Array<element>::~Array() noexcept {
        clear();
    }

    template<typename element>
    Array<element>::Array(const Array<element> &other): Array(other.block_size_) {
        try_push_all(other);
    }

    template<typename element>
    Array<element>::Array(Array<element> &&other) noexcept: block_size_(DEFAULT_BLOCK_SIZE),
                                                            curr_capacity_(0), curr_size_(0) {
        swap_all(other);
    }

    template<typename element>
    Array<element>::Array(size_t count, const element &value): Array(count) {
        while (count > 0) {
            push_back(value);
            --count;
        }
    }

    template<typename element>
    void swap(Array<element> &first, Array<element> &second) {
        first.swap_all(second);
    }

    template<typename element>
    inline size_t Array<element>::size() const {
        return curr_size_;
    }

    template<typename element>
    inline size_t Array<element>::capacity() const {
        return curr_capacity_;
    }

    template<typename element>
    void Array<element>::print(std::ostream &os) const {
        os << "[";
        for (size_t i = 0; i < curr_size_; ++i) {
            os << data_[i / block_size_][i % block_size_];
            if (i != curr_size_ - 1) {
                os << ", ";
            }
        }
        os << "]";
    }

    template<typename element>
    void Array<element>::clear() {
        while (curr_size_ > 0) {
            pop_back();
        }
    }

    template<typename element>
    void Array<element>::swap_all(Array<element> &other) {
        std::swap(block_size_, other.block_size_);
        std::swap(curr_capacity_, other.curr_capacity_);
        std::swap(curr_size_, other.curr_size_);
        std::swap(data_, other.data_);
    }

    template<typename element>
    void Array<element>::try_push_all(const Array<element> &other) {
        for (size_t i = 0; i < other.curr_size_; ++i) {
            try {
                push_back(other[i]);
            } catch (...) {
                clear();
                throw;
            }
        }
    }

    template<typename element>
    std::ostream &operator<<(std::ostream &os, const Array<element> &array) {
        array.print(os);
        return os;
    }

    template<typename element>
    void *Array<element>::add_block() {
        void *ptr = std::malloc(block_size_ * sizeof(element));

        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        try {
            data_.push_back(static_cast<element *>(ptr));
            curr_capacity_ += block_size_;
        } catch (const std::bad_alloc &) {
            std::free(ptr);
            throw;
        }
        return ptr;
    }

    template<typename element>
    void Array<element>::remove_block() {
        std::free(data_.back());
        data_.pop_back();
        curr_capacity_ -= block_size_;
    }

    template<typename element>
    void Array<element>::remove_block_condition() {
        if (curr_size_ % block_size_ == 0) {
            remove_block();
        }
    }

    template<typename element>
    void Array<element>::add_block_condition() {
        if (curr_size_ == curr_capacity_) {
            add_block();
        }
    }

    template<typename element>
    void Array<element>::push_back(const element &item) {
        add_block_condition();

        try {
            new(&data_[curr_size_ / block_size_][curr_size_ % block_size_]) element(item);
            ++curr_size_;
        } catch (...) {
            remove_block_condition();
            throw;
        }
    }

    template<typename element>
    void Array<element>::push_back(element &&item) {
        add_block_condition();

        try {
            new(&data_[curr_size_ / block_size_][curr_size_ % block_size_]) element(std::move(item));
            ++curr_size_;
        } catch (...) {
            remove_block_condition();
            throw;
        }
    }

    template<typename element>
    void Array<element>::pop_back() {
#ifdef __DEBUG__
        if (curr_size_ <= 0) {
            throw std::invalid_argument("Empty array");
        }
#endif
        --curr_size_;
        data_[curr_size_ / block_size_][curr_size_ % block_size_].~element();
        remove_block_condition();
    }

    template<typename element>
    void Array<element>::check_index(size_t index) const {
#ifdef __DEBUG__
        if (index >= curr_size_) {
            throw std::out_of_range("Invalid index");
        }
#endif
    }

    template<typename element>
    element &Array<element>::at(size_t index) {
        check_index(index);
        return data_[index / block_size_][index % block_size_];
    }

    template<typename element>
    const element &Array<element>::at(size_t index) const {
        check_index(index);
        return data_[index / block_size_][index % block_size_];
    }

    template<typename element>
    element &Array<element>::operator[](size_t index) {
        return at(index);
    }

    template<typename element>
    const element &Array<element>::operator[](size_t index) const {
        return at(index);
    }

    template<typename element>
    Array<element> &Array<element>::operator=(Array<element> &other) {
        clear();
        if (this != &other) {
            Array<element> tmp(other);
            swap_all(tmp);
        }

        return *this;
    }

    template<typename element>
    Array<element> &Array<element>::operator=(Array<element> &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        swap_all(other);

        return *this;
    }

    template<typename element>
    typename Array<element>::iterator Array<element>::begin() {
        return iterator(this, 0);
    }

    template<typename element>
    typename Array<element>::iterator Array<element>::end() {
        return iterator(this, size());
    }

    template<typename element>
    typename Array<element>::const_iterator Array<element>::begin() const {
        return const_iterator(this, 0);
    }


    template<typename element>
    typename Array<element>::const_iterator Array<element>::end() const {
        return const_iterator(this, size());
    }

    template<typename element>
    typename Array<element>::const_iterator Array<element>::cbegin() const {
        return const_iterator(this, 0);
    }


    template<typename element>
    typename Array<element>::const_iterator Array<element>::cend() const {
        return const_iterator(this, size());
    }

    template<typename element>
    template<bool constant>
    class Array<element>::iterator_base {
    private:
        std::conditional_t<constant, const Array<element> *, Array<element> *> array_;
        size_t pos_;

        iterator_base(std::conditional_t<constant, const Array<element> *, Array<element> *> array_, size_t pos);

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::conditional_t<constant, const element, element>;
        using pointer = std::conditional_t<constant, const element *, element *>;
        using reference = std::conditional_t<constant, const element &, element &>;
        using array_pointer = std::conditional_t<constant, const Array<element> *, Array<element> *>;
        using difference_type = std::ptrdiff_t;

        bool operator==(const iterator_base &other) const;

        bool operator!=(const iterator_base &other) const;

        iterator_base &operator++();

        iterator_base operator++(int);

        reference operator*() const;

        pointer operator->() const;

        iterator_base &operator--();

        iterator_base operator--(int);

        iterator_base operator+(difference_type n) const;

        iterator_base operator-(difference_type n) const;

        difference_type operator-(const iterator_base &other) const;

        iterator_base &operator+=(difference_type n);

        iterator_base &operator-=(difference_type n);

        reference operator[](difference_type n) const;

        bool operator<(const iterator_base &other) const;

        bool operator>(const iterator_base &other) const;

        bool operator<=(const iterator_base &other) const;

        bool operator>=(const iterator_base &other) const;

        operator iterator_base<true>() const;

        friend class Array<element>;

    };

    template<typename element>
    template<bool constant>
    Array<element>::iterator_base<constant>::iterator_base(
            std::conditional_t<constant, const Array<element> *, Array<element> *> array, size_t pos): array_(array),
                                                                                                       pos_(pos) {}

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator==(const iterator_base &other) const {
        return array_ == other.array_ && pos_ == other.pos_;
    }

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator!=(const iterator_base &other) const {
        return !(*this == other);
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> &Array<element>::iterator_base<constant>::operator++() {
        ++pos_;
        return *this;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> Array<element>::iterator_base<constant>::operator++(int) {
        iterator_base<constant> tmp = *this;
        ++pos_;
        return tmp;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>::reference
    Array<element>::iterator_base<constant>::operator*() const {
        return array_->at(pos_);
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>::pointer
    Array<element>::iterator_base<constant>::operator->() const {
        return &array_->at(pos_);
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> &Array<element>::iterator_base<constant>::operator--() {
        --pos_;
        return *this;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> Array<element>::iterator_base<constant>::operator--(int) {
        iterator_base<constant> tmp = *this;
        --pos_;
        return tmp;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>
    Array<element>::iterator_base<constant>::operator+(difference_type n) const {
        return iterator_base<constant>(array_, pos_ + n);
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>
    Array<element>::iterator_base<constant>::operator-(difference_type n) const {
        return iterator_base<constant>(array_, pos_ - n);
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>::difference_type
    Array<element>::iterator_base<constant>::operator-(const iterator_base &other) const {
        return pos_ - other.pos_;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> &
    Array<element>::iterator_base<constant>::operator+=(difference_type n) {
        pos_ += n;
        return *this;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant> &
    Array<element>::iterator_base<constant>::operator-=(difference_type n) {
        pos_ -= n;
        return *this;
    }

    template<typename element>
    template<bool constant>
    typename Array<element>::template iterator_base<constant>::reference
    Array<element>::iterator_base<constant>::operator[](difference_type n) const {
        return array_->at(pos_ + n);
    }

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator<(const iterator_base &other) const {
        return pos_ < other.pos_;
    }

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator>(const iterator_base &other) const {
        return pos_ > other.pos_;
    }

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator<=(const iterator_base &other) const {
        return pos_ <= other.pos_;
    }

    template<typename element>
    template<bool constant>
    bool Array<element>::iterator_base<constant>::operator>=(const iterator_base &other) const {
        return pos_ >= other.pos_;
    }

    template<typename iterator_base>
    iterator_base operator+(typename iterator_base::difference_type n, const iterator_base &it) {
        return it + n;
    }


    template<typename element>
    template<bool constant>
    Array<element>::iterator_base<constant>::operator iterator_base<true>() const {
        return iterator_base<true>(array_, pos_);
    }

}

#include <type_traits>

#endif //INC_11_12TH_HW_ARRAY_H