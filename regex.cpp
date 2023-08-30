
#include <chrono>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

std::string to_gmt_name(int zoneOffset) {
    zoneOffset = -zoneOffset;
  //   std::cout << "Use zone: " << zoneOffset << "\n";
  return std::string("Etc/GMT") + +(zoneOffset > 0 ? "+" : "") +
         (zoneOffset ? std::to_string(zoneOffset) : "");
}
std::string zone_time_now(int zone) {
  auto z = std::chrono::locate_zone(to_gmt_name(zone));
  std::cout << to_gmt_name(zone) << " -> " << z->name() << "\n";

  if (!z) {
    return {"invalid time zone"};
  }

  // const auto now =
  // std::chrono::floor<std::chrono::minutes>(std::chrono::system_clock::now());
  const auto now = std::chrono::system_clock::now();
  const auto localNow = std::chrono::zoned_time {std::chrono::current_zone(),now};
//   const std::chrono::zoned_time time{z, localNow}; It's ok.
  const std::chrono::zoned_time time{z, now};
  std::stringstream ss;
  ss << time;
  return ss.str();
}
int main() {
  std::string src = "2023-06-30T12:00:00.000+08:00";

  std::regex re{"([0-9]+)-([0-9]+)-([0-9]+)T([0-9]+):([0-9]+):([0-9]+)\\.([0-9]"
                "+)([+-][0-9]+):([0-9]+)"};
  std::smatch color_match;
  auto result = std::regex_search(src, color_match, re);
  std::string array[] = {"total",    "year",        "month",  "day",
                         "hour",     "minute",      "second", "ms",
                         "timezone", "timezone_min"};
  int i = 0;
  if (color_match.empty()) {
    std::cerr << "Not match.\n";
  }
  for (auto c : color_match) {

    std::cout << array[i] << ": " << c.str() << "\n";
    i++;
  }
  auto d1 = std::chrono::year_month_day(
      std::chrono::year{2023}, std::chrono::month{10}, std::chrono::day{12});

  const auto today = std::chrono::sys_days{
      std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
  auto fu = std::chrono::sys_days{d1};
  std::cout << (fu - today).count() << " days\n";
  const std::chrono::zoned_time cur_time{std::chrono::current_zone(),
                                         std::chrono::system_clock::now()};
  std::cout << cur_time << '\n';
  const std::chrono::zoned_time gmt_time{std::chrono::locate_zone("Etc/GMT"),
                                         std::chrono::system_clock::now()};
  std::cout << gmt_time << '\n';

  std::cout << zone_time_now(std::stoi(color_match[8])) << "\n";

  std::cout << "Zone name:" << std::chrono::current_zone()->name() << "\n";
  //   std::cout << "Zone name:" << std::<< "\n";

  for (auto &tzdb : std::chrono::get_tzdb_list()) {
    std::cout << tzdb.version << "\n";
    std::cout << tzdb.links[0].name() <<"\n";
    std::cout << tzdb.links[0].target() <<"\n";
    for (auto &zone : tzdb.zones) {
      //   std::cout << zone.name() << "\n";
    }
  }

  for (int i = -11; i < 12; i++) {
    std::cout << zone_time_now(i) << "\n";
  }
}