#include <iostream>
#include <chrono>
#include <vector>

// using namespace std;

namespace timing {
    
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;
    typedef std::chrono::duration<double> Duration;
    typedef std::vector<long long> TimeParts;

    Time curr_time;

    TimeParts parse_duration(Duration t) {

        std::chrono::days d = std::chrono::duration_cast<std::chrono::days> (t);
        std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours> (t);
        std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes> (t);
        std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds> (t);
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (t);

        TimeParts parts = {d.count(), h.count(), m.count(), s.count(), ms.count()};
        return parts;

    }

    std::string strftime(Duration dur) {
        
        TimeParts parts = parse_duration(dur);

        long long d = parts[0];
        long long h = parts[1];
        long long m = parts[2];
        long long s = parts[3];
        long long ms = parts[4];

        std::string day_str = std::to_string(d) + " days ";
        std::string hour_str = std::to_string(h) + " hours ";
        std::string min_str = std::to_string(m) + " minutes ";
        std::string sec_str = std::to_string(s) + " seconds ";
        std::string millisec_str = std::to_string(ms) + " milliseconds ";

        std::string output = "--- " + day_str + hour_str + min_str + sec_str + millisec_str + " ---";

        return output;

    }

    void start() {
        curr_time = std::chrono::high_resolution_clock::now();
    }

    void end() {
        Duration time_taken = (std::chrono::high_resolution_clock::now() - curr_time);
        std::string output = strftime(time_taken);
        std::cout << output << std::endl;
    }

}