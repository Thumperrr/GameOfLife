#ifndef _JSONREADER_H
#define _JSONREADER_H

#include "core/Exception.hpp"

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace gol
{
    namespace util
    {
        class JsonReader
        {
            class JsonReaderImpl
            {
                friend class JsonReader;
                boost::property_tree::ptree tree;

            public:
                JsonReaderImpl(const std::string &file)
                {
                    try
                    {
                        boost::property_tree::read_json(file, tree);
                    }
                    catch(boost::property_tree::json_parser_error &p)
                    {
                        throw core::exception(p.what());
                    }
                }
                ~JsonReaderImpl() = default;
            };

        public:
            JsonReader(const std::string &file) : impl(new JsonReaderImpl(file)) {};
            ~JsonReader() = default;

            template<typename T>
            T getProperty(const std::string &key)
            {
                boost::optional<T> ret = impl->tree.get_optional<T>(key);
                if(ret == boost::optional<T>())
                    throw core::exception("Error: JsonReader::getProperty failed.");
                return ret.get();
            }

        private:
            std::unique_ptr<JsonReaderImpl> impl;
        };
    }
}

#endif