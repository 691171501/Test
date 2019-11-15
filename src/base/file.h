//
// Created by xuchaowu on 10/10/19.
//

#ifndef EQUITY_SERVER_FILE_H
#define EQUITY_SERVER_FILE_H
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <mutex>
#include "string_utils.h"

namespace  zsequity{
    namespace rawdata{

        using BinaryData = std::vector<uint8_t>;
        using StringData = std::vector<std::string>;

        template <class DataType, int MAX_LINE_LEN>
        class FileIO{
        public:
            std::vector<DataType> ReadData (const std::string& file ,
                                            long& pos ,
                                            const std::string& delmiter = ",",
                                            bool trim = true ){

                std::vector<DataType> data;
                return  data;
            }

        };

        template <int MAX_LINE_LEN>
        class FileIO<BinaryData, MAX_LINE_LEN> {
        public:
            std::vector<BinaryData> ReadData(const std::string &file,
                                             long& pos ,
                                             const std::string &delmiter = ",",
                                             bool trim = true) {
                std::vector<BinaryData> data;
                return  data;
            }
        };

        template <int MAX_LINE_LEN>
        class FileIO<StringData, MAX_LINE_LEN> {
        public:
            std::vector<StringData> ReadData(const std::string &file,
                                             long& pos ,
                                             const std::string &delmiter = ",",
                                             bool trim = true) {

                std::vector<StringData>  vec_data;
                std::ifstream inf(file, std::ios::in);
                long start_pos = inf.tellg();
                inf.seekg(0, std::ios::end);
                long end = inf.tellg();

                inf.seekg(pos, std::ios::beg);
                char buf[MAX_LINE_LEN] = {0};

                while (!inf.eof()) {
                    inf.getline(buf, MAX_LINE_LEN);
                    std::vector<std::string> data = StringSplit(buf, delmiter);
                    if(data.size() <2) {
                        continue;
                    }

                    if (!trim) {
                        vec_data.emplace_back(std::move(data));
                    } else {
                        std::vector<std::string> trimmed_data;

                        for (const auto& val : data) {
                            trimmed_data.emplace_back(Trim(val));
                        }

                        vec_data.emplace_back(std::move(trimmed_data));
                    }
                }

                pos = end;
                return  vec_data;
            }
        };




        class SaveToFile {
        public:
            SaveToFile() : outf_(nullptr){
            }

            ~SaveToFile() {
                CloseFile();
            }

            template <class T>
            void ToFile(const int& type, const T& data) {
                std::lock_guard<std::mutex> lock(mutex_);
                LOG_ASSERT(outf_ != nullptr);
                std::fwrite(&type, sizeof(type), 1, outf_);
                std::fwrite(&data, sizeof(data), 1 , outf_);
            }

            template <class T>
            void ToFile(const T& data) {
                LOG_ASSERT(outf_ != nullptr);
                std::lock_guard<std::mutex> lock(mutex_);
                std::fwrite(&data, sizeof(data), 1 , outf_);
            }

            void ToFile(void* data, int len) {
                LOG_ASSERT(outf_ != nullptr);
                LOG_ASSERT(data != nullptr);
                CHECK_GT(len, 0);
                std::fwrite(data, len, 1 , outf_);
            }

            void CloseFile() {
                if (outf_ != nullptr) {
                    std::fclose(outf_);
                    outf_ = nullptr;
                }
            }

            void OpenFile(const std::string& file) {
                CHECK(outf_ == nullptr);
                file_  = file;
                outf_ = std::fopen(file.c_str(), "ab");
            }

            void OpenFile() {
                CHECK(outf_ == nullptr);
                outf_ = std::fopen(file_.c_str(), "ab");
            }


        private:
            std::FILE* outf_;
            std::mutex mutex_;
            std::string file_;
        };

    }
}



#endif //EQUITY_SERVER_FILE_H
