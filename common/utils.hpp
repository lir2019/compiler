#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <iostream>
#include <sstream>
#include <memory>

#define LOG do { std::cout << __FILE__ << ": " << __LINE__ << std::endl; } while (false)

#define CHECK(predicate, comment)                                                               \
  do {                                                                                          \
    auto res = predicate;                                                                       \
    if (!res) {                                                                                 \
      std::stringstream ss;                                                                     \
      ss << "check " << #predicate << " failed: " << comment;                                   \
      std::cerr << __FILE__ << ": " << __LINE__ << "  " << ss.str() << std::endl;               \
      throw std::runtime_error(ss.str().c_str());                                               \
    }                                                                                           \
  } while (false)

#define DECL_DUMP_FUNCS(class_name)                                                             \
  void Print(std::ostream &os) const ;                                                          \
  std::string ToString() const ;                                                                \
  friend std::ostream &operator<<(std::ostream &os, const class_name &object);

#define DEFINE_DUMP_FUNCS(class_name, print_body)                                               \
  void class_name::Print(std::ostream &os) const { print_body }                                 \
  std::string class_name::ToString() const {                                                    \
    std::stringstream ss;                                                                       \
    this->Print(ss);                                                                            \
    return ss.str();                                                                            \
  }                                                                                             \
  std::ostream &operator<<(std::ostream &os, const class_name &object) {                        \
    object.Print(os);                                                                           \
    return os;                                                                                  \
  }

template <typename T, typename First>
bool IsA(std::shared_ptr<T> sptr) {
  if (sptr == nullptr) {
    return false;
  }
  if (std::dynamic_pointer_cast<First>(sptr)) {
    return true;
  }
  return false;
}

template <typename T, typename First, typename Second, typename ...Rest>
bool IsA(std::shared_ptr<T> sptr) {
  if (sptr == nullptr) {
    return false;
  }
  if (std::dynamic_pointer_cast<First>(sptr)) {
    return true;
  }
  return IsA<T, Second, Rest...>(sptr);
}

#endif  // COMMON_UTILS_HPP
