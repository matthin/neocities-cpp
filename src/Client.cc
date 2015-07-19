#include "Client.h"
#include <cpr.h>
#include <utility>
#include <iostream>

namespace neoc {

constexpr char Client::rootPath[];

Client::Client(const std::string& user, const std::string pass)
    : user(std::move(user)), pass(std::move(pass)) {
}

bool Client::upload(const std::string& name, const std::string& location) {
  const auto response = cpr::Post(
    Url{std::string(rootPath) + "upload"},
    Authentication{user, pass},
    Multipart{{name, File{location}}}
  );
  return response.status_code == 200;
}

bool Client::remove(const std::string& name) {
  const auto response = cpr::Post(
    Url{std::string(rootPath) + "delete"},
    Authentication{user, pass},
    Multipart{{"filenames[]", name}}
  );
  return response.status_code == 200;
}

std::string Client::info() {
  const auto response = cpr::Get(
    Url{std::string(rootPath) + "info"},
    Authentication{user, pass}
  );
  return response.text;
}

std::string Client::info(const std::string& user) {
  const auto response = cpr::Get(
    Url{std::string(rootPath) + "info"},
    Parameters{{"sitename", user}}
  );
  return response.text;
}

} // namespace neoc
