/*
    This example parses a JSON file and pretty-prints
    it to standard output.
*/

#include <boost/json/src.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>

namespace json = boost::json;

json::value parse_file( char const* filename )
{
    std::shared_ptr<std::istream> f;

    if (strcmp(filename, "-") == 0)
    {
        f.reset(&std::cin, [](...) {});
    }
    else
    {
        std::ifstream* pFile = new std::ifstream(filename);
        if (!pFile->is_open())
        {
            return nullptr;
        }
        f.reset(pFile);
    }


    json::stream_parser p;
    json::error_code ec;
    while (f->good())
    {
        char buf[4096];
        f->read(buf, sizeof(buf));
        size_t nread = f->gcount();
        p.write(buf, nread, ec);
    };

    if( ec )
        return nullptr;
    p.finish( ec );
    if( ec )
        return nullptr;
    return p.release();
}

void pretty_print( std::ostream& os, json::value const& jv, std::string* indent = nullptr )
{
    std::string indent_;
    if(! indent)
        indent = &indent_;
    switch(jv.kind())
    {
    case json::kind::object:
    {
        os << "{\n";
        indent->append(4, ' ');
        auto const& obj = jv.get_object();
        if(! obj.empty())
        {
            auto it = obj.begin();
            for(;;)
            {
                os << *indent << json::serialize(it->key()) << " : ";
                pretty_print(os, it->value(), indent);
                if(++it == obj.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "}";
        break;
    }

    case json::kind::array:
    {
        os << "[\n";
        indent->append(4, ' ');
        auto const& arr = jv.get_array();
        if(! arr.empty())
        {
            auto it = arr.begin();
            for(;;)
            {
                os << *indent;
                pretty_print( os, *it, indent);
                if(++it == arr.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "]";
        break;
    }

    case json::kind::string:
    {
        os << json::serialize(jv.get_string());
        break;
    }

    case json::kind::uint64:
    case json::kind::int64:
    case json::kind::double_:
        os << jv;
        break;

    case json::kind::bool_:
        if(jv.get_bool())
            os << "true";
        else
            os << "false";
        break;

    case json::kind::null:
        os << "null";
        break;
    }

    if(indent->empty())
        os << "\n";
}

int main(int argc, char** argv)
{
    char filename[260]{};
    switch (argc)
    {
    case 1: 
        strcpy_s(filename, "-");
        break;
    case 2:
        strcpy_s(filename, argv[1]);
        break;
    default:
        std::cerr << "Usage: JsonPretty <jsonfile>" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        // Parse the file as JSON
        auto const jv = parse_file(filename);

        // Now pretty-print the value
        pretty_print(std::cout, jv);
    }
    catch(std::exception const& e)
    {
        std::cerr <<
            "Caught exception: "
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}