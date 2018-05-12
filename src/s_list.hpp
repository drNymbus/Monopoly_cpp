#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

namespace sl {
    template <typename T>
    struct SList {
            T* data;
            SList<T>* next;

            friend std::ostream& operator <<(std::ostream& os, SList* l) {
                if (l->next == nullptr) {
                    return os;
                }

                l = l->next;
                os << "{ ";
                while(l->next != nullptr) {
                    os << l->data << ", ";
                    l = l->next;
                }
                os << l->data << " ";
                os << "}";
                return os;
            }
    };


/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* create_list(void) {
        SList<T>* l = new SList<T>();
        if (l != nullptr) {
            l->next = nullptr;
            return l;
        } else {
            std::cerr << "Cannot create list" << std::endl;
            return nullptr;
        }
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> void free_list(SList<T>* l) {
        SList<T>* p = l;
        while (p->next != nullptr) {
            SList<T>* tmp = p->next;
            delete p;
            p = tmp;
        }
        delete p;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> unsigned int size(SList<T>* l) {
        unsigned int i = 0;
        while (l->next != nullptr) {
            l = l->next;
            i++;
        }
        return i;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> T* get_data(SList<T>* l) {
        if (l == nullptr) {
            std::cerr << "Cannot get data from null pointer" << std::endl;
            return nullptr;
        }
        return l->data;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* get_next(SList<T>* l) {
        return l->next;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* prepend(SList<T>* l, T* value) {
        SList<T>* p = create_list<T>();
        if (p != nullptr) {
            p->data = value;
            p->next = l->next;
            l->next = p;
            return l;
        }
        return nullptr;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* append(SList<T>* l, T* value) {
        SList<T>* p = l;
        while (p->next != nullptr) {
            p = p->next;
        }

        SList<T>* n_node = create_list<T>();
        n_node->data = value;
        p->next = n_node;

        return l;
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* insert_after(SList<T>* l, SList<T>* p, T* data) {
        if (l == nullptr || p == nullptr) {
            std::cerr << "Cannot insert_after with nullptr" << std::endl;
            return nullptr;
        }
        SList<T>* n_node = create_list<T>();
        n_node->data = data;

        n_node->next = p->next;
        p->next = n_node;

        return l;
    }

    template <typename T> SList<T>* insert_before(SList<T>* l, SList<T>* p, T* data) {
        SList<T>* prev = l;
        while (prev->next != p && prev->next != nullptr) {
            prev = prev->next;
        }
        if (prev->next == p) {
            SList<T>* n_node = create_list<T>();
            n_node->data = data;
            n_node->next = p;

            prev->next = n_node;
            return l;
        } else {
            std::cerr << "Cannot insert_before with nullptr" << std::endl;
            return nullptr;
        }
    }

/*
 * \param:
 * \brief:
 * \return:
 */
    template <typename T> SList<T>* remove(SList<T>* l, SList<T>* p) {
        SList<T>* rm = l;
        while (rm->next != p && rm->next != nullptr) {
            rm = rm->next;
        }
        if (rm->next != nullptr) {
            rm->next = p->next;
            delete p;
            return l;
        } else {
            std::cout << "Cannot remove item not in list" << std::endl;
            return nullptr;
        }
    }
}

// bool operator>(SList* l1, SList* l2);
// bool operator<(SList* l1, SList* l2);
// bool operator==(SList* l1, SList* l2);
// ostream& operator<<(ostream& os, SList* l);
