#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

int main() {
  using std::chrono_literals::operator""y;
  using std::operator""sv;

  const auto now = std::chrono::floor<std::chrono::minutes>(
      std::chrono::system_clock::now());

  { std::cout << std::chrono::zoned_time{} << " : default\n"; }
  {
    std::string location{"America/Phoenix"sv};
    std::cout << std::chrono::zoned_time{location} << " : " << location << '\n';
  }
  {
    const std::chrono::time_zone *TimeZonePtr = std::chrono::locate_zone("UTC");
    std::cout << std::chrono::zoned_time{TimeZonePtr} << " : UTC time zone\n";
  }
  {
    std::string location{"Europe/Rome"sv};
    std::cout << std::chrono::zoned_time{location,
                                         std::chrono::local_days{2021y / 12 /
                                                                 31}}
              << " : " << location << '\n';
  }
  {
    std::string location{"Europe/Rome"sv};
    auto some_date = std::chrono::sys_time<std::chrono::days>{2021y / 12 / 31};
    std::cout << std::chrono::zoned_time{location, some_date} << " : "
              << location << '\n';
  }
  {
    std::string location{"Europe/Rome"sv};
    std::cout << std::chrono::zoned_time{location, now} << " : " << location
              << '\n';
  }
  {
    std::string NewYork{"America/New_York"sv};
    std::string Tokyo{"Asia/Tokyo"sv};
    const std::chrono::zoned_time tz_Tokyo{Tokyo, now};
    const std::chrono::zoned_time tz_NewYork{NewYork, now};
    std::cout << std::chrono::zoned_time{Tokyo, tz_NewYork} << " : " << Tokyo
              << '\n';
    std::cout << std::chrono::zoned_time{NewYork, tz_Tokyo} << " : " << NewYork
              << '\n';
  }
    {
    std::string NewYork{"Etc/GMT+8"sv};
    std::string Tokyo{"Etc/GMT-8"sv};
    const std::chrono::zoned_time tz_Tokyo{Tokyo, now};
    const std::chrono::zoned_time tz_NewYork{NewYork, now};
    std::cout << std::chrono::zoned_time{Tokyo, tz_NewYork} << " : " << Tokyo
              << '\n';
    std::cout << std::chrono::zoned_time{NewYork, tz_Tokyo} << " : " << NewYork
              << '\n';
  }
}