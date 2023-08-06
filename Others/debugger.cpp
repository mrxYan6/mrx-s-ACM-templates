

namespace dbg {
    class dbg_ostream {
    public:
        template <typename T>
        dbg_ostream& operator<<(const T& data) {
            std::cerr << "\033[31m" << data << "\033[0m";
            return *this;
        }
    };
    dbg_ostream cerr;
};