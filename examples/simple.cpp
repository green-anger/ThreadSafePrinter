#include <thread>
#include <vector>

#include "ThreadSafePrinter.hpp"


using namespace alt;


namespace
{

    class CustomPolicy1
    {
    public:
        static void prefix( std::ostringstream& oss )
        {
            oss << "[begin] ";
        }

        static void suffix( std::ostringstream& oss )
        {
            oss << " [end]";
        }
    };


    class CustomPolicy2 : public MarkPolicy
    {
    public:
        static void prefix( std::ostringstream& oss )
        {
            MarkPolicy::prefix( oss );
            oss << "[custom prefix] ";
        }

        static void suffix( std::ostringstream& oss )
        {
            MarkPolicy::suffix( oss );
            oss << " [custom suffix]";
        }
    };


}


using TSP = ThreadSafePrinter<>;
using TSPM = ThreadSafePrinter<MarkPolicy>;
using TSPC1 = ThreadSafePrinter<CustomPolicy1>;
using TSPC2 = ThreadSafePrinter<CustomPolicy2>;


int main( int argc, char** argv )
{
    TSP() << "main thread " << std::this_thread::get_id() << "\n";

    const std::size_t tNum = 4;
    std::vector<std::thread> vec;

    auto clearVec = [&vec]() {
        for ( auto&& t : vec )
            t.join();
        vec.clear();
    };


    TSP() << "\nTest.1\n";

    for ( decltype( vec )::size_type i = 0; i < tNum; ++i )
    {
        vec.emplace_back( std::thread( [i]() {
            for ( int k = 0; k < 10; ++k )
                TSP() << "Thread " << std::to_string( i );
        } ) );
    }

    clearVec();


    TSP() << "\nTest.2\n";

    for ( decltype( vec )::size_type i = 0; i < tNum; ++i )
    {
        vec.emplace_back( std::thread( [i]() {
            for ( int k = 0; k < 10; ++k )
                TSPM() << "Thread " << std::to_string( i );
        } ) );
    }

    clearVec();


    TSP() << "\nTest.3\n";

    for ( decltype( vec )::size_type i = 0; i < tNum; ++i )
    {
        vec.emplace_back( std::thread( [i]() {
            for ( int k = 0; k < 10; ++k )
                TSPC1() << "Thread " << std::to_string( i );
        } ) );
    }

    clearVec();


    TSP() << "\nTest.4\n";

    for ( decltype( vec )::size_type i = 0; i < tNum; ++i )
    {
        vec.emplace_back( std::thread( [i]() {
            for ( int k = 0; k < 10; ++k )
                TSPC2() << "Thread " << std::to_string( i );
        } ) );
    }

    clearVec();


    return 0;
}
