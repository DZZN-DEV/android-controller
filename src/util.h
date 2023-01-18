#ifndef UTIL_H
#define UTIL_H

#include <QByteArray>
#include <tuple>

template <typename... TArgs>
void append(QByteArray& byteArray, std::tuple<TArgs...> const& data) {
  std::apply(
      [&](auto const&... elem) {
        (byteArray.append(reinterpret_cast<const char*>(&elem), sizeof(elem)),
         ...);
      },
      data);
}

#endif  // UTIL_H
