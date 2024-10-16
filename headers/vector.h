#include <exception>
#include <stdexcept>
#include <string>

namespace vector{
    class VectorException: public std::exception{
    public:
        explicit VectorException(std::string &&cur_message) {
            message = std::move(cur_message);
        }

        const char* what() {
            return message.c_str();
        }
    private:
        std::string message;
    };

    template <class T>
    class Vector{
    private:
        int reserve{};
        int len{};
        T *data;

    public:
        //default constructor
        Vector() {
            reserve = 4;
            len = 0;
            data = new T[4];
        }

        //copy constructor
        Vector(const Vector &s) {
            reserve = s.reserve;
            len = s.len;
            data = new T[s.reserve];
            for (int i = 0; i < s.len; i++){
                data[i] = s.data[i];
            }
        }

        //move constructor
        Vector(Vector &&s) noexcept{
            reserve = s.reserve;
            len = s.len;
            data = std::move(s.data);
            s.data = nullptr;
        }

        //copy assignment operator
        Vector& operator=(const Vector &other){
            this = Vector(other);
            return *this;
        }

        //move assignment operator
        Vector& operator=(Vector&& other) noexcept{
            len = std::move(other.len);
            reserve = std::move(other.reserve);
            data = std::move(other.data);
            return *this;
        }

        ~Vector(){
            delete []data;
        };

        struct Iterator {
            Iterator(T* ptr, int i, Vector<T> *cur_vec) {
                cur_val = ptr;
                index = i;
                vec = cur_vec;
            }

            T& operator*() const{
                if (cur_val == nullptr) {throw std::out_of_range{"no such element"};}
                return *(cur_val);
            }

            bool operator==(const Iterator& b) const{
                return this->index == b.index;
            }

            bool operator!=(const Iterator& b) const{
                return this->index != b.index;
            }

            Iterator operator++(){
                if (index + 1 < vec->len) {
                    this->cur_val = (T*)(&((vec->data)[index + 1]));
                    this->index += 1;
                    return (*this);
                } else {
                    this->index = (vec->len) + 1;
                    this->cur_val = nullptr;

                    return vec->end();
                }
            }

            Iterator operator--(){
                if (index - 1 >= 0) {
                    this->cur_val = (T*)(&((vec->data)[index - 1]));
                    this->index -= 1;
                    return (*this);
                } else {
                    this->index = (vec->len) + 1;
                    this->cur_val = nullptr;

                    return vec->end();
                }
            }

        private:
            T* cur_val = nullptr;
            int index = -1;
            Vector<T> *vec = nullptr;
        };

        Iterator begin() { Iterator ret = Iterator(&this->data[0], 0, this); return ret; }
        Iterator end() { Iterator ret = Iterator(nullptr, this->len + 1, this); return ret; }

        Iterator begin() const { Iterator ret = Iterator(&this->data[0], 0, this); return ret; }
        Iterator end() const { Iterator ret = Iterator(nullptr, (this->len) + 1, this); return ret; }

        T &operator [] (const int i) {
            if (i >= 0 && i < this->len) {
                return this->data[i];
            } else {
                throw VectorException("Invalid index in [] operator");
            }
        }

        int size() {
            return this->len;
        }

        int capacity() {
            return this->reserve;
        }

        T &back() {
            if (this->empty()) {
                throw VectorException("Trying to get the back element of empty vector");
            } else {
                T &a = this->data[this->len - 1];
                return a;
            }
        }

        T &front() {
            if (this->empty()) {
                throw VectorException("Trying to get the front element of empty vector");
            } else {
                T &a = this->data[0];
                return a;
            }
        }

        bool empty() {
            if (this->len == 0) {
                return true;
            } else {
                return false;
            }
        }

        void push_back(const T& elem) {
            if (this->len < this->reserve) {
                data[len] = elem;
                ++len;
            } else {
                T *new_data = new T[this->reserve * 2];
                for (int i = 0; i < this->len; i++) {
                    new_data[i] = data[i];
                }

                T *temp = this->data;
                this->data = new_data;
                delete [] temp;

                data[len] = elem;
                ++len;
                reserve = this->reserve * 2;
            }
        }

        void push_back(T&& elem) {
            this->push_back(elem);
        }

        void pop_back() {
            if (this->len > 0) {
                --len;
            } else {
                throw VectorException("Trying to pop from empty vector");
            }
        }

    };
}
